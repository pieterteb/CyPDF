#include <stddef.h>

#include "cypdf_resource.h"
#include "cypdf_dict.h"
#include "cypdf_dict_parameters.h"
#include "cypdf_graphics_state.h"
#include "cypdf_log.h"
#include "cypdf_memory.h"
#include "cypdf_name.h"
#include "cypdf_types.h"



CYPDF_ObjResource* CYPDF_NewResource(CYPDF_MemMgr* const memmgr) {
    CYPDF_TRACE;

    CYPDF_ObjResource* resource = CYPDF_NewDict(memmgr);

    resource->header.subclass = CYPDF_OBJ_SUBCLASS_RESOURCES;

    return resource;
}


CYPDF_ObjName* CYPDF_ResourceGetName(CYPDF_ObjResource* const resource, const size_t entry_index, CYPDF_Object* const obj) {
    CYPDF_ObjDict* obj_dict = CYPDF_DictValueAtIndex(resource, entry_index);

    size_t length = CYPDF_DictLength(obj_dict);
    for (size_t i = 0; i < length; ++i) {
        if (CYPDF_DictValueAtIndex(obj_dict, i) == obj) {
            return CYPDF_DictKeyAtIndex(obj_dict, i);
        }
    }

    return NULL;
}


void CYPDF_ResourceAddGFXState(CYPDF_ObjResource* const resource, CYPDF_ObjGFXState* const gfx_state) {
    CYPDF_TRACE;

    CYPDF_ObjDict* gfx_state_dict = NULL;
    if (!CYPDF_DictKeyAtIndex(resource, CYPDF_RESOURCE_GFX_STATE_I)) {
        gfx_state_dict = CYPDF_NewDict(resource->memmgr);
        CYPDF_DictSetAtIndex(resource, CYPDF_RESOURCE_GFX_STATE_I, CYPDF_RESOURCE_GFX_STATE_K, gfx_state_dict);
    } else {
        gfx_state_dict = CYPDF_DictValueAtIndex(resource, CYPDF_RESOURCE_GFX_STATE_I);
    }

    char entry[sizeof(CYPDF_RESOURCES_GFXSTATE_ENUM) + 16] = { 0 };
    sprintf(entry, "%s%zu", CYPDF_RESOURCES_GFXSTATE_ENUM, CYPDF_DictLength(gfx_state_dict));
    CYPDF_DictAppend(gfx_state_dict, entry, gfx_state);
}

void CYPDF_ResourceAddXObject() {
    
}
