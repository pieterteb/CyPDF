#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "cypdf_object.h"
#include "cypdf_array.h"
#include "cypdf_bool.h"
#include "cypdf_catalog.h"
#include "cypdf_consts.h"
#include "cypdf_dict.h"
#include "cypdf_info.h"
#include "cypdf_name.h"
#include "cypdf_null.h"
#include "cypdf_number.h"
#include "cypdf_pages.h"
#include "cypdf_print.h"
#include "cypdf_real.h"
#include "cypdf_stream.h"
#include "cypdf_string.h"
#include "cypdf_utils.h"



CYPDF_Object* CYPDF_NewObj(bool indirect, enum CYPDF_OCLASS class) {
    /* Assign size, write_func and free_func according to the object class. */
    size_t size = 0;
    switch (class)
    {
    case CYPDF_OCLASS_NULL:
        size = sizeof(CYPDF_ObjNull);
        break;
    case CYPDF_OCLASS_BOOL:
        size = sizeof(CYPDF_ObjBool);
        break;
    case CYPDF_OCLASS_NUMBER:
        size = sizeof(CYPDF_ObjNumber);
        break;
    case CYPDF_OCLASS_REAL:
        size = sizeof(CYPDF_ObjReal);
        break;
    case CYPDF_OCLASS_STRING:
        size = sizeof(CYPDF_ObjString);
        break;
    case CYPDF_OCLASS_NAME:
        size = sizeof(CYPDF_ObjName);
        break;
    case CYPDF_OCLASS_ARRAY:
        size = sizeof(CYPDF_ObjArray);
        break;
    case CYPDF_OCLASS_DICT:
        size = sizeof(CYPDF_ObjDict);
        break;
    case CYPDF_OCLASS_STREAM:
        size = sizeof(CYPDF_ObjStream);
        break;
    case CYPDF_OCLASS_INFO:
        size = sizeof(CYPDF_ObjInfo);
        break;
    case CYPDF_OCLASS_CATALOG:
        size = sizeof(CYPDF_ObjCatalog);
        break;
    case CYPDF_OCLASS_PAGE:
        size = sizeof(CYPDF_ObjPage);
        break;
    case CYPDF_OCLASS_PNODE:
        size = sizeof(CYPDF_ObjPNode);
        break;
    default:
        size = sizeof(CYPDF_ObjNull);
        break;
    }

    CYPDF_ObjNull* obj = (CYPDF_ObjNull*)CYPDF_scalloc(1, size);
    if (obj) {
        /* If the given class doesn't exist, it is set to unknown. */
        if (class > CYPDF_OCLASS_COUNT) {
            class = CYPDF_OCLASS_UNKNOWN;
        }

        obj->header.indirect = indirect;
        obj->header.class = class;
        obj->header.onum = CYPDF_DEFAULT_ONUM;
        obj->header.ogen = CYPDF_DEFAULT_OGEN;
    }

    return (CYPDF_Object*)obj;
}

void CYPDF_ObjSetOnum(CYPDF_Object* obj, uint32_t onum) {
    /* If the given ID is invalid, the default ID is used, which essentially nullifies the object. */
    if (onum > CYPDF_INDIRECT_OBJ_MAX) {
        onum = CYPDF_DEFAULT_ONUM;
    }

    CYPDF_ObjNull* _obj = (CYPDF_ObjNull*)obj;
    _obj->header.onum = onum;
}

bool CYPDF_ObjIsDirect(CYPDF_Object* obj) {
    bool direct = CYPDF_FALSE;
    if (obj) {
        CYPDF_ObjNull* _obj = (CYPDF_ObjNull*)obj;
        direct = !_obj->header.indirect;
    }

    return direct;
}

enum CYPDF_OCLASS CYPDF_ObjGetClass(CYPDF_Object* obj) {
    enum CYPDF_OCLASS class = CYPDF_OCLASS_NONE;
    if (obj) {
        CYPDF_ObjNull* _obj = (CYPDF_ObjNull*)obj;
        class = _obj->header.class;
    }

    return class;
}

uint32_t CYPDF_ObjGetOnum(CYPDF_Object* obj) {
    uint32_t onum = CYPDF_DEFAULT_ONUM;
    if (obj) {
        CYPDF_ObjNull* _obj = (CYPDF_ObjNull*)obj;
        onum = _obj->header.onum;
    }

    return onum;
}

uint16_t CYPDF_ObjGetOgen(CYPDF_Object* obj) {
    uint16_t ogen = CYPDF_DEFAULT_OGEN;
    if (obj) {
        CYPDF_ObjNull* _obj = (CYPDF_ObjNull*)obj;
        ogen = _obj->header.ogen;
    }

    return ogen;
}

CYPDF_PrintFunc CYPDF_ObjGetPrint(CYPDF_Object* obj) {
    CYPDF_PrintFunc print_func = NULL;
    if (obj) {
        enum CYPDF_OCLASS class = CYPDF_ObjGetClass(obj);

        switch (class)
        {
        case CYPDF_OCLASS_NULL:
            print_func = CYPDF_PRINT_NULL;
            break;
        case CYPDF_OCLASS_BOOL:
            print_func = CYPDF_PRINT_BOOL;
            break;
        case CYPDF_OCLASS_NUMBER:
            print_func = CYPDF_PRINT_NUMBER;
            break;
        case CYPDF_OCLASS_REAL:
            print_func = CYPDF_PRINT_REAL;
            break;
        case CYPDF_OCLASS_STRING:
            print_func = CYPDF_PRINT_STRING;
            break;
        case CYPDF_OCLASS_NAME:
            print_func = CYPDF_PRINT_NAME;
            break;
        case CYPDF_OCLASS_ARRAY:
            print_func = CYPDF_PRINT_ARRAY;
            break;
        case CYPDF_OCLASS_DICT:
            print_func = CYPDF_PRINT_DICT;
            break;
        case CYPDF_OCLASS_STREAM:
            print_func = CYPDF_PRINT_STREAM;
            break;
        case CYPDF_OCLASS_INFO:
            print_func = CYPDF_PRINT_INFO;
            break;
        case CYPDF_OCLASS_CATALOG:
            print_func = CYPDF_PRINT_CATALOG;
            break;
        case CYPDF_OCLASS_PAGE:
            print_func = CYPDF_PRINT_PAGE;
            break;
        case CYPDF_OCLASS_PNODE:
            print_func = CYPDF_PRINT_PNODE;
            break;
        default:
            print_func = CYPDF_PRINT_NULL;
            break;
        }
    }

    return print_func;
}

CYPDF_FreeFunc CYPDF_ObjGetFree(CYPDF_Object* obj) {
    CYPDF_FreeFunc free_func = NULL;
    if (obj) {
        enum CYPDF_OCLASS class = CYPDF_ObjGetClass(obj);

        switch (class)
        {
        case CYPDF_OCLASS_NULL:
            free_func = CYPDF_FREE_NULL;
            break;
        case CYPDF_OCLASS_BOOL:
            free_func = CYPDF_FREE_BOOL;
            break;
        case CYPDF_OCLASS_NUMBER:
            free_func = CYDPF_FREE_NUMBER;
            break;
        case CYPDF_OCLASS_REAL:
            free_func = CYPDF_FREE_REAL;
            break;
        case CYPDF_OCLASS_STRING:
            free_func = CYPDF_FREE_STRING;
            break;
        case CYPDF_OCLASS_NAME:
            free_func = CYPDF_FREE_NAME;
            break;
        case CYPDF_OCLASS_ARRAY:
            free_func = CYPDF_FREE_ARRAY;
            break;
        case CYPDF_OCLASS_DICT:
            free_func = CYPDF_FREE_DICT;
            break;
        case CYPDF_OCLASS_STREAM:
            free_func = CYPDF_FREE_STREAM;
            break;
        case CYPDF_OCLASS_INFO:
            free_func = CYPDF_FREE_INFO;
            break;
        case CYPDF_OCLASS_CATALOG:
            free_func = CYPDF_FREE_CATALOG;
            break;
        case CYPDF_OCLASS_PAGE:
            free_func = CYPDF_FREE_PAGE;
            break;
        case CYPDF_OCLASS_PNODE:
            free_func = CYPDF_FREE_PNODE;
            break;
        default:
            free_func = CYPDF_FREE_NULL;
            break;
        }
    }

    return free_func;
}

void CYPDF_PrintObjDirect(FILE* fp, CYPDF_Object* obj) {
    if (fp == NULL || obj == NULL) {
        return;
    }

    CYPDF_PrintFunc print_func = CYPDF_ObjGetPrint(obj);
    print_func(fp, obj); /* Writes the object directly. */
}

void CYPDF_PrintObjDef(FILE* fp, CYPDF_Object* obj) {
    if (fp == NULL || obj == NULL) {
        return;
    }

    /* If the object itself is not indirect, it cannot be written indirectly. 
    This is because it's ID and gen would be invalid. */
    if (!CYPDF_ObjIsDirect(obj)) {
        CYPDF_fprintfNL(fp, "%u %hu obj", CYPDF_ObjGetOnum(obj), CYPDF_ObjGetOgen(obj));
        CYPDF_PrintObjDirect(fp, obj);
        CYPDF_PrintNL(fp);
        CYPDF_fprintfNL(fp, "endobj");
        CYPDF_PrintNL(fp);
    }
}

void CYPDF_PrintObjRef(FILE* fp, CYPDF_Object* obj) {
    if (fp == NULL || obj == NULL) {
        return;
    }

    /* If the object itself is not indirect, it cannot be written indirectly. 
    This is because it's onj_num and gen_num would be invalid. 
    An object that is indirect should never be written indirectly. */
    if (!CYPDF_ObjIsDirect(obj)) {
        fprintf(fp, "%u %hu R", CYPDF_ObjGetOnum(obj), CYPDF_ObjGetOgen(obj));
    }
}

void CYPDF_FreeObj(CYPDF_Object* obj, bool ifIndirect) {
    if (obj) {
        /* An indirect object should only be freed if specified, since multiple attempts to free it might occur. */
        if (CYPDF_ObjIsDirect(obj) || ifIndirect) {
            CYPDF_FreeFunc free_func = CYPDF_ObjGetFree(obj);
            free_func(obj);
        }
    }
}
