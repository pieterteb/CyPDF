#include "cypdf_resources.h"
#include "cypdf_dict.h"
#include "cypdf_dict_parameters.h"
#include "cypdf_graphics_state.h"
#include "cypdf_log.h"
#include "cypdf_memmgr.h"



CYPDF_ObjResources* CYPDF_NewResources(CYPDF_MemMgr* const restrict memmgr) {
    CYPDF_TRACE;

    CYPDF_ObjResources* resources = CYPDF_NewDict(memmgr);

    if (resources) {
        resources->header.subclass = CYPDF_OBJ_SUBCLASS_RESOURCES;
    }

    return resources;
}


void CYPDF_ResourcesAddGFXState(CYPDF_ObjResources* const restrict resources, CYPDF_ObjGFXState* const restrict gfx_state) {
    CYPDF_TRACE;

    if (resources) {
        CYPDF_ObjDict* gfx_state_dict;
        if (resources->count < CYPDF_RESOURCE_GFX_STATE_I - 1U) {
            gfx_state_dict = CYPDF_NewDict(resources->memmgr);
            CYPDF_DictSetAtIndex(resources, CYPDF_RESOURCE_GFX_STATE_I, CYPDF_GFX_STATE_TYPE_K, gfx_state_dict);
        } else {
            gfx_state_dict = (CYPDF_ObjDict*)resources->values[CYPDF_RESOURCE_GFX_STATE_I];
        }
        char entry[sizeof(CYPDF_RESOURCES_GFXSTATE_ENUM) + 16] = { 0 };
        sprintf(entry, "%s%zu", CYPDF_RESOURCES_GFXSTATE_ENUM, gfx_state_dict->count);
        CYPDF_DictAppend(gfx_state_dict, entry, gfx_state);
    }
}
