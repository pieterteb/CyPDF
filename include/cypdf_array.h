#ifndef CYPDF_ARRAY_H
#define CYPDF_ARRAY_H


#include <stddef.h>

#include "cypdf_memmgr.h"
#include "cypdf_object.h"
#include "cypdf_print.h"
#include "cypdf_types.h"



#define CYPDF_FREE_ARRAY    CYPDF_FreeArray
#define CYPDF_PRINT_ARRAY   CYPDF_PrintArray


typedef struct CYPDF_ObjArray {
    CYPDF_ObjHeader header;

    CYPDF_Object**  objs;
    size_t          obj_count;

    CYPDF_MemMgr*   memmgr;
} CYPDF_ObjArray;


CYPDF_ObjArray* CYPDF_NewArray(CYPDF_MemMgr* const restrict memmgr);

void CYPDF_FreeArray(CYPDF_Object* obj);

void CYPDF_PrintArray(CYPDF_Channel* const restrict channel, const CYPDF_Object* const obj);


void CYPDF_ArrayAppend(CYPDF_ObjArray* const restrict array, CYPDF_Object* const restrict obj);

CYPDF_ObjArray* CYPDF_ArrayFromRect(CYPDF_MemMgr* const restrict memmgr, const CYPDF_Rect rect);



#endif /* CYPDF_ARRAY_H */
