#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "cypdf_decode_deflate.h"
#include "cypdf_log.h"
#include "cypdf_memory.h"



typedef struct CYPDF_Inflate {
    const unsigned char*    bytes;
    size_t                  size;
    size_t                  byte_pos;
    unsigned char           bit_pos;

    unsigned char*          decompressed;
    size_t                  decompressed_length;
    size_t                  decompressed_size;
} CYPDF_Inflate;


static void DecompressedAppend(CYPDF_Inflate* restrict const inflate, const unsigned char* restrict const source, const size_t length);

static uint16_t* BuildHuffmanTree(const size_t* const code_length, const size_t code_count, size_t* const tree_size);

static int ConsumeBit(CYPDF_Inflate* const bit_stream);

static int ConsumeByte(CYPDF_Inflate* const bit_stream);  


unsigned char* CYPDF_DecodeDeflate(const unsigned char* const source, const size_t size) {
    if (!source) {
        return NULL;
    }

    CYPDF_Inflate inflate = {
        .bytes = source,
        .size = size,
        .byte_pos = 0,
        .bit_pos = 0x80,
        .decompressed = CYPDF_malloc(1024 * sizeof(unsigned char)),
        .decompressed_length = 0,
        .decompressed_size = 1024
    };

    /* Process blocks. */
    bool final = false;
    do {
        final = ConsumeBit(&inflate);
        if (ConsumeBit(&inflate)) {          /* Compressed with Dynamic Huffman Codes */
            ConsumeBit(&inflate);

        } else if (ConsumeBit(&inflate)) {   /* Compressed with Fixed Huffman Codes */

        } else {                            /* No Compression */
            BlockUncompressed(&inflate);
        }
    } while (!final);

    return inflate.decompressed;
}

static void BlockUncompressed(CYPDF_Inflate* const inflate) {
    if (inflate->bit_pos != 0x80) {
        ConsumeByte(inflate);
    }

    size_t length = ConsumeByte(inflate);
    ConsumeByte(inflate);                   /* Consume NLEN byte. */
    for (size_t i = 0; i < length; ++i) {
        AppendByte(inflate, ConsumeByte(inflate));
    }
}

static void AppendByte(CYPDF_Inflate* const inflate, const unsigned char byte) {
    if (inflate->decompressed_length == inflate->decompressed_size) {
        inflate->decompressed_size *= 2;
        inflate->decompressed = CYPDF_realloc(inflate->decompressed, inflate->decompressed_size * sizeof(unsigned char));
    }

    inflate->decompressed[inflate->decompressed_length] = byte;
    ++inflate->decompressed_length;
}

static uint16_t* BuildHuffmanTree(const size_t* const code_length, const size_t code_count, size_t* const tree_size) {
    size_t code_length_frequency[CYPDF_DEFLATE_CODE_LENGTH_MAX + 1] = { 0 };
    size_t max_code_length = 0;
    for (size_t i = 0; i < code_count; ++i) {
        if (code_length[i] > CYPDF_DEFLATE_CODE_LENGTH_MAX) {
            fprintf(stderr, "Huffman code length exceeds the limit: %zu > %u\n", code_length[i], CYPDF_DEFLATE_CODE_LENGTH_MAX);
            return NULL;
        }
        ++code_length_frequency[code_length[i]];

        if (code_length[i] > max_code_length) {
            max_code_length = code_length[i];
        }
    }

    /* Determine lowest possible code for each code length. */
    uint16_t code = 0;
    uint16_t next_code[CYPDF_DEFLATE_CODE_LENGTH_MAX + 1] = { 0 };
    for (size_t bits = 1; bits <= CYPDF_DEFLATE_CODE_LENGTH_MAX; ++bits) {
        code = (uint16_t)((code + code_length_frequency[bits - 1]) << 1);
        next_code[bits] = code;
    }

    /* Map Huffman codes to alphabet values. */
    uint16_t max_code = (uint16_t)(next_code[max_code_length] + (uint16_t)code_length_frequency[max_code_length] - 1);
    uint16_t* huffman_tree = CYPDF_malloc((max_code + 1) * sizeof(uint16_t));
    *tree_size = max_code + 1;
    memset(huffman_tree, 0xFF, (max_code + 1) * sizeof(uint16_t));

    size_t curr_length = 0;
    for (size_t i = 0; i < code_count; ++i) {
        curr_length = code_length[i];
        huffman_tree[next_code[curr_length]] = (uint16_t)i;
        ++next_code[curr_length];
    }

    return huffman_tree;
}

static int ConsumeBit(CYPDF_Inflate* const inflate) {
    inflate->bit_pos >>= 1;
    if (!inflate->bit_pos) {
        ++inflate->byte_pos;
        if (inflate->byte_pos == inflate->size) {
            return -1;
        }
        inflate->bit_pos = 0x80;
    }

    return inflate->bytes[inflate->byte_pos] & inflate->bit_pos;
}

static int ConsumeByte(CYPDF_Inflate* const inflate) {
    if (inflate->byte_pos == inflate->size) {
        return -1;
    }

    return inflate->bytes[inflate->byte_pos++];
}
