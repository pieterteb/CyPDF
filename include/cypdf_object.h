#ifndef CYPDF_OBJECT_H
#define CYPDF_OBJECT_H


#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "cypdf_print.h"
#include "cypdf_types.h"



typedef void CYPDF_Object;


enum CYPDF_ObjectClass {
    CYPDF_OBJECT_CLASS_NULL = 0,
    CYPDF_OBJECT_CLASS_BOOL,
    CYPDF_OBJECT_CLASS_INTEGER,
    CYPDF_OBJECT_CLASS_NUMBER,
    CYPDF_OBJECT_CLASS_STRING,
    CYPDF_OBJECT_CLASS_NAME,
    CYPDF_OBJECT_CLASS_ARRAY,
    CYPDF_OBJECT_CLASS_DICT,
    CYPDF_OBJECT_CLASS_STREAM,
    CYPDF_OBJECT_CLASS_PAGE,

    CYPDF_OBJECT_CLASS_COUNT,
};

enum CYPDF_ObjectSubclass {
    CYPDF_OBJECT_SUBCLASS_NONE = 0,
    CYPDF_OBJECT_SUBCLASS_INFO,
    CYPDF_OBJECT_SUBCLASS_CATALOG,
    CYPDF_OBJECT_SUBCLASS_PAGE,
    CYPDF_OBJECT_SUBCLASS_PAGE_NODE,
    CYPDF_OBJECT_SUBCLASS_GFX_STATE,
    CYPDF_OBJECT_SUBCLASS_RESOURCES,
    CYPDF_OBJECT_SUBCLASS_XOBJECT,

    CYPDF_OBJECT_SUBCLASS_COUNT,
};


/* Masks and default values for object header elements. */
#define CYPDF_OBJECT_INDIRECT                   (uint64_t)0x0000000000000001

#define CYPDF_OBJECT_NUMBER                     (uint64_t)0x0000000000FFFFFE
#define CYPDF_OBJECT_NUMBER_DEFAULT             (unsigned)0

#define CYPDF_GENERATION_NUMBER                 (uint64_t)0x000000FFFF000000
#define CYPDF_GENERATION_NUMBER_DEFAULT         (unsigned)0

#define CYPDF_OBJECT_CLASS                      (uint64_t)0x00003F0000000000
#define CYPDF_OBJECT_CLASS_DEFAULT              (unsigned)CYPDF_OBJECT_CLASS_NULL

#define CYPDF_OBJECT_SUBCLASS                   (uint64_t)0x000FC00000000000
#define CYPDF_OBJECT_SUBCLASS_DEFAULT           (unsigned)CYPDF_OBJECT_SUBCLASS_NONE


typedef uint64_t CYPDF_ObjectHeader;

/*
 * Structures defining PDF objects. Each object has a header defined as follows.
 * Bits not explicitly described contain zeroes:
 * 
 *  Direct Object:
 *              Bit 0:      0                   (!CYPDF_OBJECT_INDIRECT)
 *              Bit 1-23:   0                   (CYPDF_OBJECT_NUMBER)
 *              Bit 24-39:  0                   (CYPDF_GENERATION_NUMBER)
 *              Bit 40-45:  object_class        (CYPDF_OBJECT_CLASS)
 *              Bit 46-51:  object_subclass     (CYPDF_OBJECT_SUBCLASS)
 * 
 *  Indirect Object:
 *              Bit 0:      1                   (CYPDF_OBJECT_INDIRECT)
 *              Bit 1-23:   object_number       (CYPDF_OBJECT_NUMBER)
 *              Bit 24-39:  generation_number   (CYPDF_GENERATION_NUMBER)
 *              Bit 40-45:  object_class        (CYPDF_OBJECT_CLASS)
 *              Bit 46-51:  object_subclass     (CYPDF_OBJECT_SUBCLASS)
 * 
 */


/* 
 * Struct describing null object.
 */
typedef struct CYPDF_ObjectNull {
    CYPDF_ObjectHeader          header;
} CYPDF_ObjectNull;

CYPDF_ObjectNull* CYPDF_object_null_new(bool indirect);
void CYPDF_object_null_free(CYPDF_ObjectNull* object_null);
void CYPDF_object_null_print(FILE* file_stream, CYPDF_ObjectNull* object_null __attribute_maybe_unused__);


/* 
 * Struct describing null object.
 */
typedef struct CYPDF_ObjectInteger {
    CYPDF_ObjectHeader          header;
    int32_t                     value;
} CYPDF_ObjectInteger;


/* Object header setters. */
void CYPDF_object_set_indirect(CYPDF_Object* object);
void CYPDF_object_set_object_number(CYPDF_Object* object, unsigned object_number);
void CYPDF_object_set_generation_number(CYPDF_Object* object, unsigned generation_number);
void CYPDF_object_set_class(CYPDF_Object* object, enum CYPDF_ObjectClass object_class);
void CYPDF_object_set_subclass(CYPDF_Object* object, enum CYPDF_ObjectSubclass object_subclass);

/* Object header getters. */
bool CYPDF_object_is_indirect(CYPDF_Object* object);
unsigned CYPDF_object_get_object_number(CYPDF_Object* object);
unsigned CYPDF_object_get_generation_number(CYPDF_Object* object);
enum CYPDF_ObjectClass CYPDF_object_get_object_class(CYPDF_Object* object);
enum CYPDF_ObjectSubclass CYPDF_object_get_object_subclass(CYPDF_Object* object)


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
