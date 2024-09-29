#include "cypdf_integer.h"
#include "cypdf_memmgr.h"
#include "cypdf_object.h"
#include "cypdf_print.h"
#include "cypdf_types.h"



CYPDF_ObjInteger* CYPDF_NewInteger(CYPDF_MemMgr* const restrict memmgr, const int value) {
    CYPDF_ObjInteger* integer = (CYPDF_ObjInteger*)CYPDF_GetMem(memmgr, sizeof(CYPDF_ObjInteger));

    if (integer) {
        integer->header.class = CYPDF_OBJ_CLASS_INTEGER;

        integer->value = value;
    }

    return integer;
}

void CYPDF_PrintInteger(CYPDF_Channel* const restrict channel, const CYPDF_Object* const obj) {
    if (channel && obj) {
        CYPDF_ObjInteger* integer = (CYPDF_ObjInteger*)obj;

        CYPDF_ChannelPrint(channel, "%d", integer->value);
    }
}


void CYPDF_IntegerSetValue(CYPDF_ObjInteger* const restrict integer, const int value) {
    if (integer) {
        integer->value = value;
    }
}

int CYPDF_IntegerGetValue(const CYPDF_ObjInteger* const restrict integer) {
    if (integer) {
        return integer->value;
    }

    return 0;
}