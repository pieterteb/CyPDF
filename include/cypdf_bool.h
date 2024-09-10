#ifndef CYPDF_BOOL_H
#define CYPDF_BOOL_H


#include <stdio.h>

#include "cypdf_object.h"
#include "cypdf_types.h"



#define CYPDF_WRITE_BOOL            CYPDF_Write_Bool
#define CYPDF_FREE_BOOL             CYPDF_Free_Bool


/* CYPDF_Obj_Bool struct */
typedef struct _CYPDF_Obj_Bool {
    CYPDF_Obj_Header        header;
    CYPDF_BOOL              value;
} CYPDF_Obj_Bool;


CYPDF_Obj_Bool* CYPDF_New_Bool(CYPDF_BOOL indirect, CYPDF_BOOL val);

/**
 * @brief Writes obj to fp. Does nothing if fp == NULL or obj == NULL.
 * 
 * @param fp 
 * @param obj 
 */
void CYPDF_Write_Bool(FILE* fp, CYPDF_Object* obj);

/**
 * @brief Frees obj. Does nothing if obj is NULL.
 * 
 * @param obj 
 */
void CYPDF_Free_Bool(CYPDF_Object* obj);



#endif /* CYPDF_BOOL_H */
