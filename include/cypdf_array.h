#ifndef CYPDF_ARRAY_H
#define CYPDF_ARRAY_H


#include <stdio.h>

#include "cypdf_object.h"
#include "cypdf_types.h"



#define CYPDF_WRITE_ARRAY               CYPDF_Write_Array
#define CYPDF_FREE_ARRAY                CYPDF_Free_Array


/* CYPDF_Obj_Array struct */
typedef struct _CYPDF_Obj_Array {
    CYPDF_Obj_Header        header;
    CYPDF_Object**          objs;
    CYPDF_SIZE              obj_count;
} CYPDF_Obj_Array;


CYPDF_Obj_Array* CYPDF_New_Array(CYPDF_BOOL indirect);

CYPDF_Obj_Array* CYPDF_Array_From_Rect(CYPDF_Rect rect, CYPDF_BOOL indirect);

/**
 * @brief Appends obj to array.
 * 
 * @param array 
 * @param obj 
 */
void CYPDF_Array_Append(CYPDF_Obj_Array* array, CYPDF_Object* obj);

/**
 * @brief Writes obj to fp. Does nothing if fp == NULL or obj == NULL.
 * 
 * @param fp 
 * @param obj 
 */
void CYPDF_Write_Array(FILE* fp, CYPDF_Object* obj);

/**
 * @brief Frees obj. Does nothing if obj is NULL.
 * 
 * @param obj 
 */
void CYPDF_Free_Array(CYPDF_Object* obj);



#endif /* CYPDF_ARRAY_H */
