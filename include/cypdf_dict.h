#ifndef CYPDF_DICT_H
#define CYPDF_DICT_H


#include <stdbool.h>
#include <stdio.h>

#include "cypdf_name.h"
#include "cypdf_object.h"
#include "cypdf_types.h"



#define CYPDF_PRINT_DICT                CYPDF_PrintDict
#define CYPDF_FREE_DICT                 CYPDF_FreeDict


typedef struct CYPDF_ObjDict {
    CYPDF_ObjHeader header;
    CYPDF_ObjName** keys;
    CYPDF_Object**  values;
    size_t          count;
} CYPDF_ObjDict;


CYPDF_ObjDict* CYPDF_NewDict(bool indirect);

/**
 * @brief Appends the key value pair to dict. Does nothing if dict is NULL.
 * 
 * @param dict 
 * @param key 
 * @param value 
 */
void CYPDF_DictAppend(CYPDF_ObjDict* dict, const char* key_name, CYPDF_Object* value);

/**
 * @brief Writes obj to fp. Does nothing if fp == NULL or obj == NULL.
 * 
 * @param fp 
 * @param dict 
 */
void CYPDF_PrintDict(FILE* fp, CYPDF_Object* obj);

/**
 * @brief Frees obj. Does nothing if obj is NULL.
 * 
 * @param obj 
 */
void CYPDF_FreeDict(CYPDF_Object* obj);



#endif /* CYPDF_DICT_H */
