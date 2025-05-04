#include "cypdf_object.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "cypdf_limits.h"



CYPDF_ObjectString* CPYDF_object_string_new(bool indirect, enum CYPDF_StringType string_type, enum CYPDF_StringFormat string_format, const uint8_t* bytes, unsigned byte_count) {
    CYPDF_ObjectString* object_string = calloc(1, sizeof(*object_string));

    if (object_string) {
        if (indirect)
            CYPDF_object_set_indirect(object_string);
        CYPDF_object_set_class(object_string, CYPDF_OBJECT_CLASS_STRING);

        assert(CYPDF_STRING_TYPE_DEFAULT <= object_string->type && object_string->type < CYPDF_STRING_TYPE_COUNT);
        assert(CYPDF_STRING_FORMAT_DEFAULT <= object_string->format && object_string->format < CYPDF_STRING_FORMAT_COUNT);

        object_string->type = string_type;
        object_string->format = string_format;
        if (byte_count) {
            assert(bytes != NULL);

            byte_count = CYPDF_STRING_LENGTH_MAX < byte_count ? CYPDF_STRING_LENGTH_MAX : byte_count;
            object_string->bytes = malloc(byte_count);

            if (object_string->bytes) {
                memcpy(object_string->bytes, bytes, byte_count);
                object_string->byte_count = byte_count;
            } else {
                free(object_string);
                return NULL;
            }
        }
    }

    return object_string;
}

void CYPDF_object_string_free(CYPDF_ObjectString* object_string) {
    assert(object_string != NULL);

    free(object_string->bytes);
    free(object_string);
}

void CYPDF_object_string_print(FILE* file_stream, CYPDF_ObjectString* object_string) {
    assert(file_stream != NULL);
    assert(object_string != NULL);

    assert(CYPDF_STRING_TYPE_DEFAULT <= object_string->type && object_string->type < CYPDF_STRING_TYPE_COUNT);
    assert(CYPDF_STRING_FORMAT_DEFAULT <= object_string->format && object_string->format < CYPDF_STRING_FORMAT_COUNT);

    uint8_t left_bracket = 0;
    uint8_t right_bracket = 0;
    switch (object_string->format) {
        case CYPDF_STRING_FORMAT_LITERAL:
            left_bracket = '<';
            right_bracket = '>';
        default:
            left_bracket = '(';
            right_bracket = ')';
            break;
    }

    fputc(left_bracket, file_stream);
    fwrite(object_string->bytes, sizeof(object_string->bytes[0]), object_string->byte_count, file_stream);
    fputc(right_bracket, file_stream);
}
