#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
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


static void BlockFixed(CYPDF_Inflate* const inflate);

static void BlockUncompressed(CYPDF_Inflate* const inflate);

static uint16_t* BuildHuffmanTree(const size_t* const code_lens, const size_t code_count, size_t* const tree_size);

static void ProcessLZ77(CYPDF_Inflate* const inflate, uint16_t code, const uint16_t* const dist_alphabet, const size_t* const dist_code_lens);

static uint16_t GetNextCode(CYPDF_Inflate* const inflate, const uint16_t* const alphabet, const size_t* const code_lens);

static bool ConsumeBit(CYPDF_Inflate* const inflate);

static unsigned char ConsumeByte(CYPDF_Inflate* const inflate);

static void AppendByte(CYPDF_Inflate* const inflate, const unsigned char byte);


unsigned char* CYPDF_DecodeInflate(const unsigned char* restrict const source, const size_t len, size_t* restrict const inflated_len) {
    if (!source) {
        return NULL;
    }

    CYPDF_Inflate inflate = {
        .bytes = source,
        .len = len,
        .byte_pos = (size_t)-1,
        .bit_pos = 0,
        .inflated = CYPDF_malloc(1024 * sizeof(unsigned char)),
        .inflated_len = 0,
        .inflated_size = 1024
    };

    /* Process blocks. */
    bool final_block = false;
    do {
        final_block = ConsumeBit(&inflate);
        if (ConsumeBit(&inflate)) {          /* Compressed with Dynamic Huffman Codes */
            ConsumeBit(&inflate);

        } else if (ConsumeBit(&inflate)) {   /* Compressed with Fixed Huffman Codes */
            BlockFixed(&inflate);
        } else {                            /* No Compression */
            BlockUncompressed(&inflate);
        }
    } while (!final_block);

    inflate.inflated = CYPDF_realloc(inflate.inflated, inflate.inflated_len * sizeof(unsigned char));

    *inflated_len = inflate.inflated_len;
    return inflate.inflated;
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
    size_t lit_count = 0;
    uint16_t* lit_alphabet = BuildHuffmanTree(lit_code_lens, 288, &lit_count);

    size_t dist_code_lens[32];
    for (i = 0; i < 32; ++i) {
        dist_code_lens[i] = 5;
    }
    size_t dist_count = 0;
    uint16_t* dist_alphabet = BuildHuffmanTree(dist_code_lens, 32, &dist_count);

    uint16_t code = 0;
    while (code != 256) {     /* 256 indicates end of block */
        code = GetNextCode(inflate, lit_alphabet, lit_code_lens);

        if (code < 256) {
            AppendByte(inflate, (unsigned char)code);
        } else if (code > 256) {
            ProcessLZ77(inflate, code, dist_alphabet, dist_code_lens);
        }
    }
}

static void BlockUncompressed(CYPDF_Inflate* const inflate) {
    /* Go to next byte boundary. */
    if (inflate->bit_pos != 0x80) {
        ConsumeByte(inflate);
    }

    size_t length = ConsumeByte(inflate);
    ConsumeByte(inflate);                           /* Consume NLEN byte. */
    for (size_t i = 0; i < length; ++i) {
        AppendByte(inflate, ConsumeByte(inflate));
    }
}

static uint16_t* BuildHuffmanTree(const size_t* const code_lens, const size_t code_count, size_t* const tree_size) {
    size_t code_len_freq[CYPDF_DEFLATE_CODE_LENGTH_MAX + 1] = { 0 };
    size_t max_code_len = 0;
    for (size_t i = 0; i < code_count; ++i) {
        if (code_lens[i] > CYPDF_DEFLATE_CODE_LENGTH_MAX) {
            fprintf(stderr, "Huffman code length exceeds the limit: %zu > %u\n", code_lens[i], CYPDF_DEFLATE_CODE_LENGTH_MAX);
            return NULL;
        }
        ++code_len_freq[code_lens[i]];

        if (code_lens[i] > max_code_len) {
            max_code_len = code_lens[i];
        }
    }

    /* Determine lowest possible code for each code length. */
    uint16_t code = 0;
    uint16_t next_code[CYPDF_DEFLATE_CODE_LENGTH_MAX + 1] = { 0 };
    for (size_t bits = 1; bits <= CYPDF_DEFLATE_CODE_LENGTH_MAX; ++bits) {
        code = (uint16_t)((code + code_len_freq[bits - 1]) << 1);
        next_code[bits] = code;
    }

    /* Map Huffman codes to alphabet values. */
    uint16_t max_code = (uint16_t)(next_code[max_code_len] + (uint16_t)code_len_freq[max_code_len] - 1);
    uint16_t* huffman_tree = CYPDF_malloc((max_code + 1) * sizeof(uint16_t));
    *tree_size = max_code + 1;
    memset(huffman_tree, 0xFF, (max_code + 1) * sizeof(uint16_t));

    size_t curr_len = 0;
    for (size_t i = 0; i < code_count; ++i) {
        curr_len = code_lens[i];
        if (curr_len) {
            huffman_tree[next_code[curr_len]] = (uint16_t)i;
            ++next_code[curr_len];
        }
    }

    return huffman_tree;
}

static void ProcessLZ77(CYPDF_Inflate* const inflate, uint16_t code, const uint16_t* const dist_alphabet, const size_t* const dist_code_lens) {
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
        1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193, 257, 385, 513, 769, 1025, 1537, 2049, 3037, 4097, 6145, 8193, 12289, 16385, 24577, 0, 0
    };

    code -= 257;
    
    size_t lz77_len = 0;
    size_t i;
    for (i = 0; i < len_bits[code]; ++i) {
        lz77_len = lz77_len << 1 | (size_t)ConsumeBit(inflate);
    }
    lz77_len += len_base[code];

    uint16_t dist_code = GetNextCode(inflate, dist_alphabet, dist_code_lens);
    size_t lz77_dist = 0;
    for (i = 0; i < dist_bits[dist_code]; ++i) {
        lz77_dist = lz77_dist << 1 | ConsumeBit(inflate);
    }
    lz77_dist += dist_base[dist_code];

    for (i = 0; i < lz77_len; ++i) {
        AppendByte(inflate, inflate->inflated[inflate->inflated_len - lz77_dist]);
    }
}

static uint16_t GetNextCode(CYPDF_Inflate* const inflate, const uint16_t* const alphabet, const size_t* const code_lens) {
    uint16_t code = 0;
    size_t code_len = 0;
    do {
        code = code << 1 | ConsumeBit(inflate);
        ++code_len;
    } while (alphabet[code] == 0xFFFF || code_lens[alphabet[code]] != code_len);

    return alphabet[code];
}

static bool ConsumeBit(CYPDF_Inflate* const inflate) {
    inflate->bit_pos >>= 1;
    if (!inflate->bit_pos) {
        ++inflate->byte_pos;
        inflate->bit_pos = 0x80;
    }

    return inflate->bytes[inflate->byte_pos] & inflate->bit_pos;
}

static unsigned char ConsumeByte(CYPDF_Inflate* const inflate) {
    return inflate->bytes[inflate->byte_pos++];
}

static void AppendByte(CYPDF_Inflate* const inflate, const unsigned char byte) {
    if (inflate->inflated_len == inflate->inflated_size) {
        inflate->inflated_size *= 2;
        inflate->inflated = CYPDF_realloc(inflate->inflated, inflate->inflated_size * sizeof(unsigned char));
    }

    inflate->inflated[inflate->inflated_len] = byte;
    ++inflate->inflated_len;
}
