#include <stdlib.h>
#include <string.h>

#include "cypdf_dict.h"
#include "cypdf_consts.h"
#include "cypdf_memmgr.h"
#include "cypdf_name.h"
#include "cypdf_object.h"
#include "cypdf_print.h"
#include "cypdf_types.h"



CYPDF_ObjDict* CYPDF_NewDict(CYPDF_MemMgr* const restrict memmgr) {
    CYPDF_ObjDict* dict = (CYPDF_ObjDict*)CYPDF_GetMem(memmgr, sizeof(CYPDF_ObjDict));

    if (dict) {
        dict->header.class = CYPDF_OBJ_CLASS_DICT;
        dict->header.subclass = CYPDF_OBJ_SUBCLASS_NONE;

        dict->keys = NULL;
        dict->values = NULL;
        dict->count = 0;

        dict->memmgr = CYPDF_NewMemMgr(CYPDF_FreeObj);
    }

    return dict;
}

void CYPDF_FreeDict(CYPDF_Object* obj) {
    if (obj) {
        CYPDF_ObjDict* dict = (CYPDF_ObjDict*)obj;

        CYPDF_DestroyMemMgr(dict->memmgr);
        free(dict->keys);
        free(dict->values);

        free(dict);
    }
}

void CYPDF_PrintDict(CYPDF_Channel* const restrict channel, const CYPDF_Object* const obj) {
    if (channel && obj) {
        CYPDF_ObjDict* dict = (CYPDF_ObjDict*)obj;

        CYPDF_ChannelPrintLine(channel, "<<");

        for(size_t i = 0; i < dict->count; ++i) {
            CYPDF_PrintObjDirect(channel, dict->keys[i]);
            CYPDF_ChannelPrint(channel, " ");

            if (CYPDF_ObjIsIndirect(dict->values[i])) {
                CYPDF_PrintObjRef(channel, dict->values[i]);
            } else {
                CYPDF_PrintObjDirect(channel, dict->values[i]);
            }
            CYPDF_ChannelPrintNL(channel);
        }

        CYPDF_ChannelPrint(channel, ">>");
    }
}


void CYPDF_DictAppend(CYPDF_ObjDict* const restrict dict, const char key_name[restrict static 1], CYPDF_Object* const value) {
    if (dict) {
        dict->keys = CYPDF_realloc(dict->keys, (dict->count + 1) * sizeof(CYPDF_ObjName*));
        dict->values = CYPDF_realloc(dict->values, (dict->count + 1) * sizeof(CYPDF_Object*));
        dict->keys[dict->count] = CYPDF_NewName(dict->memmgr, key_name);
        dict->values[dict->count] = value;
        ++dict->count;
    }
}

CYPDF_Object* CYPDF_DictGetValue(CYPDF_ObjDict* const restrict dict, const char key_name[restrict static 1]) {
    if (dict) {
        for (size_t i = 0; i < dict->count; ++i) {
            if (!strcmp(key_name, dict->keys[i]->value)) {
                return dict->values[i];
            }
        }
    }

    return NULL;
}
