#ifndef CYPDF_RESOURCES_H
#define CYPDF_RESOURCES_H


#include <stddef.h>

#include "cypdf_dict.h"
#include "cypdf_graphics_state.h"
#include "cypdf_memory.h"
#include "cypdf_name.h"
#include "cypdf_types.h"



#define CYPDF_RESOURCES_GFXSTATE_ENUM   "G"


typedef CYPDF_ObjDict CYPDF_ObjResources;


CYPDF_ObjResources* CYPDF_NewResources(CYPDF_MemMgr* const memmgr);


CYPDF_ObjName* CYPDF_ResourcesGetName(CYPDF_ObjResources* const resources, const size_t entry_index, CYPDF_Object* const obj);


void CYPDF_ResourcesAddGFXState(CYPDF_ObjResources* const resources, CYPDF_ObjGFXState* const gfx_state);



#endif /* CYPDF_RESOURCES_H */
