#include <stdlib.h>

#include "cypdf_array.h"
#include "cypdf_log.h"
#include "cypdf_memmgr.h"
#include "cypdf_number.h"
#include "cypdf_object.h"
#include "cypdf_print.h"
#include "cypdf_types.h"



CYPDF_ObjArray* CYPDF_NewArray(CYPDF_MemMgr* const restrict memmgr) {
    CYPDF_TRACE;

    CYPDF_ObjArray* array = (CYPDF_ObjArray*)CYPDF_GetMem(memmgr, sizeof(CYPDF_ObjArray));

    if (array) {
        array->header.class = CYPDF_OBJ_CLASS_ARRAY;

        array->objs = NULL;
        array->obj_count = 0;

        array->memmgr = CYPDF_NewMemMgr(CYPDF_FreeObj);
    }

    return array;
}

void CYPDF_FreeArray(CYPDF_Object* obj) {
    CYPDF_TRACE;

    if (obj) {
        CYPDF_ObjArray* array = (CYPDF_ObjArray*)obj;
        
        CYPDF_DestroyMemMgr(array->memmgr);
        free(array->objs);

        free(array);
    }
}

void CYPDF_PrintArray(CYPDF_Channel* const restrict channel, const CYPDF_Object* const obj) {
    CYPDF_TRACE;

    if (channel && obj) {
        CYPDF_ObjArray* array = (CYPDF_ObjArray*)obj;

        CYPDF_ChannelPrint(channel, "[");
        for (size_t i = 0; i < array->obj_count; ++i) {
            CYPDF_Object* _obj = array->objs[i];

            if (CYPDF_ObjIsIndirect(_obj)) {
                CYPDF_PrintObjRef(channel, _obj);
            } else {
                CYPDF_PrintObjDirect(channel, _obj);
            }
            if (i + 1 == array->obj_count) {
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
        array->objs = CYPDF_realloc(array->objs, (array->obj_count + 1) * sizeof(CYPDF_Object*));
        array->objs[array->obj_count] = obj;
        ++array->obj_count;
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
