#ifndef CYPDF_STREAM_H
#define CYPDF_STREAM_H


#include <stdio.h>

#include "cypdf_dict.h"
#include "cypdf_types.h"



#define CYPDF_WRITE_STREAM                      CYPDF_Write_Stream
#define CYPDF_FREE_STREAM                       CYPDF_Free_Stream


/* CYPDF_Obj_Stream struct */
typedef struct _CYPDF_Obj_Stream {
    CYPDF_Obj_Header        header;

    CYPDF_Obj_Dict*         dict;
    CYPDF_BYTE*             val;
    CYPDF_SIZE              val_size;
} CYPDF_Obj_Stream;


CYPDF_Obj_Stream* CYPDF_New_Stream(CYPDF_BOOL indirect, CYPDF_UINT32 onum);

/**
 * @brief Writes a CYPDF_BYTE array to stream->val.
 * 
 * @param stream 
 * @param val 
 * @param val_size 
 */
void CYPDF_Write_To_Stream(CYPDF_Obj_Stream* stream, CYPDF_BYTE* val, CYPDF_SIZE val_size);

void CYPDF_Write_Stream(FILE* fp, CYPDF_Object* obj);

void CYPDF_Free_Stream(CYPDF_Object* obj);



#endif /* CYPDF_STREAM_H */
