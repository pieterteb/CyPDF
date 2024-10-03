#include "cypdf_number.h"
#include "cypdf_log.h"
#include "cypdf_memmgr.h"
#include "cypdf_object.h"
#include "cypdf_print.h"
#include "cypdf_types.h"



CYPDF_ObjNumber* CYPDF_NewNumber(CYPDF_MemMgr* const restrict memmgr, const float value) {
    CYPDF_TRACE;

    CYPDF_ObjNumber* number = (CYPDF_ObjNumber*)CYPDF_GetMem(memmgr, sizeof(CYPDF_ObjNumber));

    if (number) {
        number->header.class = CYPDF_OBJ_CLASS_NUMBER;
        number->value = value;
    }

    return number;
}

void CYPDF_PrintNumber(CYPDF_Channel* const restrict channel, const CYPDF_Object* const obj) {
    CYPDF_TRACE;

    if (channel && obj) {
        CYPDF_ObjNumber* number = (CYPDF_ObjNumber*)obj;

        CYPDF_ChannelPrint(channel, "%g", number->value);
    }
}


void CYPDF_NumberSetValue(CYPDF_ObjNumber* const restrict number, const float value) {
    CYPDF_TRACE;

    if (number) {
        number->value = value;
    }
}

float CYPDF_NumberGetValue(const CYPDF_ObjNumber* const number) {
    CYPDF_TRACE;

    if (number) {
        return number->value;
    }

    return 0.0f;
}
