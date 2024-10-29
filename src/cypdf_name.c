#include <string.h>

#include "cypdf_name.h"
#include "cypdf_log.h"
#include "cypdf_memory.h"
#include "cypdf_object.h"
#include "cypdf_print.h"
#include "cypdf_types.h"



CYPDF_ObjName* CYPDF_NewName(CYPDF_MemMgr* const restrict memmgr, const char* restrict value) {
    CYPDF_TRACE;

    CYPDF_ObjName* name = (CYPDF_ObjName*)CYPDF_GetMem(memmgr, sizeof(CYPDF_ObjName));

    if (name) {
        name->header.class = CYPDF_OBJ_CLASS_NAME;
        strncpy(name->value, value, CYPDF_MAX_NAME_LEN);
        name->value[CYPDF_MAX_NAME_LEN] = 0;
    }

    return name;
}

void CYPDF_PrintName(CYPDF_Channel* const restrict channel, const CYPDF_Object* const obj) {
    CYPDF_TRACE;

    if (channel && obj) {
        CYPDF_ObjName* name = (CYPDF_ObjName*)obj;

        CYPDF_ChannelPrint(channel, "/%s", name->value);
    }
}
