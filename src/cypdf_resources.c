#include "cypdf_resources.h"
#include "cypdf_dict.h"
#include "cypdf_dict_parameters.h"
#include "cypdf_graphics_state.h"
#include "cypdf_memmgr.h"



CYPDF_ObjResources* CYPDF_NewResources(CYPDF_MemMgr* const restrict memmgr) {
    CYPDF_ObjResources* resources = CYPDF_NewDict(memmgr);

    if (resources) {
        resources->header.subclass = CYPDF_OBJ_SUBCLASS_RESOURCES;
    }

    return resources;
}

void CYPDF_ResourcesSetGFXState(CYPDF_ObjResources* const restrict resources, CYPDF_ObjGFXState* const restrict gfx_state) {
    if (resources) {
        CYPDF_DictAppend(resources, CYPDF_RESOURCE_GFX_STATE_K, gfx_state);
    }
}
