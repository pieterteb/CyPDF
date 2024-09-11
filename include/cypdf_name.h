#ifndef CYPDF_NAME_H
#define CYPDF_NAME_H


#include <stdbool.h>
#include <stdio.h>

#include "cypdf_object.h"



#define CYPDF_TYPE_NAME                 "Type"


#define CYPDF_PRINT_NAME                CYPDF_PrintName
#define CYPDF_FREE_NAME                 CYPDF_FreeName


#define CYPDF_MAX_NAME_LEN              127


typedef struct CYPDF_ObjName {
    CYPDF_ObjHeader header;
    char            val[CYPDF_MAX_NAME_LEN + 1];
} CYPDF_ObjName;


/**
 * @brief Creates new CYPDF_ObjName initialized with value. If the length of value exceeds CYPDF_MAX_NAME_LEN, only the first CYPDF_MAX_NAME_LEN characters of value are used to initialize the CYPDF_ObjName.
 * 
 * @param indirect 
 * @param ID 
 * @param value 
 * @return CYPDF_ObjName* | Returns NULL if object creation fails.
 */
CYPDF_ObjName* CYPDF_NewName(bool indirect, const char* val);

/**
 * @brief Writes obj to fp. Does nothing if fp == NULL or obj == NULL.
 * 
 * @param fp 
 * @param obj 
 */
void CYPDF_PrintName(FILE* fp, CYPDF_Object* obj);

/**
 * @brief Frees obj. Does nothing if obj is NULL.
 * 
 * @param obj 
 */
void CYPDF_FreeName(CYPDF_Object* obj);



#endif /* CYPDF_NAME_H */
