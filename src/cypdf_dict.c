#include <stdlib.h>
#include <string.h>

#include "cypdf_dict.h"
#include "cypdf_consts.h"
#include "cypdf_list.h"
#include "cypdf_log.h"
#include "cypdf_memory.h"
#include "cypdf_name.h"
#include "cypdf_object.h"
#include "cypdf_print.h"
#include "cypdf_types.h"



CYPDF_ObjDict* CYPDF_NewDict(CYPDF_MemMgr* const memmgr) {
    CYPDF_TRACE;

    CYPDF_ObjDict* dict = (CYPDF_ObjDict*)CYPDF_GetMem(memmgr, sizeof(CYPDF_ObjDict));

    dict->header.class = CYPDF_OBJ_CLASS_DICT;
    dict->header.subclass = CYPDF_OBJ_SUBCLASS_NONE;

    dict->key_list = CYPF_NewList(CYPDF_LIST_DEFAULT_BLOCK_SIZE);
    dict->value_list = CYPF_NewList(CYPDF_LIST_DEFAULT_BLOCK_SIZE);

    dict->memmgr = CYPDF_NewMemMgr(CYPDF_FreeObj);

    return dict;
}

void CYPDF_FreeDict(CYPDF_Object* obj) {
    CYPDF_TRACE;

    CYPDF_ObjDict* dict = (CYPDF_ObjDict*)obj;

    CYPDF_FreeList(dict->key_list);
    CYPDF_FreeList(dict->value_list);
    CYPDF_DestroyMemMgr(dict->memmgr);

    free(dict);
}

void CYPDF_PrintDict(CYPDF_Channel* const channel, const CYPDF_Object* const obj) {
    CYPDF_TRACE;

    CYPDF_ObjDict* dict = (CYPDF_ObjDict*)obj;

    CYPDF_ChannelPrintLine(channel, "<<");

    size_t length = CYPDF_DictLength(dict);
    for(size_t i = 0; i < length; ++i) {
        CYPDF_ObjName* key = CYPDF_DictKeyAtIndex(dict, i);
        CYPDF_Object* value = CYPDF_DictValueAtIndex(dict, i);
        if (key) {
            CYPDF_PrintObjDirect(channel, key);
            CYPDF_ChannelPrint(channel, " ");
            if (CYPDF_ObjIsIndirect(value)) {
                CYPDF_PrintObjRef(channel, value);
            } else {
                CYPDF_PrintObjDirect(channel, value);
            }
            CYPDF_ChannelPrintNL(channel);
        }
    }

    CYPDF_ChannelPrint(channel, ">>");
}


void CYPDF_DictAppend(CYPDF_ObjDict* const restrict dict, const char* restrict key_name, CYPDF_Object* const restrict value) {
    CYPDF_TRACE;

    CYPFD_ListAppend(dict->key_list, CYPDF_NewName(dict->memmgr, key_name));
    CYPFD_ListAppend(dict->value_list, value);
}

void CYPDF_DictSetAtIndex(CYPDF_ObjDict* const restrict dict, const size_t index, const char* restrict key_name, CYPDF_Object* const restrict value) {
    CYPDF_TRACE;

    if (!CYPDF_ListAtIndex(dict->key_list, index)) {
        CYPDF_ListSetAtIndex(dict->key_list, index, CYPDF_NewName(dict->memmgr, key_name));
    }
    CYPDF_ListSetAtIndex(dict->value_list, index, value);
}

CYPDF_ObjName* CYPDF_DictKeyAtIndex(CYPDF_ObjDict* const dict, const size_t index) {
    CYPDF_TRACE;

    if (index < CYPDF_DictLength(dict)) {
        return CYPDF_ListAtIndex(dict->key_list, index);
    }

    return NULL;
}

CYPDF_Object* CYPDF_DictValueAtIndex(CYPDF_ObjDict* const dict, const size_t index) {
    CYPDF_TRACE;

    if (index < CYPDF_DictLength(dict)) {
        return CYPDF_ListAtIndex(dict->value_list, index);
    }

    return NULL;
}

CYPDF_Object* CYPDF_DictValueAtName(CYPDF_ObjDict* const restrict dict, const char key_name[restrict static 1]) {
    CYPDF_TRACE;

    const size_t dict_length = CYPDF_DictLength(dict);
    for (size_t i = 0; i < dict_length; ++i) {
        if (!strcmp(key_name, CYPDF_DictKeyAtIndex(dict, i)->value)) {
            return CYPDF_DictValueAtIndex(dict, i);
        }
    }

    return NULL;
}

size_t CYPDF_DictLength(CYPDF_ObjDict* const dict) {
    CYPDF_TRACE;

    return CYPDF_ListLength(dict->key_list);
}
