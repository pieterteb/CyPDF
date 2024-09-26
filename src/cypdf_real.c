#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cypdf_real.h"
#include "cypdf_mmgr.h"
#include "cypdf_object.h"
#include "cypdf_types.h"



CYPDF_ObjReal* CYPDF_NewReal(CYPDF_MMgr* const mmgr, const float value) {
    CYPDF_ObjReal* real = (CYPDF_ObjReal*)CYPDF_GetMem(mmgr, sizeof(CYPDF_ObjReal));

    if (real) {
        CYPDF_InitHeader(real, CYPDF_OCLASS_REAL);
        real->value = value;
    }

    return real;
}

void CYPDF_RealSetValue(CYPDF_ObjReal* const real, const float value) {
    if (real) {
        real->value = value;
    }
}

float CYPDF_RealGetValue(const CYPDF_ObjReal* const real) {
    if (real) {
        return real->value;
    }

    return 0.0f;
}

void CYPDF_PrintReal(FILE* restrict fp, const CYPDF_Object* const obj) {
    if (fp && obj) {
        CYPDF_ObjReal* real = (CYPDF_ObjReal*)obj;
        fprintf(fp, "%g", real->value);
    }
}

void CYPDF_FreeReal(CYPDF_Object* obj) {
    if (obj) {
        CYPDF_ObjReal* real = (CYPDF_ObjReal*)obj;
        free(real);
    }
}
