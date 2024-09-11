#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cypdf_name.h"
#include "cypdf_object.h"
#include "cypdf_utils.h"



CYPDF_ObjName* CYPDF_NewName(bool indirect, const char* val) {
    CYPDF_ObjName* name = (CYPDF_ObjName*)CYPDF_NewObj(indirect, CYPDF_OCLASS_NAME);
    if (name) {
        memcpy(name->val, val, MAX(strlen(val), CYPDF_MAX_NAME_LEN));
    }

    return name;
}

void CYPDF_PrintName(FILE* fp, CYPDF_Object* obj) {
    if (fp == NULL || obj == NULL) {
        return;
    }

    CYPDF_ObjName* name = (CYPDF_ObjName*)obj;
    fprintf(fp, "/%s", name->val);
}

void CYPDF_FreeName(CYPDF_Object* obj) {
    if (obj) {
        CYPDF_ObjName* name = (CYPDF_ObjName*)obj;
        free(name);
    }
}
