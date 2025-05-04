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
    CYPDF_OBJECT_CLASS_REAL,
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
 *              Bit 0:      0,                  (!CYPDF_OBJECT_INDIRECT)
 *              Bit 1-23:   0,                  (CYPDF_OBJECT_NUMBER)
 *              Bit 24-39:  0,                  (CYPDF_GENERATION_NUMBER)
 *              Bit 40-45:  object_class,       (CYPDF_OBJECT_CLASS)
 *              Bit 46-51:  object_subclass.    (CYPDF_OBJECT_SUBCLASS)
 * 
 *  Indirect Object:
 *              Bit 0:      1,                  (CYPDF_OBJECT_INDIRECT)
 *              Bit 1-23:   object_number,      (CYPDF_OBJECT_NUMBER)
 *              Bit 24-39:  generation_number,  (CYPDF_GENERATION_NUMBER)
 *              Bit 40-45:  object_class,       (CYPDF_OBJECT_CLASS)
 *              Bit 46-51:  object_subclass.    (CYPDF_OBJECT_SUBCLASS)
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
 * Struct describing bool object.
 * 
 *      header:         as described above,
 *      value:          boolean value of the object.
 * 
 */
typedef struct CYPDF_ObjectBool {
    CYPDF_ObjectHeader          header;

    bool                        value;
} CYPDF_ObjectBool;

CYPDF_ObjectBool* CYPDF_object_bool_new(bool indirect, bool value);
void CYPDF_object_bool_free(CYPDF_ObjectBool* object_bool);
void CYPDF_object_bool_print(FILE* file_stream, CYPDF_ObjectBool* object_bool);


/* 
 * Struct describing integer object.
 * 
 *      header:         as described above,
 *      value:          integer value of the object.
 * 
 */
typedef struct CYPDF_ObjectInteger {
    CYPDF_ObjectHeader          header;

    int32_t                     value;
} CYPDF_ObjectInteger;

CYPDF_ObjectInteger* CYPDF_object_integer_new(bool indirect, int32_t value);
void CYPDF_object_integer_free(CYPDF_ObjectInteger* object_integer);
void CYPDF_object_integer_print(FILE* file_stream, CYPDF_ObjectInteger* object_integer);


/* 
 * Struct describing real object.
 * 
 *      header:         as described above,
 *      value:          floating point value of the object.
 * 
 */
typedef struct CYPDF_ObjectReal {
    CYPDF_ObjectHeader          header;

    float                       value;
} CYPDF_ObjectReal;

CYPDF_ObjectReal* CYPDF_object_real_new(bool indirect, float value);
void CYPDF_object_real_free(CYPDF_ObjectReal* object_real);
void CYPDF_object_real_print(FILE* file_stream, CYPDF_ObjectReal* object_real);


enum CYPDF_StringType {
    CYPDF_STRING_TYPE_ASCII_STRING = 0, /* UTF-16BE encoded string with a leading byte order marker. */
    CYPDF_STRING_TYPE_BYTE_STRING,      /* Used for binary data represented as a series of 8-bit bytes, where each byte can be any value representable in 8 bits. */
    CYPDF_STRING_TYPE_UTF_16BE_ENCODED, /* Used for characters that are represented in a single byte using ASCII encoding. */
    CYPDF_STRING_TYPE_PDF_DOC_ENCODED,  /* Used for characters and glyphs that are represented in a single byte, using PDFDocEncoding. */

    CYPDF_STRING_TYPE_COUNT,
};

#define CYPDF_STRING_TYPE_DEFAULT               CYPDF_STRING_TYPE_ASCII_STRING

enum CYPDF_StringFormat {
    CYPDF_STRING_FORMAT_LITERAL = 0,
    CYPDF_STRING_FORMAT_HEXADECIMAL,

    CYPDF_STRING_FORMAT_COUNT,
};

#define CYPDF_STRING_FORMAT_DEFAULT             CYPDF_STRING_FORMAT_LITERAL

/* 
 * Struct describing string object.
 * 
 *      header:         as described above,
 *      type:           type of string; determines how the string is interpreted,
 *      format:         determines how the string will be printed internally,
 *      bytes:          array of bytes,
 *      byte_count:     number of bytes in bytes.
 * 
 */
typedef struct CYPDF_ObjectString {
    CYPDF_ObjectHeader          header;

    enum CYPDF_StringType       type;
    enum CYPDF_StringFormat     format;
    uint8_t*                    bytes;
    unsigned                    byte_count;
} CYPDF_ObjectString;

CYPDF_ObjectString* CPYDF_object_string_new(bool indirect, enum CYPDF_StringType string_type, enum CYPDF_StringFormat string_format, const uint8_t* bytes, unsigned byte_count); /* Copies at most CYPDF_STRING_LENGTH_MAX bytes from bytes to the string object. */
void CYPDF_object_string_free(CYPDF_ObjectString* object_string);
void CYPDF_object_string_print(FILE* file_stream, CYPDF_ObjectString* object_string);


/* 
 * Struct describing name object.
 * 
 *      header:         as described above,
 *      value:          string containing non-delimeter and non-white-space characters.
 * 
 */
typedef struct CYPDF_ObjectName {
    CYPDF_ObjectHeader          header;

    char*                       value;
} CYPDF_ObjectName;

CYPDF_ObjectName* CYPDF_object_name_new(bool indirect, const char* restrict value); /* Copies at most CYPDF_NAME_LENGTH_MAX characters from value to the name object. */
void CYPDF_object_name_free(CYPDF_ObjectName* object_name);
void CYPDF_object_name_print(FILE* file_stream, CYPDF_ObjectName* object_name);


/* 
 * Struct describing array object.
 * 
 *      header:         as described above,
 *      objects:        array of objects,
 *      object_count:   number of objects in objects,
 *      size:           size in bytes of allocated memory.
 * 
 */
typedef struct CYPDF_ObjectArray {
    CYPDF_ObjectHeader          header;

    CYPDF_Object**              objects;
    size_t                      object_count;
    size_t                      size;
} CYPDF_ObjectArray;

CYPDF_ObjectArray* CYPDF_object_array_new(bool indirect);
void CYPDF_object_array_free(CYPDF_ObjectArray* object_array);
void CYPDF_obj_array_print(FILE* file_stream, CYPDF_ObjectArray* object_array);

void CYPDF_object_array_append(CYPDF_ObjectArray* object_array, CYPDF_Object* object);


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



#endif /* CYPDF_OBJECT_H */
