#include <stdbool.h>
#include <stdint.h>

#include "cypdf_object.h"
#include "cypdf_array.h"
#include "cypdf_bool.h"
#include "cypdf_consts.h"
#include "cypdf_dict.h"
#include "cypdf_integer.h"
#include "cypdf_log.h"
#include "cypdf_name.h"
#include "cypdf_null.h"
#include "cypdf_number.h"
#include "cypdf_print.h"
#include "cypdf_stream.h"
#include "cypdf_string.h"
#include "cypdf_types.h"



void CYPDF_FreeObj(CYPDF_Object* obj) {
    CYPDF_TRACE;

    if (obj) {
        CYPDF_FreeFunc free_func = NULL;

        switch (CYPDF_ObjGetClass(obj))
        {
        case CYPDF_OBJ_CLASS_STRING:
            free_func = CYPDF_FREE_STRING;
            break;
        case CYPDF_OBJ_CLASS_ARRAY:
            free_func = CYPDF_FREE_ARRAY;
            break;
        case CYPDF_OBJ_CLASS_DICT:
            free_func = CYPDF_FREE_DICT;
            break;
        case CYPDF_OBJ_CLASS_STREAM:
            free_func = CYPDF_FREE_STREAM;
            break;
        default:
            free_func = CYPDF_FREE_NULL;
            break;
        }

        free_func(obj);
    }
}

void CYPDF_PrintObjDirect(CYPDF_Channel* const restrict channel, const CYPDF_Object* const obj) {
    CYPDF_TRACE;

    if (obj) {
        CYPDF_PrintFunc print_func = NULL;

        switch (CYPDF_ObjGetClass(obj))
        {
        case CYPDF_OBJ_CLASS_BOOL:
            print_func = CYPDF_PRINT_BOOL;
            break;
        case CYPDF_OBJ_CLASS_INTEGER:
            print_func = CYPDF_PRINT_INTEGER;
            break;
        case CYPDF_OBJ_CLASS_NUMBER:
            print_func = CYPDF_PRINT_NUMBER;
            break;
        case CYPDF_OBJ_CLASS_STRING:
            print_func = CYPDF_PRINT_STRING;
            break;
        case CYPDF_OBJ_CLASS_NAME:
            print_func = CYPDF_PRINT_NAME;
            break;
        case CYPDF_OBJ_CLASS_ARRAY:
            print_func = CYPDF_PRINT_ARRAY;
            break;
        case CYPDF_OBJ_CLASS_DICT:
            print_func = CYPDF_PRINT_DICT;
            break;
        case CYPDF_OBJ_CLASS_STREAM:
            print_func = CYPDF_PRINT_STREAM;
            break;
        default:
            print_func = CYPDF_PRINT_NULL;
            break;
        }

        print_func(channel, obj);
    }
}

void CYPDF_PrintObjDef(CYPDF_Channel* const restrict channel, const CYPDF_Object* const obj) {
    CYPDF_TRACE;

    if (channel && obj) {
        /* If the object itself is not indirect, it cannot be written indirectly. 
        This is because it's onum and ogen would be invalid. */
        if (CYPDF_ObjIsIndirect(obj)) {
            CYPDF_ChannelPrintLine(channel, "%u %hu obj", CYPDF_ObjGetObjNum(obj), CYPDF_ObjGetObjGen(obj));
            CYPDF_PrintObjDirect(channel, obj);
            CYPDF_ChannelPrintNL(channel);
            CYPDF_ChannelPrintLine(channel, "endobj");
        }
    }
}

void CYPDF_PrintObjRef(CYPDF_Channel* const restrict channel, const CYPDF_Object* const obj) {
    CYPDF_TRACE;

    if (channel && obj) {
        /* If the object itself is not indirect, it cannot be written as a reference. 
        This is because it's onum and ogen would be invalid. */
        if (CYPDF_ObjIsIndirect(obj)) {
            CYPDF_ChannelPrint(channel, "%u %hu R", CYPDF_ObjGetObjNum(obj), CYPDF_ObjGetObjGen(obj));
        }
    }
}


bool CYPDF_ObjIsIndirect(const CYPDF_Object* const obj) {
    CYPDF_TRACE;

    bool indirect = false;
    if (obj) {
        CYPDF_ObjNull* _obj = (CYPDF_ObjNull*)obj;
        indirect = _obj->header.indirect;
    }

    return indirect;
}

enum CYPDF_OBJ_CLASS CYPDF_ObjGetClass(const CYPDF_Object* const obj) {
    CYPDF_TRACE;

    enum CYPDF_OBJ_CLASS class = CYPDF_OBJ_CLASS_UNKNOWN;
    if (obj) {
        CYPDF_ObjNull* _obj = (CYPDF_ObjNull*)obj;
        class = _obj->header.class;
    }

    return class;
}

enum CYPDF_OBJ_SUBCLASS CYPDF_ObjGetSubclass(const CYPDF_Object* const obj) {
    CYPDF_TRACE;

    enum CYPDF_OBJ_SUBCLASS subclass = CYPDF_OBJ_SUBCLASS_UNKNOWN;
    if (obj) {
        CYPDF_ObjNull* _obj = (CYPDF_ObjNull*)obj;
        subclass = _obj->header.subclass;
    }

    return subclass;
}

uint32_t CYPDF_ObjGetObjNum(const CYPDF_Object* const obj) {
    CYPDF_TRACE;

    uint32_t onum = CYPDF_DEFAULT_OBJ_NUM;
    if (obj) {
        CYPDF_ObjNull* _obj = (CYPDF_ObjNull*)obj;
        onum = _obj->header.obj_num;
    }

    return onum;
}

uint16_t CYPDF_ObjGetObjGen(const CYPDF_Object* const obj) {
    CYPDF_TRACE;

    uint16_t ogen = CYPDF_DEFAULT_OBJ_GEN;
    if (obj) {
        CYPDF_ObjNull* _obj = (CYPDF_ObjNull*)obj;
        ogen = _obj->header.obj_gen;
    }

    return ogen;
}
