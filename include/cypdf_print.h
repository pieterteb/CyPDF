#ifndef CYPDF_PRINT_H
#define CYPDF_PRINT_H


#include <stdio.h>

#include "cypdf_types.h"



/**
 * @brief Writes buffer followed by an end of line sequence to stream.
 * 
 * @param buffer 
 * @param element_size 
 * @param element_count 
 * @param stream 
 * @return size_t | Returns the amount of bytes successfully written.
 */
size_t CYPDF_fwrite_NL(const void* buffer, size_t element_size, size_t element_count, FILE* stream);

size_t CYPDF_Write_NL(FILE* fp);

/**
 * @brief Behaves like fprintf but appends the newline sequence to the printed chars. If format is NULL, only the newline sequence is printed.
 * 
 * @param fp 
 * @param format 
 * @param ... 
 * @return int | The amount of characters printed.
 */
int CYPDF_fprintf_NL(FILE* fp, const char* format, ...);

/**
 * @brief Behaves like sprintf but appends the newline sequence to the printed chars. If format is NULL, only the newline sequence is printed.
 * 
 * @param dest 
 * @param format 
 * @param ... 
 * @return int | The amount of characters printed.
 */
int CYPDF_sprintf_NL(char* dest, const char* format, ...);

/**
 * @brief Writes src as a comment to fp.
 * 
 * @param fp 
 * @param src 
 * @return size_t | Returns the amount of bytes successfully written.
 */
size_t CYPDF_Write_Comment(FILE* fp, const char* src);



#endif /* CYPDF_PRINT_H */
