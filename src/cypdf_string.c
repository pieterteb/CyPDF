#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cypdf_string.h"
#include "cypdf_object.h"
#include "cypdf_utils.h"



CYPDF_ObjString* CPYDF_NewString(CYPDF_MMgr* const mmgr, const enum CYPDF_STRING_TYPE type, const char* restrict val) {
    CYPDF_ObjString* string = (CYPDF_ObjString*)CYPDF_GetMem(mmgr, sizeof(CYPDF_ObjString));

    if (string) {
        CYPDF_InitHeader(string, CYPDF_OCLASS_STRING);
        string->type = type;
        string->val = CYPDF_smalloc(strlen(val) + 1);

        strcpy(string->val, val);
    }

    return string;
}

char* CYPDF_GetString(const CYPDF_ObjString* const string) {
    if (string) {
        return string->val;
    }

    return NULL;
}

void CYPDF_PrintString(FILE* restrict fp, const CYPDF_Object* const obj) {
    if (fp && obj) {
        CYPDF_ObjString* string = (CYPDF_ObjString*)obj;

        switch (string->type)
        {
        case CYPDF_STRTYPE_BYTE:
            fputc('<', fp);
            fprintf(fp, "%s", string->val);
            fputc('>', fp);
            break;
        default:
            fputc('(', fp);
            fprintf(fp, "%s", string->val);
            fputc(')', fp);
            break;
        }
    }    
}

void CYPDF_FreeString(CYPDF_Object* obj) {
    if (obj) {
        CYPDF_ObjString* string = (CYPDF_ObjString*)obj;

        free(string->val);
        free(string);
    }
}
