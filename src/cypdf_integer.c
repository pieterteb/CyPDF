#include "cypdf_object.h"

#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "cypdf_limits.h"


CYPDF_ObjectInteger* CYPDF_object_integer_new(bool indirect, int32_t value) {
    static_assert(INT32_MAX == CYPDF_INTEGER_MAX && INT32_MIN == CYPDF_INTEGER_MIN);

    CYPDF_ObjectInteger* object_integer = calloc(1, sizeof(*object_integer));

    if (object_integer) {
        if (indirect)
            CYPDF_object_set_indirect(object_integer);
        CYPDF_object_set_class(object_integer, CYPDF_OBJECT_CLASS_INTEGER);

        object_integer->value = value;
    }

    return object_integer;
}

void CYPDF_object_integer_free(CYPDF_ObjectInteger* object_integer) {
    assert(object_integer != NULL);

    free(object_integer);
}

void CYPDF_object_integer_print(FILE* file_stream, CYPDF_ObjectInteger* object_integer) {
    assert(file_stream != NULL);
    assert(object_integer != NULL);

    fprintf(file_stream, "%d", object_integer->value);
}
