#include <stdlib.h>

#include "cypdf_null.h"
#include "cypdf_types.h"



CYPDF_Obj_Null* CYPDF_New_Null(CYPDF_BOOL indirect) {
    CYPDF_Obj_Null* null = (CYPDF_Obj_Null*)CYPDF_New_Obj(indirect, CYPDF_OCLASS_NULL);

    return null;
}

void CYPDF_Write_Null(FILE* fp, CYPDF_Object* obj __attribute_maybe_unused__) {
    fprintf(fp, "null");

    return;
}

void CYPDF_Free_Null(CYPDF_Object* obj) {
    if (obj) {
        CYPDF_Obj_Null* null = (CYPDF_Obj_Null*)obj;
        free(null);
    }
}
