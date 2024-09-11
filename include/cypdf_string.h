#ifndef CYPDF_STRING_H
#define CYPDF_STRING_H


#include <stdbool.h>
#include <stdio.h>

#include "cypdf_object.h"



#define CYPDF_PRINT_STRING          CYPDF_PrintString
#define CYPDF_FREE_STRING           CYPDF_FreeString


enum CYPDF_STRING_TYPE {
    CYPDF_STRTYPE_STRING,           /* Beginning with PDF 1.7, this type is further qualified as ASCII string, PDFDocEncoded string, and byte string. */
    CYPDF_STRTYPE_TEXT,             /* Used for human-readable characters, such as text annotations, bookmark names, article names, and document information. */
    CYPDF_STRTYPE_ASCII,            /* Used for characters that are represented in a single byte using ASCII encoding. */
    CYPDF_STRTYPE_BYTE,             /* Used for binary data represented as a series of 8-bit bytes, where each byte can be any value representable in 8 bits. */

    CYPDF_STRTYPE_COUNT,
};


typedef struct CYPDF_StringObj {
    CYPDF_ObjHeader         header;

    enum CYPDF_STRING_TYPE  type;
    unsigned char*          value;
    size_t                  size;
} CYPDF_ObjString;


/**
 * @brief Creates new CYPDF_Obj_String initialized with value. If memory allocation for obj->value fails, obj->value is set to NULL and obj->size is set to 0.
 * 
 * @param indirect 
 * @param ID 
 * @param size
 * @param value 
 * @param valsize Size of value in bytes.
 * @return CYPDF_Obj_String* | Returns NULL if object creation fails.
 */
CYPDF_ObjString* CPYDF_NewString(bool indirect, enum CYPDF_STRING_TYPE type, unsigned char* value, size_t valsize);

/**
 * @brief Writes obj to fp. Does nothing if fp == NULL or obj == NULL.
 * 
 * @param fp 
 * @param obj 
 */
void CYPDF_PrintString(FILE* fp, CYPDF_Object* obj);

/**
 * @brief Frees obj. Does nothing if obj is NULL.
 * 
 * @param obj 
 */
void CYPDF_FreeString(CYPDF_Object* obj);



#endif /* CYPDF_STRING_H */
