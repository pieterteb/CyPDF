#include "stdint.h"

#include "cypdf_graphics_state.h"
#include "cypdf_array.h"
#include "cypdf_color.h"
#include "cypdf_mmgr.h"
#include "cypdf_name.h"
#include "cypdf_number.h"
#include "cypdf_real.h"
#include "cypdf_utils.h"



CYPDF_GFXState* CYPDF_NewGFXState(CYPDF_MMgr* const mmgr) {
    CYPDF_GFXState* state = CYPDF_smalloc(sizeof(CYPDF_GFXState));

    if (state) {
        state->color_space = (CYPDF_ColorSpace){
            .type = CYPDF_COLOR_SPACE_DEFAULT
        };

        state->line_width = CYPDF_NewReal(mmgr, CYPDF_LINE_WIDTH_DEFAULT);
        state->line_cap = CYPDF_NewNumber(mmgr, CYPDF_LINE_CAP_DEFAULT);
        state->line_join = CYPDF_NewNumber(mmgr, CYPDF_LINE_JOIN_DEFAULT);
        state->miter_limit = CYPDF_NewReal(mmgr, CYPDF_MITER_LIMIT_DEFAULT);

        /* Describes a solid line. */
        state->dash_pattern.pattern = CYPDF_NewArray(mmgr);
        state->dash_pattern.phase = 0;
    }

    return state;
}

void CYPDF_FreeGFXState(CYPDF_GFXState* state) {
    if (state) {
        free(state);
    }
}

void CYPDF_GFXStateSetColorSpace(CYPDF_GFXState* const state, const uint16_t color_space) {
    if (state) {
        state->color_space.type = color_space;
    }
}

void CYPDF_GFXStateSetLineWidth(CYPDF_GFXState* const state, const float line_width) {
    if (state) {
        CYPDF_RealSetValue(state->line_width, line_width);
    }
}

void CYPDF_GFXStateSetLineCap(CYPDF_GFXState* const state, const int line_cap) {
    if (state) {
        CYPDF_NumberSetValue(state->line_cap, line_cap);
    }
}

void CYPDF_GFXStateSetLineJoin(CYPDF_GFXState* const state, const int line_join) {
    if (state) {
        CYPDF_NumberSetValue(state->line_join, line_join);
    }
}

void CYPDF_GFXStateSetMiterLimit(CYPDF_GFXState* const state, const float miter_limit) {
    if (state) {
        CYPDF_RealSetValue(state->miter_limit, miter_limit);
    }
}

void CYPDF_GFXStateSetDashPattern(CYPDF_GFXState* const state, const CYPDF_ObjArray* const pattern, const int phase) {
    if (state) {
        state->dash_pattern.pattern = pattern;
        state->dash_pattern.phase = phase;
    }
}
