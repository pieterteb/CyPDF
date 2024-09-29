#ifndef CYPDF_TRAILER_H
#define CYPDF_TRAILER_H


#include <stddef.h>

#include "cypdf_doc.h"
#include "cypdf_print.h"



void CYPDF_PrintTrailer(CYPDF_Channel* const restrict channel, const CYPDF_Doc* const restrict pdf, const char* restrict file_path, const size_t xref_offset);



#endif /* CYPDF_TRAILER_H */
