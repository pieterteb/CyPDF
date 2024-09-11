#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cypdf_real.h"
#include "cypdf_object.h"



CYPDF_ObjReal* CYPDF_NewReal(bool indirect, float value) {
    CYPDF_ObjReal* real = (CYPDF_ObjReal*)CYPDF_NewObj(indirect, CYPDF_OCLASS_REAL);
    if (real) {
        real->value = value;
    }

    return real;
}

void CYPDF_PrintReal(FILE* fp, CYPDF_Object* obj) {
    if (fp == NULL || obj == NULL) {
        return;
    }

    CYPDF_ObjReal* real = (CYPDF_ObjReal*)obj;
    fprintf(fp, "%g", real->value);
}

void CYPDF_FreeReal(CYPDF_Object* obj) {
    if (obj) {
        CYPDF_ObjReal* real = (CYPDF_ObjReal*)obj;
        free(real);
    }
}
