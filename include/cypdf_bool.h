#ifndef CYPDF_BOOL_H
#define CYPDF_BOOL_H


#include <stdbool.h>
#include <stdio.h>

#include "cypdf_object.h"



#define CYPDF_PRINT_BOOL            CYPDF_PrintBool
#define CYPDF_FREE_BOOL             CYPDF_FreeBool


typedef struct CYPDF_ObjBool {
    CYPDF_ObjHeader header;
    bool            val;
} CYPDF_ObjBool;


CYPDF_ObjBool* CYPDF_NewBool(bool indirect, bool val);

/**
 * @brief Writes obj to fp. Does nothing if fp == NULL or obj == NULL.
 * 
 * @param fp 
 * @param obj 
 */
void CYPDF_PrintBool(FILE* fp, CYPDF_Object* obj);

/**
 * @brief Frees obj. Does nothing if obj is NULL.
 * 
 * @param obj 
 */
void CYPDF_FreeBool(CYPDF_Object* obj);



#endif /* CYPDF_BOOL_H */
