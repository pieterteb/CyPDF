#ifndef CYPDF_NUMBER_H
#define CYPDF_NUMBER_H


#include <stdbool.h>
#include <stdio.h>

#include "cypdf_object.h"



#define CYPDF_PRINT_NUMBER              CYPDF_PrintNumber
#define CYDPF_FREE_NUMBER               CYPDF_FreeNumber


typedef struct CYPDF_ObjNumber {
    CYPDF_ObjHeader header;
    int             val;
} CYPDF_ObjNumber;


CYPDF_ObjNumber* CYPDF_NewNumber(bool indirect, int val);

/**
 * @brief Writes obj to fp. Does nothing if fp == NULL or obj == NULL.
 * 
 * @param fp 
 * @param obj 
 */
void CYPDF_PrintNumber(FILE* fp, CYPDF_Object* obj);

/**
 * @brief Frees obj. Does nothing if obj is NULL.
 * 
 * @param obj 
 */
void CYPDF_FreeNumber(CYPDF_Object* obj);



#endif /* CYPDF_NUMBER_H */
