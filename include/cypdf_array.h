#ifndef CYPDF_ARRAY_H
#define CYPDF_ARRAY_H


#include <stdbool.h>
#include <stdio.h>

#include "cypdf_object.h"
#include "cypdf_types.h"



#define CYPDF_PRINT_ARRAY               CYPDF_PrintArray
#define CYPDF_FREE_ARRAY                CYPDF_FreeArray


typedef struct CYPDF_ObjArray {
    CYPDF_ObjHeader header;
    CYPDF_Object**  objs;
    size_t          obj_count;
} CYPDF_ObjArray;


CYPDF_ObjArray* CYPDF_NewArray(bool indirect);

CYPDF_ObjArray* CYPDF_ArrayFromRect(CYPDF_Rect rect, bool indirect);

/**
 * @brief Appends obj to array.
 * 
 * @param array 
 * @param obj 
 */
void CYPDF_ArrayAppend(CYPDF_ObjArray* array, CYPDF_Object* obj);

/**
 * @brief Writes obj to fp. Does nothing if fp == NULL or obj == NULL.
 * 
 * @param fp 
 * @param obj 
 */
void CYPDF_PrintArray(FILE* fp, CYPDF_Object* obj);

/**
 * @brief Frees obj. Does nothing if obj is NULL.
 * 
 * @param obj 
 */
void CYPDF_FreeArray(CYPDF_Object* obj);



#endif /* CYPDF_ARRAY_H */
