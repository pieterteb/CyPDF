#include "cypdf_object.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>



CYPDF_ObjectBool* CYPDF_object_bool_new(bool indirect, bool value) {
    CYPDF_ObjectBool* object_bool = calloc(1, sizeof(*object_bool));

    if (object_bool) {
        if (indirect)
            CYPDF_object_set_indirect(object_bool);
        CYPDF_object_set_class(object_bool, CYPDF_OBJECT_CLASS_BOOL);

        object_bool->value = value;
    }

    return object_bool;
}

void CYPDF_object_bool_free(CYPDF_ObjectBool* object_bool) {
    assert(object_bool != NULL);

    free(object_bool);
}

void CYPDF_object_bool_print(FILE* file_stream, CYPDF_ObjectBool* object_bool) {
    assert(file_stream != NULL);
    assert(object_bool != NULL);

    if (object_bool->value)
        fprintf(file_stream, "true");
    else
        fprintf(file_stream, "false");
}
