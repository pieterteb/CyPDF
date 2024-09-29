#ifndef CYPDF_RESOURCES_H
#define CYPDF_RESOURCES_H


#include "cypdf_dict.h"
#include "cypdf_graphics_state.h"
#include "cypdf_memmgr.h"



typedef CYPDF_ObjDict CYPDF_ObjResources;


CYPDF_ObjResources* CYPDF_NewResources(CYPDF_MemMgr* const restrict memmgr);

void CYPDF_ResourcesSetGFXState(CYPDF_ObjResources* const restrict resources, CYPDF_ObjGFXState* const restrict gfx_state);



#endif /* CYPDF_RESOURCES_H */
