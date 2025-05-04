#include "cypdf_object.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>



CYPDF_ObjectArray* CYPDF_object_array_new(bool indirect) {
    CYPDF_ObjectArray* object_array = calloc(1, sizeof(*object_array));

    if (object_array) {
        if (indirect)
            CYPDF_object_set_indirect(object_array);
        CYPDF_object_set_class(object_array, CYPDF_OBJECT_CLASS_ARRAY);
    }

    return object_array;
}

void CYPDF_object_array_free(CYPDF_ObjectArray* object_array) {
    assert(object_array != NULL);

    free(object_array->objects);
    free(object_array);
}

void CYPDF_obj_array_print(FILE* file_stream, CYPDF_ObjectArray* object_array) {
    assert(file_stream != NULL);
    assert(object_array != NULL);

    fputc('[', file_stream);
    for (size_t i = 0; i < object_array->object_count; ++i) {
        if (CYPDF_object_is_indirect(object_array->objects[i]))
            CYPDF_object_print_reference(object_array->objects[i]);
        else
            CYPDF_object_print_direct(object_array->objects[i]);

        if (i + 1 == object_array->object_count)
            break;
        
        fputc(' ', file_stream);
    }
    fputc(']', file_stream);
}


void CYPDF_object_array_append(CYPDF_ObjectArray* object_array, CYPDF_Object* object) {
    assert(object_array != NULL);
    assert(object != NULL);

    if (object_array->object_count == object_array->size) {
        object_array->objects = realloc(object_array->objects, (object_array->size + 1) * sizeof(*object_array->objects));
        
        if (!object_array->objects)
            return;
        else
            ++object_array->size;
    }
    object_array->objects[object_array->object_count] = object;
    ++object_array->object_count;
}
