#ifndef CYPDF_STREAM_H
#define CYPDF_STREAM_H


#include <stdbool.h>
#include <stdio.h>

#include "cypdf_dict.h"



#define CYPDF_PRINT_STREAM                      CYPDF_PrintStream
#define CYPDF_FREE_STREAM                       CYPDF_FreeStream


typedef struct CYPDF_ObjStream {
    CYPDF_ObjHeader header;

    CYPDF_ObjDict*  dict;
    unsigned char*  val;
    size_t          val_size;
} CYPDF_ObjStream;


CYPDF_ObjStream* CYPDF_NewStream(const bool indirect);

void CYPDF_PrintToStream(CYPDF_ObjStream* const stream, const char format[restrict static 1], ...);

void CYPDF_PrintStream(FILE* restrict fp, CYPDF_Object* const obj);

void CYPDF_FreeStream(CYPDF_Object* const obj);



#endif /* CYPDF_STREAM_H */
