#include <stdbool.h>
#include <stdlib.h>

#include "cypdf_null.h"



CYPDF_ObjNull* CYPDF_New_Null(bool indirect) {
    CYPDF_ObjNull* null = (CYPDF_ObjNull*)CYPDF_NewObj(indirect, CYPDF_OCLASS_NULL);

    return null;
}

void CYPDF_PrintNull(FILE* fp, CYPDF_Object* obj __attribute_maybe_unused__) {
    fprintf(fp, "null");

    return;
}

void CYPDF_FreeNull(CYPDF_Object* obj) {
    if (obj) {
        CYPDF_ObjNull* null = (CYPDF_ObjNull*)obj;
        free(null);
    }
}
