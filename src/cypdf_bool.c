#include <stdbool.h>

#include "cypdf_bool.h"
#include "cypdf_log.h"
#include "cypdf_memmgr.h"
#include "cypdf_object.h"
#include "cypdf_print.h"
#include "cypdf_types.h"



CYPDF_ObjBool* CYPDF_NewBool(CYPDF_MemMgr* const restrict memmgr, const bool value) {
    CYPDF_TRACE;

    CYPDF_ObjBool* boolean = (CYPDF_ObjBool*)CYPDF_GetMem(memmgr, sizeof(CYPDF_ObjBool));

    if (boolean) {
        boolean->header.class = CYPDF_OBJ_CLASS_BOOL;
        boolean->value = value;
    }

    return boolean;
}

void CYPDF_PrintBool(CYPDF_Channel* const restrict channel, const CYPDF_Object* const obj) {
    CYPDF_TRACE;

    if (channel && obj) {
        CYPDF_ObjBool* boolean = (CYPDF_ObjBool*)obj;

        if (boolean->value) {
            CYPDF_ChannelPrint(channel, "true");
        } else {
            CYPDF_ChannelPrint(channel, "false");
        }
    }    
}
