#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cypdf_number.h"
#include "cypdf_object.h"



CYPDF_ObjNumber* CYPDF_NewNumber(bool indirect, int val) {
    CYPDF_ObjNumber* number = (CYPDF_ObjNumber*)CYPDF_NewObj(indirect, CYPDF_OCLASS_NUMBER);
    if (number) {
        number->val = val;
    }

    return number;
}

void CYPDF_PrintNumber(FILE* fp, CYPDF_Object* obj) {
    if (fp == NULL || obj == NULL) {
        return;
    }

    CYPDF_ObjNumber* number = (CYPDF_ObjNumber*)obj;
    fprintf(fp, "%d", number->val);
}

void CYPDF_FreeNumber(CYPDF_Object* obj) {
    if (obj) {
        CYPDF_ObjNumber* number = (CYPDF_ObjNumber*)obj;
        free(number);
    }
}
