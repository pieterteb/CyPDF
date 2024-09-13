#include <stdio.h>
#include <stdlib.h>

#include "cypdf_dict.h"
#include "cypdf_consts.h"
#include "cypdf_mmgr.h"
#include "cypdf_name.h"
#include "cypdf_object.h"
#include "cypdf_print.h"
#include "cypdf_types.h"
#include "cypdf_utils.h"



CYPDF_ObjDict* CYPDF_NewDict(CYPDF_MMgr* const mmgr) {
    CYPDF_ObjDict* dict = (CYPDF_ObjDict*)CYPDF_GetMem(mmgr, sizeof(CYPDF_ObjDict));

    if (dict) {
        CYPDF_InitHeader(dict, CYPDF_OCLASS_DICT);
        dict->keys = NULL;
        dict->values = NULL;
        dict->count = 0;
    }

    return dict;
}

void CYPDF_DictAppend(CYPDF_MMgr* const mmgr, CYPDF_ObjDict* const dict, char key_name[restrict static 1], CYPDF_Object* const value) {
    if (dict) {
        CYPDF_ObjName* key = CYPDF_NewName(mmgr, key_name);

        dict->keys = CYPDF_srealloc(dict->keys, (dict->count + 1) * sizeof(CYPDF_ObjName*));
        dict->values = CYPDF_srealloc(dict->values, (dict->count + 1) * sizeof(CYPDF_Object*));
        dict->keys[dict->count] = key;
        dict->values[dict->count] = value;
        ++dict->count;
    }
}

void CYPDF_PrintDict(FILE* restrict fp, const CYPDF_Object* const obj) {
    if (fp && obj) {
        CYPDF_ObjDict* dict = (CYPDF_ObjDict*)obj;

        CYPDF_fprintfNL(fp, "<<");

        /* Write all dictionary entry object pairs. */
        for(size_t i = 0; i < dict->count; ++i) {
            CYPDF_PrintObjDirect(fp, dict->keys[i]);
            fputc(' ', fp);

            if (!CYPDF_ObjIsIndirect(dict->values[i])) {
                CYPDF_PrintObjDirect(fp, dict->values[i]);
            } else {
                CYPDF_PrintObjRef(fp, dict->values[i]);
            }
            
            CYPDF_PrintNL(fp);
        }

        fprintf(fp, ">>");
    }
}

void CYPDF_FreeDict(CYPDF_Object* obj) {
    if (obj) {
        CYPDF_ObjDict* dict = (CYPDF_ObjDict*)obj;
        
        free(dict->keys);
        free(dict->values);
        free(dict);
    }
}
