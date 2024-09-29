#include <string.h>

#include "cypdf_name.h"
#include "cypdf_memmgr.h"
#include "cypdf_object.h"
#include "cypdf_print.h"
#include "cypdf_types.h"



CYPDF_ObjName* CYPDF_NewName(CYPDF_MemMgr* const restrict memmgr, const char value[restrict static 1]) {
    CYPDF_ObjName* name = (CYPDF_ObjName*)CYPDF_GetMem(memmgr, sizeof(CYPDF_ObjName));

    if (name) {
        name->header.class = CYPDF_OBJ_CLASS_NAME;
        strncpy(name->value, value, CYPDF_MAX_NAME_LEN);
        name->value[CYPDF_MAX_NAME_LEN] = 0;
    }

    return name;
}

void CYPDF_PrintName(CYPDF_Channel* const restrict channel, const CYPDF_Object* const obj) {
    if (channel && obj) {
        CYPDF_ObjName* name = (CYPDF_ObjName*)obj;

        CYPDF_ChannelPrint(channel, "/%s", name->value);
    }
}
