#include "cypdf_object.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>



CYPDF_ObjectNull* CYPDF_object_null_new(bool indirect) {
    CYPDF_ObjectNull* object_null = calloc(1, sizeof(*object_null));

    if (object_null) {
        if (indirect)
            CYPDF_object_set_indirect(object_null);
        CYPDF_object_set_class(object_null, CYPDF_OBJECT_CLASS_NULL);
    }

    return object_null;
}

void CYPDF_object_null_free(CYPDF_ObjectNull* object_null) {
    assert(object_null != NULL);

    free(object_null);
}

void CYPDF_object_null_print(FILE* file_stream, CYPDF_ObjectNull* object_null __attribute_maybe_unused__) {
    assert(file_stream != NULL);
    assert(object_null != NULL);

    fprintf(file_stream, "null");
}
