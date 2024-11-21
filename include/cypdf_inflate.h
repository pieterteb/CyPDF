/*
https://datatracker.ietf.org/doc/html/rfc1951#section-7
*/

#ifndef CYPDF_DECODE_DEFLATE_H
#define CYPDF_DECODE_DEFLATE_H


#include <stddef.h>



#define CYPDF_DEFLATE_CODE_LENGTH_MAX       15
#define CYPDF_DEFLATE_UNKNOWN_CODE          0xFFFF


unsigned char* CYPDF_ZLibUncompress(const unsigned char* restrict const source, const size_t length, size_t* restrict const inflated_length);

unsigned char* CYPDF_Inflate(const unsigned char* restrict const source, const size_t length, size_t* restrict const inflated_length);



#endif /* CYPDF_DEOCDE_DEFLATE_H */
