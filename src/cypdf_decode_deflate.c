#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "cypdf_decode_deflate.h"
#include "cypdf_log.h"
#include "cypdf_memory.h"



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
