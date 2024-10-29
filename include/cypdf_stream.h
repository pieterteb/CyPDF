#ifndef CYPDF_STREAM_H
#define CYPDF_STREAM_H


#include <stdarg.h>
#include <stddef.h>

#include "cypdf_dict.h"
#include "cypdf_memory.h"
#include "cypdf_object.h"
#include "cypdf_print.h"
#include "cypdf_types.h"



#define CYPDF_FREE_STREAM   CYPDF_FreeStream
#define CYPDF_PRINT_STREAM  CYPDF_PrintStream


typedef struct CYPDF_ObjStream {
    CYPDF_ObjHeader header;

    unsigned char*  bytes;
    size_t          length;

    CYPDF_ObjDict*  dict;
} CYPDF_ObjStream;


CYPDF_ObjStream* CYPDF_NewStream(CYPDF_MemMgr* const memmgr);

void CYPDF_FreeStream(CYPDF_Object* obj);

void CYPDF_PrintStream(CYPDF_Channel* const channel, const CYPDF_Object* const obj);


int CYPDF_PrintToStream(CYPDF_ObjStream* const restrict stream, const char format[restrict static 1], va_list args);

size_t CYPDF_WriteToStream(CYPDF_ObjStream* const restrict stream, const void* restrict buffer, const size_t size, size_t count);



#endif /* CYPDF_STREAM_H */
