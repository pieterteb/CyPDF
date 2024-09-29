#ifndef CYPDF_GRAPHICS_STATE_H
#define CYPDF_GRAPHICS_STATE_H


#include "cypdf_dict.h"
#include "cypdf_memmgr.h"



typedef CYPDF_ObjDict CYPDF_ObjGraphicsState;
typedef CYPDF_ObjGraphicsState CYPDF_ObjGFXState;


CYPDF_ObjGFXState* CYPDF_NewGFXStateDict(CYPDF_MemMgr* const restrict memmgr);


void CYPDF_GFXStateSetLineWidth(CYPDF_ObjGFXState* const restrict gfx_state, const float line_width);

void CYPDF_GFXStateSetLineCap(CYPDF_ObjGFXState* const restrict gfx_state, const int line_cap);

void CYPDF_GFXStateSetLineJoin(CYPDF_ObjGFXState* const restrict gfx_state, const int line_join);

void CYPDF_GFXStateSetMiterLimit(CYPDF_ObjGFXState* const restrict gfx_state, const float miter_limit);



#endif /* CYPDF_GRAPHICS_STATE */
