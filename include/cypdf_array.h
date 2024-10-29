#ifndef CYPDF_ARRAY_H
#define CYPDF_ARRAY_H


#include <stddef.h>

#include "cypdf_list.h"
#include "cypdf_memory.h"
#include "cypdf_object.h"
#include "cypdf_print.h"
#include "cypdf_types.h"



#define CYPDF_FREE_ARRAY    CYPDF_FreeArray
#define CYPDF_PRINT_ARRAY   CYPDF_PrintArray


typedef struct CYPDF_ObjArray {
    CYPDF_ObjHeader header;

    CYPDF_List*     obj_list;

    CYPDF_MemMgr*   memmgr;
} CYPDF_ObjArray;


CYPDF_ObjArray* CYPDF_NewArray(CYPDF_MemMgr* const restrict memmgr);

void CYPDF_FreeArray(CYPDF_Object* obj);

void CYPDF_PrintArray(CYPDF_Channel* const restrict channel, const CYPDF_Object* const obj);


void CYPDF_ArrayAppend(CYPDF_ObjArray* const restrict array, CYPDF_Object* const restrict obj);

CYPDF_ObjArray* CYPDF_ArrayFromRect(CYPDF_MemMgr* const restrict memmgr, const CYPDF_Rect rect);

CYPDF_ObjArray* CYPDF_ArrayFromIntArray(CYPDF_MemMgr* const restrict memmgr, const int* const arr, const size_t count);

CYPDF_Object* CYPDF_ArrayAtIndex(CYPDF_ObjArray* const array, const size_t index);

size_t CYPDF_ArrayLength(CYPDF_ObjArray* const array);



#endif /* CYPDF_ARRAY_H */
