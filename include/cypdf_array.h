#ifndef CYPDF_ARRAY_H
#define CYPDF_ARRAY_H


#include <stdbool.h>
#include <stdio.h>

#include "cypdf_mmgr.h"
#include "cypdf_object.h"
#include "cypdf_types.h"



#define CYPDF_PRINT_ARRAY               CYPDF_PrintArray
#define CYPDF_FREE_ARRAY                CYPDF_FreeArray


typedef struct CYPDF_ObjArray {
    CYPDF_ObjHeader header;
    CYPDF_Object**  objs;
    size_t          obj_count;
} CYPDF_ObjArray;


CYPDF_ObjArray* CYPDF_NewArray(CYPDF_MMgr* const mmgr);

CYPDF_ObjArray* CYPDF_ArrayFromRect(CYPDF_MMgr* const mmgr, const CYPDF_Rect rect);

void CYPDF_ArrayAppend(CYPDF_ObjArray* const array, CYPDF_Object* const obj);

void CYPDF_PrintArray(FILE* restrict fp, const CYPDF_Object* const obj);

/**
 * @brief Frees obj. Does nothing if obj is NULL.
 * 
 * @param obj 
 */
void CYPDF_FreeArray(CYPDF_Object* obj);



#endif /* CYPDF_ARRAY_H */
