#include <stddef.h>
#include <string.h>

#include "cypdf_resource.h"
#include "cypdf_dict.h"
#include "cypdf_dict_parameters.h"
#include "cypdf_graphics_state.h"
#include "cypdf_log.h"
#include "cypdf_memory.h"
#include "cypdf_name.h"
#include "cypdf_types.h"
#include "cypdf_xobject.h"



static void CYPDF_ResourceAdd(CYPDF_ObjResource* restrict const resource, const size_t entry_index, const char entry_key_name[restrict static 1], const char entry_enum[restrict static 1], CYPDF_Object* restrict const obj);


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


static void CYPDF_ResourceAdd(CYPDF_ObjResource* restrict const resource, const size_t entry_index, const char entry_key_name[restrict static 1], const char entry_enum[restrict static 1], CYPDF_Object* restrict const obj) {
    CYPDF_TRACE;

    CYPDF_ObjDict* dict = NULL;
    if (!CYPDF_DictKeyAtIndex(resource, entry_index)) {
        dict = CYPDF_NewDict(resource->memmgr);
        CYPDF_DictSetAtIndex(resource, entry_index, entry_key_name, dict);
    } else {
        dict = CYPDF_DictValueAtIndex(resource, entry_index);
    }

    char* entry = CYPDF_calloc(strlen(entry_enum) + 16, sizeof(char));
    sprintf(entry, "%s%zu", entry_enum, CYPDF_DictLength(dict));
    CYPDF_DictAppend(dict, entry, obj);
}

void CYPDF_ResourceAddGFXState(CYPDF_ObjResource* const resource, CYPDF_ObjGFXState* const gfx_state) {
    CYPDF_TRACE;

    CYPDF_ResourceAdd(resource, CYPDF_RESOURCE_GFX_STATE_I, CYPDF_RESOURCE_GFX_STATE_K, CYPDF_RESOURCE_GFXSTATE_ENUM, gfx_state);
}

void CYPDF_ResourceAddXObject(CYPDF_ObjResource* const resource, CYPDF_ObjXObject* const xobject) {
    CYPDF_TRACE;

    CYPDF_ResourceAdd(resource, CYPDF_RESOURCE_XOBJECT_I, CYPDF_RESOURCE_XOBJECT_K, CYPDF_RESOURCE_XOBJECT_ENUM, xobject);
}
