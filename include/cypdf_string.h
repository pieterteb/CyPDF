#ifndef CYPDF_STRING_H
#define CYPDF_STRING_H


#include <stdbool.h>
#include <stdio.h>

#include "cypdf_mmgr.h"
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
    char*                   val;
} CYPDF_ObjString;


CYPDF_ObjString* CPYDF_NewString(CYPDF_MMgr* const mmgr, const enum CYPDF_STRING_TYPE type, const char* restrict val);

char* CYPDF_GetString(const CYPDF_ObjString* const string);

void CYPDF_PrintString(FILE* restrict fp, const CYPDF_Object* const obj);

void CYPDF_FreeString(CYPDF_Object* obj);



#endif /* CYPDF_STRING_H */
