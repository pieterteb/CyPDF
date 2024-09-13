#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cypdf_array.h"
#include "cypdf_mmgr.h"
#include "cypdf_object.h"
#include "cypdf_real.h"
#include "cypdf_utils.h"



CYPDF_ObjArray* CYPDF_NewArray(CYPDF_MMgr* const mmgr) {
    CYPDF_ObjArray* array = (CYPDF_ObjArray*)CYPDF_GetMem(mmgr, sizeof(CYPDF_ObjArray));

    if (array) {
        CYPDF_InitHeader(array, CYPDF_OCLASS_ARRAY);
        array->objs = NULL;
        array->obj_count = 0;
    }

    return array;
}

CYPDF_ObjArray* CYPDF_ArrayFromRect(CYPDF_MMgr* const mmgr, const CYPDF_Rect rect) {
    CYPDF_ObjArray* array = CYPDF_NewArray(mmgr);

    if (array) {
        CYPDF_ObjReal* coord = CYPDF_NewReal(mmgr, rect.lower_left.x);
        CYPDF_ArrayAppend(array, coord);
        coord = CYPDF_NewReal(mmgr, rect.lower_left.y);
        CYPDF_ArrayAppend(array, coord);
        coord = CYPDF_NewReal(mmgr, rect.upper_right.x);
        CYPDF_ArrayAppend(array, coord);
        coord = CYPDF_NewReal(mmgr, rect.upper_right.y);
        CYPDF_ArrayAppend(array, coord);
    }

    return array;
}

void CYPDF_ArrayAppend(CYPDF_ObjArray* const array, CYPDF_Object* const obj) {
    if (array && obj) {
        array->objs = CYPDF_srealloc(array->objs, (array->obj_count + 1) * sizeof(CYPDF_Object*));
        array->objs[array->obj_count] = obj;
        ++array->obj_count;
    }
}

void CYPDF_PrintArray(FILE* restrict fp, const CYPDF_Object* const obj) {
    if (fp && obj) {
        CYPDF_ObjArray* array = (CYPDF_ObjArray*)obj;

        fputc('[', fp);
        size_t i = 0;
        for (;;) {
            CYPDF_Object* _obj = array->objs[i];

            if (CYPDF_ObjIsIndirect(_obj)) {
                CYPDF_PrintObjRef(fp, _obj);
            } else {
                CYPDF_PrintObjDirect(fp, _obj);
            }
            ++i;
            if (i >= array->obj_count) break;
            fputc(' ', fp);
        }
        fputc(']', fp);
    }
}

void CYPDF_FreeArray(CYPDF_Object* obj) {
    if (obj) {
        CYPDF_ObjArray* array = (CYPDF_ObjArray*)obj;
        
        free(array->objs);
        free(array);
    }
}
