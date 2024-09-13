#ifndef CYPDF_OBJECT_H
#define CYPDF_OBJECT_H


#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "cypdf_mmgr.h"
#include "cypdf_types.h"



enum CYPDF_OCLASS {
    CYPDF_OCLASS_NULL = 0,
    CYPDF_OCLASS_BOOL,
    CYPDF_OCLASS_NUMBER,
    CYPDF_OCLASS_REAL,
    CYPDF_OCLASS_STRING,
    CYPDF_OCLASS_NAME,
    CYPDF_OCLASS_ARRAY,
    CYPDF_OCLASS_DICT,
    CYPDF_OCLASS_STREAM,        /* A stream is always an indirect object. */

    CYPDF_OCLASS_INFO,
    CYPDF_OCLASS_CATALOG,
    CYPDF_OCLASS_PAGE,
    CYPDF_OCLASS_PNODE,

    CYPDF_OCLASS_COUNT,

    CYPDF_OCLASS_UNKNOWN
};


#define CYPDF_DEFAULT_ONUM              0x00000000          /* Used for direct objects. */
#define CYPDF_DEFAULT_OGEN              0x0000


typedef struct CYPDF_ObjHeader {
    bool                indirect;
    enum CYPDF_OCLASS   class;
    uint32_t            onum;
    uint16_t            ogen;
} CYPDF_ObjHeader;


void CYPDF_InitHeader(CYPDF_Object* const obj, enum CYPDF_OCLASS class);

void CYPDF_ObjSetOnum(CYPDF_Object* const obj, uint32_t onum);

void CYPDF_ObjSetIndirect(CYPDF_Object* const obj, const bool indirect);

bool CYPDF_ObjIsIndirect(const CYPDF_Object* const obj);

enum CYPDF_OCLASS CYPDF_ObjGetClass(const CYPDF_Object* const obj);

uint32_t CYPDF_ObjGetOnum(const CYPDF_Object* const obj);

uint16_t CYPDF_ObjGetOgen(const CYPDF_Object* const obj);

CYPDF_PrintFunc CYPDF_ObjGetPrint(const CYPDF_Object* const obj);

CYPDF_FreeFunc CYPDF_ObjGetFree(const CYPDF_Object* const obj);

void CYPDF_PrintObjDirect(FILE* restrict fp, const CYPDF_Object* const obj);

void CYPDF_PrintObjDef(FILE* restrict fp, const CYPDF_Object* const obj);

void CYPDF_PrintObjRef(FILE* restrict fp, const CYPDF_Object* const obj);

void CYPDF_FreeObj(CYPDF_Object* obj);



#endif /* CYPDF_OBJECT_H */
