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


CYPDF_ObjStream* CYPDF_NewStream(bool indirect);

/**
 * @brief Writes a CYPDF_BYTE array to stream->val.
 * 
 * @param stream 
 * @param val 
 * @param val_size 
 */
void CYPDF_PrintToStream(CYPDF_ObjStream* stream, unsigned char* val, size_t val_size);

void CYPDF_PrintStream(FILE* fp, CYPDF_Object* obj);

void CYPDF_FreeStream(CYPDF_Object* obj);



#endif /* CYPDF_STREAM_H */
