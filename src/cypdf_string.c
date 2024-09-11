#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cypdf_string.h"
#include "cypdf_object.h"
#include "cypdf_utils.h"



CYPDF_ObjString* CPYDF_NewString(bool indirect, enum CYPDF_STRING_TYPE type, unsigned char* value, size_t valsize) {
    CYPDF_ObjString* string = (CYPDF_ObjString*)CYPDF_NewObj(indirect, CYPDF_OCLASS_STRING);
    if (string) {
        string->type = type;
        string->value = CYPDF_smalloc(valsize);

        /* If memory allocation failed, string->value is not initialized. */
        if (string->value) {
            memcpy(string->value, value, valsize);
            string->size = valsize;
        } else {
            string->size = 0;
        }
    }

    return string;
}

void CYPDF_PrintString(FILE* fp, CYPDF_Object* obj) {
    if (fp == NULL || obj == NULL) {
        return;
    }

    CYPDF_ObjString* string = (CYPDF_ObjString*)obj;

    switch (string->type)
    {
    case CYPDF_STRTYPE_BYTE:
        fputc('<', fp);
        fwrite(string->value, sizeof(string->value[0]), string->size, fp);
        fputc('>', fp);
        break;
    default:
        fputc('(', fp);
        fwrite(string->value, sizeof(string->value[0]), string->size, fp);
        fputc(')', fp);
        break;
    }
}

void CYPDF_FreeString(CYPDF_Object* obj) {
    if (obj) {
        CYPDF_ObjString* string = (CYPDF_ObjString*)obj;
        free(string->value);
        free(string);
    }
}
