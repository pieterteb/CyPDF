#ifndef CYPDF_STRING_H
#define CYPDF_STRING_H


#include "cypdf_memory.h"
#include "cypdf_object.h"
#include "cypdf_print.h"
#include "cypdf_types.h"



#define CYPDF_FREE_STRING           CYPDF_FreeString
#define CYPDF_PRINT_STRING          CYPDF_PrintString


enum CYPDF_STRING_TYPE {
    CYPDF_STRTYPE_STRING,           /* Beginning with PDF 1.7, this type is further qualified as ASCII string, PDFDocEncoded string, and byte string. */
    CYPDF_STRTYPE_TEXT,             /* Used for human-readable characters, such as text annotations, bookmark names, article names, and document information. */
    CYPDF_STRTYPE_ASCII,            /* Used for characters that are represented in a single byte using ASCII encoding. */
    CYPDF_STRTYPE_BYTE,             /* Used for binary data represented as a series of 8-bit bytes, where each byte can be any value representable in 8 bits. */
};


typedef struct CYPDF_StringObj {
    CYPDF_ObjHeader         header;

    enum CYPDF_STRING_TYPE  type;
    char*                   value;
} CYPDF_ObjString;


CYPDF_ObjString* CPYDF_NewString(CYPDF_MemMgr* const restrict memmgr, const enum CYPDF_STRING_TYPE type, const char* restrict value);

void CYPDF_FreeString(CYPDF_Object* obj);

void CYPDF_PrintString(CYPDF_Channel* const restrict channel, const CYPDF_Object* const obj);


char* CYPDF_StringGet(const CYPDF_ObjString* const restrict string);



#endif /* CYPDF_STRING_H */
