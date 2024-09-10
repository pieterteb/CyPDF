#include <stdio.h>
#include <stdlib.h>

#include "cypdf_array.h"
#include "cypdf_consts.h"
#include "cypdf_object.h"
#include "cypdf_real.h"
#include "cypdf_types.h"
#include "cypdf_utils.h"



CYPDF_Obj_Array* CYPDF_New_Array(CYPDF_BOOL indirect) {
    CYPDF_Obj_Array* array = (CYPDF_Obj_Array*)CYPDF_New_Obj(indirect, CYPDF_OCLASS_ARRAY);

    return array;
}

CYPDF_Obj_Array* CYPDF_Array_From_Rect(CYPDF_Rect rect, CYPDF_BOOL indirect) {
    CYPDF_Obj_Array* array = CYPDF_New_Array(indirect);
    if (array) {
        CYPDF_Obj_Real* coord = CYPDF_New_Real(CYPDF_FALSE, rect.lower_left.x);
        CYPDF_Array_Append(array, coord);
        coord = CYPDF_New_Real(CYPDF_FALSE, rect.lower_left.y);
        CYPDF_Array_Append(array, coord);
        coord = CYPDF_New_Real(CYPDF_FALSE, rect.upper_right.x);
        CYPDF_Array_Append(array, coord);
        coord = CYPDF_New_Real(CYPDF_FALSE, rect.upper_right.y);
        CYPDF_Array_Append(array, coord);
    }

    return array;
}

void CYPDF_Array_Append(CYPDF_Obj_Array* array, CYPDF_Object* obj) {
    if (array && obj) {
        ++array->obj_count;
        array->objs = CYPDF_srealloc(array->objs, array->obj_count * sizeof(CYPDF_Object*));
        array->objs[array->obj_count - 1] = obj;
    }
}

void CYPDF_Write_Array(FILE* fp, CYPDF_Object* obj) {
    if (fp == NULL || obj == NULL) {
        return;
    }

    CYPDF_Obj_Array* array = (CYPDF_Obj_Array*)obj;
    fputc('[', fp);
    for (size_t i = 0; i < array->obj_count; ++i) {
        CYPDF_Object* _obj = array->objs[i];

        if (!CYPDF_Obj_isDirect(_obj)) {
            CYPDF_Write_Obj_Ref(fp, _obj);
        } else {
            CYPDF_Write_Obj_Direct(fp, _obj);
        }

        if (i + 1 < array->obj_count) {
            fputc(' ', fp);
        }
    }
    fputc(']', fp);
}

void CYPDF_Free_Array(CYPDF_Object* obj) {
    if (obj) {
        CYPDF_Obj_Array* array = (CYPDF_Obj_Array*)obj;
        
        for (size_t i = 0; i < array->obj_count; ++i) {
            CYPDF_Free_Obj(array->objs[i], CYPDF_FALSE);
        }
        free(array->objs);
        free(array);
    }
}
