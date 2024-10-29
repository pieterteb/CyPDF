#ifndef CYPDF_OBJECT_H
#define CYPDF_OBJECT_H


#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "cypdf_memory.h"
#include "cypdf_print.h"
#include "cypdf_types.h"



enum CYPDF_OBJ_CLASS {
    CYPDF_OBJ_CLASS_UNKNOWN = 0,

    CYPDF_OBJ_CLASS_NULL,
    CYPDF_OBJ_CLASS_BOOL,
    CYPDF_OBJ_CLASS_INTEGER,
    CYPDF_OBJ_CLASS_NUMBER,
    CYPDF_OBJ_CLASS_STRING,
    CYPDF_OBJ_CLASS_NAME,
    CYPDF_OBJ_CLASS_ARRAY,
    CYPDF_OBJ_CLASS_DICT,
    CYPDF_OBJ_CLASS_STREAM,        /* A stream is always an indirect object. */
};

enum CYPDF_OBJ_SUBCLASS {
    CYPDF_OBJ_SUBCLASS_UNKNOWN = 0,

    CYPDF_OBJ_SUBCLASS_NONE,
    CYPDF_OBJ_SUBCLASS_INFO,
    CYPDF_OBJ_SUBCLASS_CATALOG,
    CYPDF_OBJ_SUBCLASS_PAGE,
    CYPDF_OBJ_SUBCLASS_PAGE_NODE,
    CYPDF_OBJ_SUBCLASS_GFX_STATE,
    CYPDF_OBJ_SUBCLASS_RESOURCES,
};


#define CYPDF_DEFAULT_OBJ_NUM       0x00000000          /* Used for direct objects. */
#define CYPDF_DEFAULT_OBJ_GEN       0x0000
#define CYPDF_DEFAULT_OBJ_CLASS     CYPDF_OBJ_CLASS_NULL
#define CYPDF_DEFAULT_OBJ_SUBCLASS  CYPDF_OBJ_SUBCLASS_NONE


typedef struct CYPDF_ObjHeader {
    uint64_t    indirect    : 1;
    uint64_t    class       : 8;
    uint64_t    subclass    : 8;
    uint64_t    obj_num     : 23;
    uint64_t    obj_gen     : 16;
    uint64_t    reserved    : 8;
} CYPDF_ObjHeader;


void CYPDF_FreeObj(CYPDF_Object* obj);

void CYPDF_PrintObjDirect(CYPDF_Channel* const restrict channel, const CYPDF_Object* const obj);

void CYPDF_PrintObjDef(CYPDF_Channel* const restrict channel, const CYPDF_Object* const obj);

void CYPDF_PrintObjRef(CYPDF_Channel* const restrict channel, const CYPDF_Object* const obj);


bool CYPDF_ObjIsIndirect(const CYPDF_Object* const obj);

enum CYPDF_OBJ_CLASS CYPDF_ObjGetClass(const CYPDF_Object* const obj);

enum CYPDF_OBJ_SUBCLASS CYPDF_ObjGetSubclass(const CYPDF_Object* const obj);

uint32_t CYPDF_ObjGetObjNum(const CYPDF_Object* const obj);

uint16_t CYPDF_ObjGetObjGen(const CYPDF_Object* const obj);



#endif /* CYPDF_OBJECT_H */
