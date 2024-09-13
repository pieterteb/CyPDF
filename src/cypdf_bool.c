#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cypdf_bool.h"
#include "cypdf_mmgr.h"
#include "cypdf_object.h"



CYPDF_ObjBool* CYPDF_NewBool(CYPDF_MMgr* const mmgr, const bool val) {
    CYPDF_ObjBool* boolean = (CYPDF_ObjBool*)CYPDF_GetMem(mmgr, sizeof(CYPDF_ObjBool));

    if (boolean) {
        CYPDF_InitHeader(boolean, CYPDF_OCLASS_BOOL);
        boolean->val = val;
    }

    return boolean;
}

void CYPDF_PrintBool(FILE* restrict fp, const CYPDF_Object* const obj) {
    if (fp && obj) {
        CYPDF_ObjBool* boolean = (CYPDF_ObjBool*)obj;

        if (boolean->val) {
            fprintf(fp, "true");
        } else {
            fprintf(fp, "false");
        }
    }    
}

void CYPDF_FreeBool(CYPDF_Object* obj) {
    if (obj) {
        CYPDF_ObjBool* boolean = (CYPDF_ObjBool*)obj;

        free(boolean);
    }
}
