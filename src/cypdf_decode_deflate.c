#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "cypdf_decode_deflate.h"
#include "cypdf_log.h"
#include "cypdf_memory.h"



typedef struct CYPDF_Inflate {
    const unsigned char*    bytes;
    size_t                  len;
    size_t                  byte_pos;
    unsigned char           bit_pos;

    unsigned char*          inflated;
    size_t                  inflated_len;
    size_t                  inflated_size;
} CYPDF_Inflate;


static void BlockDynamic(CYPDF_Inflate* const inflate);

static void BlockFixed(CYPDF_Inflate* const inflate);

static void BlockUncompressed(CYPDF_Inflate* const inflate);

static uint16_t* HuffmanAlphabet(const size_t* const code_lens, const size_t code_count, size_t* const tree_size);

static void ProcessCompressed(CYPDF_Inflate* const inflate, const uint16_t* const lit_alphabet, const size_t lit_size, const size_t* const lit_code_lens, const uint16_t* const dist_alphabet, const size_t dist_size, const size_t* const dist_code_lens);

static void ProcessLZ77(CYPDF_Inflate* const inflate, uint16_t value, const uint16_t* const dist_alphabet, const size_t dist_size, const size_t* const dist_code_lens);

static bool ConsumeBit(CYPDF_Inflate* const inflate);

static void UnconsumeBit(CYPDF_Inflate* const inflate);

static unsigned char ConsumeByte(CYPDF_Inflate* const inflate);

static size_t ConsumeNumeric(CYPDF_Inflate* const inflate, const size_t bit_count);

static uint16_t ConsumeCode(CYPDF_Inflate* const inflate, const uint16_t* const alphabet, const size_t alphabet_size, const size_t* code_lens);

static void AppendByte(CYPDF_Inflate* const inflate, const unsigned char byte);


unsigned char* CYPDF_DecodeInflate(const unsigned char* restrict const source, const size_t len, size_t* restrict const inflated_len) {
    CYPDF_TRACE;

    if (!source) {
        return NULL;
    }

    CYPDF_Inflate inflate = {
        .bytes = source,
        .len = len,
        .byte_pos = (size_t)0,
        .bit_pos = 0x01,
        .inflated = CYPDF_malloc(1024 * sizeof(unsigned char)),
        .inflated_len = 0,
        .inflated_size = 1024
    };

    /* Process blocks. */
    bool final_block = false;
    uint16_t block_type = 0;
    do {
        final_block = ConsumeBit(&inflate);
        block_type = (uint16_t)ConsumeNumeric(&inflate, 2);
        switch (block_type)
        {
        case 0:
            BlockUncompressed(&inflate);
            break;
        case 1:
            BlockFixed(&inflate);
            break;
        case 2:
            BlockDynamic(&inflate);
            break;
        default:
            break;
        }
    } while (!final_block);

    inflate.inflated = CYPDF_realloc(inflate.inflated, inflate.inflated_len * sizeof(unsigned char));

    *inflated_len = inflate.inflated_len;
    return inflate.inflated;
}

static void BlockDynamic(CYPDF_Inflate* const inflate) {
    static size_t code_len_len_order[19] = {
        16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15
    };

    size_t lit_code_count = ConsumeNumeric(inflate, 5) + 257;
    size_t dist_code_count = ConsumeNumeric(inflate, 5) + 1;
    size_t code_len_code_count = ConsumeNumeric(inflate, 4) + 4;

    size_t code_len_code_lens[19] = { 0 };
    for (size_t i = 0; i < code_len_code_count; ++i) {
        code_len_code_lens[code_len_len_order[i]] = ConsumeNumeric(inflate, 3);
    }

    size_t code_len_size = 0;
    uint16_t* code_len_alphabet = HuffmanAlphabet(code_len_code_lens, 19, &code_len_size);

    /* Generate literal/length and dist huffman alphabet. */
    size_t code_count = lit_code_count + dist_code_count;
    size_t* code_lens = CYPDF_malloc(code_count * sizeof(size_t));
    size_t* lit_code_lens = code_lens;
    size_t* dist_code_lens = code_lens + lit_code_count;
    uint16_t value = 0;
    size_t i = 0;
    while (i < code_count) {
        value = ConsumeCode(inflate, code_len_alphabet, code_len_size, code_len_code_lens);

        if (value == CYPDF_DEFLATE_UNKNOWN_CODE) {
            return;
        } else if (value == 16) {
            size_t repeat = ConsumeNumeric(inflate, 2) + 3;
            size_t prev_len = code_lens[i - 1];
            for (size_t j = 0; j < repeat; ++j) {
                code_lens[i++] = prev_len;
            }
        } else if (value == 17 || value == 18) {
            size_t repeat = 0;
            if (value == 17) {
                repeat = ConsumeNumeric(inflate, 3) + 3;
            } else {
                repeat = ConsumeNumeric(inflate, 7) + 11;
            }

            for (size_t j = 0; j < repeat; ++j) {
                code_lens[i++] = 0;
            }
        } else {
            code_lens[i++] = value;
        }
    }

    size_t lit_size = 0;
    uint16_t* lit_alphabet = HuffmanAlphabet(lit_code_lens, lit_code_count, &lit_size);
    size_t dist_size = 0;
    uint16_t* dist_alphabet = HuffmanAlphabet(dist_code_lens, dist_code_count, &dist_size);

    free(code_len_alphabet);

    ProcessCompressed(inflate, lit_alphabet, lit_size, lit_code_lens, dist_alphabet, dist_size, dist_code_lens);

    free(code_lens);
    free(lit_alphabet);
    free(dist_alphabet);
}

static void BlockFixed(CYPDF_Inflate* const inflate) {
    size_t lit_code_lens[288];
    size_t i = 0;
    for (; i < 144; ++i) {
        lit_code_lens[i] = 8;
    }
    for (; i < 256; ++i) {
        lit_code_lens[i] = 9;
    }
    for (; i < 280; ++i) {
        lit_code_lens[i] = 7;
    }
    for (; i < 288; ++i) {
        lit_code_lens[i] = 8;
    }
    size_t lit_size = 0;
    uint16_t* lit_alphabet = HuffmanAlphabet(lit_code_lens, 288, &lit_size);

    size_t dist_code_lens[32];
    for (i = 0; i < 32; ++i) {
        dist_code_lens[i] = 5;
    }
    size_t dist_size = 0;
    uint16_t* dist_alphabet = HuffmanAlphabet(dist_code_lens, 32, &dist_size);

    ProcessCompressed(inflate, lit_alphabet, lit_size, lit_code_lens, dist_alphabet, dist_size, dist_code_lens);

    free(lit_alphabet);
    free(dist_alphabet);
}

static void BlockUncompressed(CYPDF_Inflate* const inflate) {
    /* Go to next byte boundary. */
    if (inflate->bit_pos != 0x01) {
        ConsumeByte(inflate);
    }

    size_t length = ConsumeNumeric(inflate, 16);
    ConsumeByte(inflate);                           /* Consume NLEN bytes. */
    ConsumeByte(inflate);
    for (size_t i = 0; i < length; ++i) {
        AppendByte(inflate, ConsumeByte(inflate));
    }
}

static uint16_t* HuffmanAlphabet(const size_t* const code_lens, const size_t code_count, size_t* const alphabet_size) {
    size_t code_len_freq[CYPDF_DEFLATE_CODE_LENGTH_MAX + 1] = { 0 };
    for (size_t i = 0; i < code_count; ++i) {
        if (code_lens[i] > CYPDF_DEFLATE_CODE_LENGTH_MAX) {
            fprintf(stderr, "Huffman code length exceeds the limit: %zu > %u\n", code_lens[i], CYPDF_DEFLATE_CODE_LENGTH_MAX);
            return NULL;
        }
        ++code_len_freq[code_lens[i]];
    }

    /* Determine lowest possible code for each code length. */
    uint16_t code = 0;
    uint16_t next_code[CYPDF_DEFLATE_CODE_LENGTH_MAX + 1] = { 0 };
    code_len_freq[0] = 0;
    for (size_t len = 1; len <= CYPDF_DEFLATE_CODE_LENGTH_MAX; ++len) {
        code = (uint16_t)(code + code_len_freq[len - 1]) << 1;
        next_code[len] = code;
    }

    /* Map Huffman codes to alphabet values. */
    size_t max_code_len = 0;
    for (size_t i = 0; i <= CYPDF_DEFLATE_CODE_LENGTH_MAX; ++i) {
        if (code_len_freq[CYPDF_DEFLATE_CODE_LENGTH_MAX - i]) {
            max_code_len = CYPDF_DEFLATE_CODE_LENGTH_MAX - i;
            break;
        }
    }
    *alphabet_size = next_code[max_code_len] + code_len_freq[max_code_len];
    uint16_t* alphabet = CYPDF_malloc(*alphabet_size * sizeof(uint16_t));
    memset(alphabet, CYPDF_DEFLATE_UNKNOWN_CODE & 0xFF, *alphabet_size * sizeof(uint16_t));

    size_t curr_len = 0;
    for (uint16_t i = 0; i < code_count; ++i) {
        curr_len = code_lens[i];
        if (curr_len) {
            alphabet[next_code[curr_len]] = i;
            ++next_code[curr_len];
        }
    }

    return alphabet;
}

static void ProcessCompressed(CYPDF_Inflate* const inflate, const uint16_t* const lit_alphabet, const size_t lit_size, const size_t* const lit_code_lens, const uint16_t* const dist_alphabet, const size_t dist_size, const size_t* const dist_code_lens) {
    uint16_t value = 0;
    while (value != 256) {     /* 256 indicates end of block */
        value = ConsumeCode(inflate, lit_alphabet, lit_size, lit_code_lens);

        if (value == CYPDF_DEFLATE_UNKNOWN_CODE) {
            fprintf(stderr, "Unknown literal/length code.\n");
            break;
        } else if (value < 256) {
            AppendByte(inflate, (unsigned char)value);
        } else if (value > 256) {
            ProcessLZ77(inflate, value, dist_alphabet, dist_size, dist_code_lens);
        }
    }
}

static void ProcessLZ77(CYPDF_Inflate* const inflate, uint16_t value, const uint16_t* const dist_alphabet, const size_t dist_size, const size_t* const dist_code_lens) {
    const unsigned char len_bits[31] = {
        0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0, 0, 0
    };
    const uint16_t len_base[31] = {
        3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31, 35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258, 0, 0
    };
    const unsigned char dist_bits[32] = {
        0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 0, 0
    };
    const uint16_t dist_base[32] = {
        1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193, 257, 385, 513, 769, 1025, 1537, 2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577, 0, 0
    };

    value -= 257;
    uint16_t lz77_len = (uint16_t)ConsumeNumeric(inflate, len_bits[value]) + len_base[value];

    uint16_t dist_code = ConsumeCode(inflate, dist_alphabet, dist_size, dist_code_lens);
    if (dist_code == CYPDF_DEFLATE_UNKNOWN_CODE) {
        fprintf(stderr, "Unknown distance code.\n");
        return;
    }
    uint16_t lz77_dist = (uint16_t)ConsumeNumeric(inflate, dist_bits[dist_code]) + dist_base[dist_code];

    for (size_t i = 0; i < lz77_len; ++i) {
        AppendByte(inflate, inflate->inflated[inflate->inflated_len - lz77_dist]);
    }
}

static bool ConsumeBit(CYPDF_Inflate* const inflate) {
    bool bit = inflate->bytes[inflate->byte_pos] & inflate->bit_pos;

    inflate->bit_pos <<= 1;
    if (!inflate->bit_pos) {
        inflate->bit_pos = 0x01;
        ++inflate->byte_pos;
    }

    return bit;
}

static void UnconsumeBit(CYPDF_Inflate* const inflate) {
    inflate->bit_pos >>= 1;
    if (!inflate->bit_pos) {
        inflate->bit_pos = 0x80;
        --inflate->byte_pos;
    }
}

static unsigned char ConsumeByte(CYPDF_Inflate* const inflate) {
    inflate->bit_pos = 0x01;

    return inflate->bytes[inflate->byte_pos++];
}

static size_t ConsumeNumeric(CYPDF_Inflate* const inflate, const size_t bit_count) {
    size_t numeric = 0;
    for (size_t i = 0; i < bit_count; ++i) {
        numeric |= ConsumeBit(inflate) << i;
    }

    return numeric;
}

static uint16_t ConsumeCode(CYPDF_Inflate* const inflate, const uint16_t* const alphabet, const size_t alphabet_size, const size_t* code_lens) {
    uint16_t code = 0;
    size_t code_len = 0;
    do {
        code = code << 1 | ConsumeBit(inflate);
        ++code_len;
        if (code >= alphabet_size) {
            UnconsumeBit(inflate);
            return CYPDF_DEFLATE_UNKNOWN_CODE;
        }
    } while (alphabet[code] == CYPDF_DEFLATE_UNKNOWN_CODE || code_lens[alphabet[code]] != code_len);

    return alphabet[code];
}

static void AppendByte(CYPDF_Inflate* const inflate, const unsigned char byte) {
    if (inflate->inflated_len == inflate->inflated_size) {
        inflate->inflated_size *= 2;
        inflate->inflated = CYPDF_realloc(inflate->inflated, inflate->inflated_size * sizeof(unsigned char));
    }

    inflate->inflated[inflate->inflated_len++] = byte;
}
