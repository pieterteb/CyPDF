#include <stdlib.h>
#include <string.h>

#include "cypdf_string.h"
#include "cypdf_log.h"
#include "cypdf_memory.h"
#include "cypdf_object.h"
#include "cypdf_print.h"
#include "cypdf_types.h"



CYPDF_ObjString* CPYDF_NewString(CYPDF_MemMgr* const restrict memmgr, const enum CYPDF_STRING_TYPE type, const char* restrict value) {
    CYPDF_TRACE;

    CYPDF_ObjString* string = (CYPDF_ObjString*)CYPDF_GetMem(memmgr, sizeof(CYPDF_ObjString));

    if (string) {
        string->header.class = CYPDF_OBJ_CLASS_STRING;

        string->type = type;
        string->value = CYPDF_malloc(strlen(value) + 1);
        strcpy(string->value, value);
    }

    return string;
}

void CYPDF_FreeString(CYPDF_Object* obj) {
    CYPDF_TRACE;

    if (obj) {
        CYPDF_ObjString* string = (CYPDF_ObjString*)obj;

        free(string->value);
        free(string);
    }
}

void CYPDF_PrintString(CYPDF_Channel* const restrict channel, const CYPDF_Object* const obj) {
    CYPDF_TRACE;

    if (channel && obj) {
        CYPDF_ObjString* string = (CYPDF_ObjString*)obj;

        switch (string->type)
        {
        case CYPDF_STRTYPE_BYTE:
            CYPDF_ChannelPrint(channel, "<%s>", string->value);
            break;
        default:
            CYPDF_ChannelPrint(channel, "(%s)", string->value);
            break;
        }
    }    
}


char* CYPDF_StringGet(const CYPDF_ObjString* const restrict string) {
    CYPDF_TRACE;

    if (string) {
        return string->value;
    }

    return NULL;
}
