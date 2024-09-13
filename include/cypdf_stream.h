#ifndef CYPDF_STREAM_H
#define CYPDF_STREAM_H


#include <stdbool.h>
#include <stdio.h>

#include "cypdf_dict.h"
#include "cypdf_mmgr.h"
#include "cypdf_number.h"
#include "cypdf_object.h"
#include "cypdf_types.h"



#define CYPDF_PRINT_STREAM                      CYPDF_PrintStream
#define CYPDF_FREE_STREAM                       CYPDF_FreeStream


typedef struct CYPDF_ObjStream {
    CYPDF_ObjHeader header;

    CYPDF_ObjDict*      dict;
    unsigned char*      bytes;
    CYPDF_ObjNumber*    length;
} CYPDF_ObjStream;


CYPDF_ObjStream* CYPDF_NewStream(CYPDF_MMgr* const mmgr);

void CYPDF_PrintToStream(CYPDF_ObjStream* const stream, const char format[restrict static 1], ...);

void CYPDF_PrintStream(FILE* restrict fp, const CYPDF_Object* const obj);

void CYPDF_FreeStream(CYPDF_Object* obj);



#endif /* CYPDF_STREAM_H */
