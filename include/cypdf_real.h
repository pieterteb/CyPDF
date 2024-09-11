#ifndef CYPDF_REAL_H
#define CYPDF_REAL_H


#include <stdbool.h>
#include <stdio.h>

#include "cypdf_object.h"
#include "cypdf_types.h"



#define CYPDF_PRINT_REAL                CYPDF_PrintReal
#define CYPDF_FREE_REAL                 CYPDF_FreeReal


typedef struct CYPDF_ObjReal {
    CYPDF_ObjHeader header;
    float           value;
} CYPDF_ObjReal;


/**
 * @brief Creates new CYPDF_Obj_Real initialized with value.
 * 
 * @param indirect 
 * @param ID 
 * @param value 
 * @return CYPDF_Obj_Real* | Returns NULL if object creation fails.
 */
CYPDF_ObjReal* CYPDF_NewReal(bool indirect, float value);

/**
 * @brief Writes obj to fp. Does nothing if fp == NULL or obj == NULL.
 * 
 * @param fp 
 * @param obj 
 */
void CYPDF_PrintReal(FILE* fp, CYPDF_Object* obj);

/**
 * @brief Frees obj. Does nothing if obj is NULL.
 * 
 * @param obj 
 */
void CYPDF_FreeReal(CYPDF_Object* obj);



#endif /* CYPDF_REAL_H */
