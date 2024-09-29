#include "cypdf_graphics_state.h"
#include "cypdf_dict.h"
#include "cypdf_dict_parameters.h"
#include "cypdf_integer.h"
#include "cypdf_memmgr.h"
#include "cypdf_name.h"
#include "cypdf_number.h"
#include "cypdf_object.h"



CYPDF_ObjGFXState* CYPDF_NewGFXStateDict(CYPDF_MemMgr* const restrict memmgr) {
    CYPDF_ObjGFXState* gfx_state = CYPDF_NewDict(memmgr);

    if (gfx_state) {
        gfx_state->header.subclass = CYPDF_OBJ_SUBCLASS_GFX_STATE;

        CYPDF_DictAppend(gfx_state, CYPDF_TYPE_K, CYPDF_NewName(gfx_state->memmgr, CYPDF_GFX_STATE_TYPE_K));
    }

    return gfx_state;
}


void CYPDF_GFXStateSetLineWidth(CYPDF_ObjGFXState* const restrict gfx_state, const float line_width) {
    if (gfx_state) {
        CYPDF_DictAppend(gfx_state, CYPDF_GFX_STATE_LINE_WIDTH_K, CYPDF_NewNumber(gfx_state->memmgr, line_width));
    }
}

void CYPDF_GFXStateSetLineCap(CYPDF_ObjGFXState* const restrict gfx_state, const int line_cap) {
    if (gfx_state) {
        CYPDF_DictAppend(gfx_state, CYPDF_GFX_STATE_LINE_CAP_K, CYPDF_NewInteger(gfx_state->memmgr, line_cap));
    }
}

void CYPDF_GFXStateSetLineJoin(CYPDF_ObjGFXState* const restrict gfx_state, const int line_join) {
    if (gfx_state) {
        CYPDF_DictAppend(gfx_state, CYPDF_GFX_STATE_LINE_JOIN_K, CYPDF_NewInteger(gfx_state->memmgr, line_join));
    }
}

void CYPDF_GFXStateSetMiterLimit(CYPDF_ObjGFXState* const restrict gfx_state, const float miter_limit) {
    if (gfx_state) {
        CYPDF_DictAppend(gfx_state, CYPDF_GFX_STATE_MITER_LIMIT_K, CYPDF_NewNumber(gfx_state->memmgr, miter_limit));
    }
}
