#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cypdf_bool.h"
#include "cypdf_object.h"



CYPDF_ObjBool* CYPDF_NewBool(bool indirect, bool val) {
    CYPDF_ObjBool* boolean = (CYPDF_ObjBool*)CYPDF_NewObj(indirect, CYPDF_OCLASS_BOOL);
    if (boolean) {
        boolean->val = val;
    }

    return boolean;
}

void CYPDF_PrintBool(FILE* fp, CYPDF_Object* obj) {
    if (fp == NULL || obj == NULL) {
        return;
    }

    CYPDF_ObjBool* boolean = (CYPDF_ObjBool*)obj;
    if (boolean->val) {
        fprintf(fp, "true");
    } else {
        fprintf(fp, "false");
    }
}

void CYPDF_FreeBool(CYPDF_Object* obj) {
    if (obj) {
        CYPDF_ObjBool* boolean = (CYPDF_ObjBool*)obj;
        free(boolean);
    }
}
