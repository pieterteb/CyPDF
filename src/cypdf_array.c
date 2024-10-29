#include <stdlib.h>

#include "cypdf_array.h"
#include "cypdf_integer.h"
#include "cypdf_list.h"
#include "cypdf_log.h"
#include "cypdf_memory.h"
#include "cypdf_number.h"
#include "cypdf_object.h"
#include "cypdf_print.h"
#include "cypdf_types.h"



CYPDF_ObjArray* CYPDF_NewArray(CYPDF_MemMgr* const restrict memmgr) {
    CYPDF_TRACE;

    CYPDF_ObjArray* array = (CYPDF_ObjArray*)CYPDF_GetMem(memmgr, sizeof(CYPDF_ObjArray));

    if (array) {
        array->header.class = CYPDF_OBJ_CLASS_ARRAY;

        array->obj_list = CYPF_NewList(CYPDF_LIST_DEFAULT_BLOCK_SIZE);

        array->memmgr = CYPDF_NewMemMgr(CYPDF_FreeObj);
    }

    return array;
}

void CYPDF_FreeArray(CYPDF_Object* obj) {
    CYPDF_TRACE;

    if (obj) {
        CYPDF_ObjArray* array = (CYPDF_ObjArray*)obj;
        
        CYPDF_DestroyMemMgr(array->memmgr);
        CYPDF_FreeList(array->obj_list);

        free(array);
    }
}

void CYPDF_PrintArray(CYPDF_Channel* const restrict channel, const CYPDF_Object* const obj) {
    CYPDF_TRACE;

    if (channel && obj) {
        CYPDF_ObjArray* array = (CYPDF_ObjArray*)obj;

        CYPDF_ChannelPrint(channel, "[");
        CYPDF_List* obj_list = array->obj_list;
        size_t array_length = CYPDF_ArrayLength(array);
        for (size_t i = 0; i < array_length; ++i) {
            if (CYPDF_ObjIsIndirect(obj_list->elements[i])) {
                CYPDF_PrintObjRef(channel, obj_list->elements[i]);
            } else {
                CYPDF_PrintObjDirect(channel, obj_list->elements[i]);
            }
            if (i + 1 == array_length) {
                break;
            }
            CYPDF_ChannelPrint(channel, " ");
        }
        CYPDF_ChannelPrint(channel, "]");
    }
}


void CYPDF_ArrayAppend(CYPDF_ObjArray* const restrict array, CYPDF_Object* const restrict obj) {
    CYPDF_TRACE;

    if (array && obj) {
        CYPFD_ListAppend(array->obj_list, obj);
    }
}

CYPDF_ObjArray* CYPDF_ArrayFromRect(CYPDF_MemMgr* const restrict memmgr, const CYPDF_Rect rect) {
    CYPDF_TRACE;

    CYPDF_ObjArray* array = CYPDF_NewArray(memmgr);

    if (array) {
        CYPDF_ArrayAppend(array, CYPDF_NewNumber(array->memmgr, rect.lower_left.x));
        CYPDF_ArrayAppend(array, CYPDF_NewNumber(array->memmgr, rect.lower_left.y));
        CYPDF_ArrayAppend(array, CYPDF_NewNumber(array->memmgr, rect.upper_right.x));
        CYPDF_ArrayAppend(array, CYPDF_NewNumber(array->memmgr, rect.upper_right.y));
    }

    return array;
}

CYPDF_ObjArray* CYPDF_ArrayFromIntArray(CYPDF_MemMgr* const restrict memmgr, const int* const arr, const size_t count) {
    CYPDF_TRACE;

    CYPDF_ObjArray* array = CYPDF_NewArray(memmgr);

    if (array) {
        for (size_t i = 0; i < count; ++i) {
            CYPDF_ArrayAppend(array, CYPDF_NewInteger(array->memmgr, arr[i]));
        }
    }

    return array;
}

CYPDF_Object* CYPDF_ArrayAtIndex(CYPDF_ObjArray* const array, const size_t index) {
    CYPDF_TRACE;

    return CYPDF_ListAtIndex(array->obj_list, index);
}

size_t CYPDF_ArrayLength(CYPDF_ObjArray* const array) {
    CYPDF_TRACE;

    return CYPDF_ListLength(array->obj_list);
}
