#include <stdlib.h>
#include <string.h>

#include "cypdf_dict.h"
#include "cypdf_consts.h"
#include "cypdf_log.h"
#include "cypdf_memmgr.h"
#include "cypdf_name.h"
#include "cypdf_object.h"
#include "cypdf_print.h"
#include "cypdf_types.h"



static void CYPDF_DictResize(CYPDF_ObjDict* const restrict dict, const size_t count);


CYPDF_ObjDict* CYPDF_NewDict(CYPDF_MemMgr* const restrict memmgr) {
    CYPDF_TRACE;

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
    CYPDF_TRACE;

    if (obj) {
        CYPDF_ObjDict* dict = (CYPDF_ObjDict*)obj;

        CYPDF_DestroyMemMgr(dict->memmgr);
        free(dict->keys);
        free(dict->values);

        free(dict);
    }
}

void CYPDF_PrintDict(CYPDF_Channel* const restrict channel, const CYPDF_Object* const obj) {
    CYPDF_TRACE;

    if (channel && obj) {
        CYPDF_ObjDict* dict = (CYPDF_ObjDict*)obj;

        CYPDF_ChannelPrintLine(channel, "<<");

        for(size_t i = 0; i < dict->count; ++i) {
            if (dict->keys[i]) {
                CYPDF_PrintObjDirect(channel, dict->keys[i]);
                CYPDF_ChannelPrint(channel, " ");

                if (CYPDF_ObjIsIndirect(dict->values[i])) {
                    CYPDF_PrintObjRef(channel, dict->values[i]);
                } else {
                    CYPDF_PrintObjDirect(channel, dict->values[i]);
                }
                CYPDF_ChannelPrintNL(channel);
            }
        }

        CYPDF_ChannelPrint(channel, ">>");
    }
}


void CYPDF_DictAppend(CYPDF_ObjDict* const restrict dict, const char key_name[restrict static 1], CYPDF_Object* const restrict value) {
    CYPDF_TRACE;

    if (dict) {
        dict->keys = CYPDF_realloc(dict->keys, (dict->count + 1) * sizeof(CYPDF_ObjName*));
        dict->values = CYPDF_realloc(dict->values, (dict->count + 1) * sizeof(CYPDF_Object*));
        dict->keys[dict->count] = CYPDF_NewName(dict->memmgr, key_name);
        dict->values[dict->count] = value;
        ++dict->count;
    }
}

void CYPDF_DictSetAtIndex(CYPDF_ObjDict* const restrict dict, const size_t index, const char* restrict key_name, CYPDF_Object* const restrict value) {
    CYPDF_TRACE;

    if (dict) {
        if (index >= dict->count) {
            CYPDF_DictResize(dict, index + 1);
        }
        if (!dict->keys[index]) {
            dict->keys[index] = CYPDF_NewName(dict->memmgr, key_name);
        }
        dict->values[index] = value;
    }
}

static void CYPDF_DictResize(CYPDF_ObjDict* const restrict dict, const size_t count) {
    CYPDF_TRACE;

    if (dict) {
        if (count == dict->count) {
            return;
        }
        dict->keys = CYPDF_realloc(dict->keys, count * sizeof(CYPDF_ObjName*));
        dict->values = CYPDF_realloc(dict->values, count * sizeof(CYPDF_Object*));

        for (size_t i = dict->count; i < count; ++i) {
            dict->keys[i] = NULL;
            dict->values[i] = NULL;
        }

        dict->count = count;
    }
}

CYPDF_Object* CYPDF_DictGetValueName(CYPDF_ObjDict* const restrict dict, const char key_name[restrict static 1]) {
    CYPDF_TRACE;

    if (dict) {
        for (size_t i = 0; i < dict->count; ++i) {
            if (!strcmp(key_name, dict->keys[i]->value)) {
                return dict->values[i];
            }
        }
    }

    return NULL;
}

CYPDF_Object* CYPDF_DictGetValueIndex(CYPDF_ObjDict* const restrict dict, const size_t index) {
    CYPDF_TRACE;

    if (dict) {
        if (index < dict->count) {
            return dict->values[index];
        }
    }

    return NULL;
}
