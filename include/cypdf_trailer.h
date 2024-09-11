#ifndef CYPDF_TRAILER_H
#define CYPDF_TRAILER_H


#include <stdint.h>
#include <stdio.h>

#include "cypdf_doc.h"



/**
 * @brief Writes a trailer to pdf.
 * 
 * @param fp 
 * @param pdf 
 * @param file_path 
 * @param xref_offset 
 */
void CYPDF_PrintTrailer(FILE* fp, CYPDF_Doc* pdf, const char* file_path, uint64_t xref_offset);



#endif /* CYPDF_TRAILER_H */
