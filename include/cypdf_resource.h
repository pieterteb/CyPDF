#ifndef CYPDF_RESOURCE_H
#define CYPDF_RESOURCE_H


#include <stddef.h>

#include "cypdf_dict.h"
#include "cypdf_graphics_state.h"
#include "cypdf_memory.h"
#include "cypdf_name.h"
#include "cypdf_types.h"



#define CYPDF_RESOURCES_GFXSTATE_ENUM   "G"
#define CYPDF_RESOURCES_XOBJECT_ENUM    "X"


typedef CYPDF_ObjDict CYPDF_ObjResource;


CYPDF_ObjResource* CYPDF_NewResource(CYPDF_MemMgr* const memmgr);


CYPDF_ObjName* CYPDF_ResourceGetName(CYPDF_ObjResource* const resource, const size_t entry_index, CYPDF_Object* const obj);


void CYPDF_ResourceAddGFXState(CYPDF_ObjResource* const resource, CYPDF_ObjGFXState* const gfx_state);



#endif /* CYPDF_RESOURCE_H */
