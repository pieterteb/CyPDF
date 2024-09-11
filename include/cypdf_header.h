#ifndef CYPDF_HEADER_H
#define CYPDF_HEADER_H


#include <stdio.h>

#include "cypdf_types.h"
#include "cypdf_version.h"



#define CYPDF_HIVAL_BYTES       "\x80\x81\x82\x83"


typedef struct CYPDF_FileHeader {
    char    version[sizeof(CYPDF_PDF_VERSION)];
    char    hival_bytes[sizeof(CYPDF_HIVAL_BYTES)];
} CYPDF_FileHeader;


/**
 * @brief Creates new CYPDF_FileHeader.
 * 
 * @return CYPDF_FileHeader* | Returns NULL if memory allocation fails.
 */
CYPDF_FileHeader* CYPDF_NewFileHeader();

/**
 * @brief Writes file_header to fp. Does nothing if fp == NULL or file_header == NULL.
 * 
 * @param fp 
 * @param file_header 
 */
void CYPDF_PrintFileHeader(FILE* fp, CYPDF_FileHeader* file_header);

/**
 * @brief Frees file_header. Does nothing if file_header is NULL.
 * 
 * @param file_header 
 */
void CYPDF_FreeFileHeader(CYPDF_FileHeader* file_header);



#endif /* CYPDF_HEADER_H */
