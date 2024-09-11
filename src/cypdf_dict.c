#include <stdio.h>
#include <stdlib.h>

#include "cypdf_dict.h"
#include "cypdf_consts.h"
#include "cypdf_name.h"
#include "cypdf_object.h"
#include "cypdf_print.h"
#include "cypdf_types.h"
#include "cypdf_utils.h"



CYPDF_ObjDict* CYPDF_NewDict(bool indirect) {
    CYPDF_ObjDict* dict = (CYPDF_ObjDict*)CYPDF_NewObj(indirect, CYPDF_OCLASS_DICT);

    return dict;
}

void CYPDF_DictAppend(CYPDF_ObjDict* dict, const char* key_name, CYPDF_Object* value) {
    if (dict) {
        CYPDF_ObjName* key = CYPDF_NewName(CYPDF_FALSE, key_name);
        ++dict->count;
        dict->keys = CYPDF_srealloc(dict->keys, dict->count * sizeof(CYPDF_ObjName*));
        dict->values = CYPDF_srealloc(dict->values, dict->count * sizeof(CYPDF_Object*));
        dict->keys[dict->count - 1] = key;
        dict->values[dict->count - 1] = value;
    }
}

void CYPDF_PrintDict(FILE* fp, CYPDF_Object* obj) {
    if (fp == NULL || obj == NULL) {
        return;
    }

    CYPDF_ObjDict* dict = (CYPDF_ObjDict*)obj;

    fprintf(fp, "<<%s", CYPDF_NEW_LINE);

    /* Write all dictionary entry object pairs. */
    for(size_t i = 0; i < dict->count; ++i) {
        CYPDF_PrintObjDirect(fp, dict->keys[i]);
        fputc(' ', fp);

        if (CYPDF_ObjIsDirect(dict->values[i])) {
            CYPDF_PrintObjDirect(fp, dict->values[i]);
        } else {
            CYPDF_PrintObjRef(fp, dict->values[i]);
        }
        
        CYPDF_PrintNL(fp);
    }

    fprintf(fp, ">>");
}

void CYPDF_FreeDict(CYPDF_Object* obj) {
    if (obj) {
        CYPDF_ObjDict* dict = (CYPDF_ObjDict*)obj;
        
        for (size_t i = 0; i < dict->count; ++i) {
            CYPDF_FreeObj(dict->keys[i], CYPDF_FALSE);
            CYPDF_FreeObj(dict->values[i], CYPDF_FALSE);
        }
        free(dict->keys);
        free(dict->values);

        free(dict);
    }
}
