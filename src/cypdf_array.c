#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cypdf_array.h"
#include "cypdf_consts.h"
#include "cypdf_object.h"
#include "cypdf_real.h"
#include "cypdf_utils.h"



CYPDF_ObjArray* CYPDF_NewArray(bool indirect) {
    CYPDF_ObjArray* array = (CYPDF_ObjArray*)CYPDF_NewObj(indirect, CYPDF_OCLASS_ARRAY);

    return array;
}

CYPDF_ObjArray* CYPDF_ArrayFromRect(CYPDF_Rect rect, bool indirect) {
    CYPDF_ObjArray* array = CYPDF_NewArray(indirect);
    if (array) {
        CYPDF_ObjReal* coord = CYPDF_NewReal(CYPDF_FALSE, rect.lower_left.x);
        CYPDF_ArrayAppend(array, coord);
        coord = CYPDF_NewReal(CYPDF_FALSE, rect.lower_left.y);
        CYPDF_ArrayAppend(array, coord);
        coord = CYPDF_NewReal(CYPDF_FALSE, rect.upper_right.x);
        CYPDF_ArrayAppend(array, coord);
        coord = CYPDF_NewReal(CYPDF_FALSE, rect.upper_right.y);
        CYPDF_ArrayAppend(array, coord);
    }

    return array;
}

void CYPDF_ArrayAppend(CYPDF_ObjArray* array, CYPDF_Object* obj) {
    if (array && obj) {
        ++array->obj_count;
        array->objs = CYPDF_srealloc(array->objs, array->obj_count * sizeof(CYPDF_Object*));
        array->objs[array->obj_count - 1] = obj;
    }
}

void CYPDF_PrintArray(FILE* fp, CYPDF_Object* obj) {
    if (fp == NULL || obj == NULL) {
        return;
    }

    CYPDF_ObjArray* array = (CYPDF_ObjArray*)obj;
    fputc('[', fp);
    for (size_t i = 0; i < array->obj_count; ++i) {
        CYPDF_Object* _obj = array->objs[i];

        if (!CYPDF_ObjIsDirect(_obj)) {
            CYPDF_PrintObjRef(fp, _obj);
        } else {
            CYPDF_PrintObjDirect(fp, _obj);
        }

        if (i + 1 < array->obj_count) {
            fputc(' ', fp);
        }
    }
    fputc(']', fp);
}

void CYPDF_FreeArray(CYPDF_Object* obj) {
    if (obj) {
        CYPDF_ObjArray* array = (CYPDF_ObjArray*)obj;
        
        for (size_t i = 0; i < array->obj_count; ++i) {
            CYPDF_FreeObj(array->objs[i], CYPDF_FALSE);
        }
        free(array->objs);
        free(array);
    }
}
