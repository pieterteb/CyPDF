#include <stdlib.h>

#include "cypdf_null.h"
#include "cypdf_log.h"
#include "cypdf_memory.h"
#include "cypdf_object.h"
#include "cypdf_types.h"



CYPDF_ObjNull* CYPDF_NewNull(CYPDF_MemMgr* const restrict memmgr) {
    CYPDF_TRACE;

    CYPDF_ObjNull* null = (CYPDF_ObjNull*)CYPDF_GetMem(memmgr, sizeof(CYPDF_ObjNull));

    if (null) {
        null->header.class = CYPDF_OBJ_CLASS_NULL;
    }

    return null;
}

void CYPDF_FreeNull(CYPDF_Object* obj) {
    CYPDF_TRACE;

    if (obj) {
        CYPDF_ObjNull* null = (CYPDF_ObjNull*)obj;

        free(null);
    }
}

void CYPDF_PrintNull(CYPDF_Channel* const restrict channel, const CYPDF_Object* const restrict obj __attribute_maybe_unused__) {
    CYPDF_TRACE;

    CYPDF_ChannelPrint(channel, "null");
}
