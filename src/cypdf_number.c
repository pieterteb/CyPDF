#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cypdf_number.h"
#include "cypdf_mmgr.h"
#include "cypdf_object.h"
#include "cypdf_types.h"



CYPDF_ObjNumber* CYPDF_NewNumber(CYPDF_MMgr* const mmgr, const int val) {
    CYPDF_ObjNumber* number = (CYPDF_ObjNumber*)CYPDF_GetMem(mmgr, sizeof(CYPDF_ObjNumber));

    if (number) {
        CYPDF_InitHeader(number, CYPDF_OCLASS_NUMBER);
        number->val = val;
    }

    return number;
}

void CYPDF_SetNumber(CYPDF_ObjNumber* const number, const int val) {
    if (number) {
        number->val = val;
    }
}

int CYPDF_GetNumber(const CYPDF_ObjNumber* const number) {
    if (number) {
        return number->val;
    }

    return 0;
}

void CYPDF_PrintNumber(FILE* restrict fp, const CYPDF_Object* const obj) {
    if (fp && obj) {
        CYPDF_ObjNumber* number = (CYPDF_ObjNumber*)obj;

        fprintf(fp, "%d", CYPDF_GetNumber(number));
    }
}

void CYPDF_FreeNumber(CYPDF_Object* obj) {
    if (obj) {
        CYPDF_ObjNumber* number = (CYPDF_ObjNumber*)obj;

        free(number);
    }
}
