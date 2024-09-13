#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cypdf_name.h"
#include "cypdf_mmgr.h"
#include "cypdf_object.h"
#include "cypdf_utils.h"



CYPDF_ObjName* CYPDF_NewName(CYPDF_MMgr* const mmgr, char val[restrict static 1]) {
    CYPDF_ObjName* name = (CYPDF_ObjName*)CYPDF_GetMem(mmgr, sizeof(CYPDF_ObjName));

    if (name) {
        CYPDF_InitHeader(name, CYPDF_OCLASS_NAME);

        strncpy(name->val, val, CYPDF_MAX_NAME_LEN + 1);
        name->val[CYPDF_MAX_NAME_LEN] = 0;
    }

    return name;
}

void CYPDF_PrintName(FILE* restrict fp, const CYPDF_Object* const obj) {
    if (fp && obj) {
        CYPDF_ObjName* name = (CYPDF_ObjName*)obj;
        fprintf(fp, "/%s", name->val);
    }
}

void CYPDF_FreeName(CYPDF_Object* obj) {
    if (obj) {
        CYPDF_ObjName* name = (CYPDF_ObjName*)obj;
        free(name);
    }
}
