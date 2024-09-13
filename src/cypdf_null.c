#include <stdbool.h>
#include <stdlib.h>

#include "cypdf_null.h"
#include "cypdf_mmgr.h"
#include "cypdf_object.h"
#include "cypdf_types.h"



CYPDF_ObjNull* CYPDF_New_Null(CYPDF_MMgr* const mmgr) {
    CYPDF_ObjNull* null = (CYPDF_ObjNull*)CYPDF_GetMem(mmgr, sizeof(CYPDF_ObjNull));

    if (null) {
        CYPDF_InitHeader(null, CYPDF_OCLASS_NULL);
    }

    return null;
}

void CYPDF_PrintNull(FILE* restrict fp, const CYPDF_Object* const obj __attribute_maybe_unused__) {
    fprintf(fp, "null");

    return;
}

void CYPDF_FreeNull(CYPDF_Object* obj) {
    if (obj) {
        CYPDF_ObjNull* null = (CYPDF_ObjNull*)obj;

        free(null);
    }
}
