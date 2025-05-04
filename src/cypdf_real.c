#include "cypdf_object.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>



CYPDF_ObjectReal* CYPDF_object_real_new(bool indirect, float value) {
    CYPDF_ObjectReal* object_real = calloc(1, sizeof(*object_real));

    if (object_real) {
        if (indirect)
            CYPDF_object_set_indirect(object_real);
        CYPDF_object_set_class(object_real, CYPDF_OBJECT_CLASS_REAL);

        object_real->value = value;
    }

    return object_real;
}

void CYPDF_object_real_free(CYPDF_ObjectReal* object_real) {
    assert(object_real != NULL);

    free(object_real);
}

void CYPDF_object_real_print(FILE* file_stream, CYPDF_ObjectReal* object_real) {
    assert(file_stream != NULL);
    assert(object_real != NULL);

    fprintf(file_stream, "%g", object_real->value);
}
