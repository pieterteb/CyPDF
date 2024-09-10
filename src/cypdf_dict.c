#include <stdio.h>
#include <stdlib.h>

#include "cypdf_dict.h"
#include "cypdf_consts.h"
#include "cypdf_name.h"
#include "cypdf_object.h"
#include "cypdf_print.h"
#include "cypdf_types.h"
#include "cypdf_utils.h"



CYPDF_Obj_Dict* CYPDF_New_Dict(CYPDF_BOOL indirect) {
    CYPDF_Obj_Dict* dict = (CYPDF_Obj_Dict*)CYPDF_New_Obj(indirect, CYPDF_OCLASS_DICT);

    return dict;
}

void CYPDF_Dict_Append(CYPDF_Obj_Dict* dict, const char* key_name, CYPDF_Object* value) {
    if (dict) {
        CYPDF_Obj_Name* key = CYPDF_New_Name(CYPDF_FALSE, key_name);
        ++dict->count;
        dict->keys = CYPDF_srealloc(dict->keys, dict->count * sizeof(CYPDF_Obj_Name*));
        dict->values = CYPDF_srealloc(dict->values, dict->count * sizeof(CYPDF_Object*));
        dict->keys[dict->count - 1] = key;
        dict->values[dict->count - 1] = value;
    }
}

void CYPDF_Write_Dict(FILE* fp, CYPDF_Object* obj) {
    if (fp == NULL || obj == NULL) {
        return;
    }

    CYPDF_Obj_Dict* dict = (CYPDF_Obj_Dict*)obj;

    fprintf(fp, "<<%s", CYPDF_NEW_LINE);

    /* Write all dictionary entry object pairs. */
    for(size_t i = 0; i < dict->count; ++i) {
        CYPDF_Write_Obj_Direct(fp, dict->keys[i]);
        fputc(' ', fp);

        if (CYPDF_Obj_isDirect(dict->values[i])) {
            CYPDF_Write_Obj_Direct(fp, dict->values[i]);
        } else {
            CYPDF_Write_Obj_Ref(fp, dict->values[i]);
        }
        
        CYPDF_Write_NL(fp);
    }

    fprintf(fp, ">>");
}

void CYPDF_Free_Dict(CYPDF_Object* obj) {
    if (obj) {
        CYPDF_Obj_Dict* dict = (CYPDF_Obj_Dict*)obj;
        
        for (size_t i = 0; i < dict->count; ++i) {
            CYPDF_Free_Obj(dict->keys[i], CYPDF_FALSE);
            CYPDF_Free_Obj(dict->values[i], CYPDF_FALSE);
        }
        free(dict->keys);
        free(dict->values);

        free(dict);
    }
}
