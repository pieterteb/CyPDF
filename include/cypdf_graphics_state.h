#ifndef CYPDF_GRAPHICS_STATE_H
#define CYPDF_GRAPHICS_STATE_H


#include "cypdf_array.h"
#include "cypdf_bool.h"
#include "cypdf_color.h"
#include "cypdf_dict.h"
#include "cypdf_mmgr.h"
#include "cypdf_name.h"
#include "cypdf_number.h"
#include "cypdf_real.h"



#define CYPDF_LINE_WIDTH_DEFAULT            1.0f
#define CYPDF_LINE_CAP_DEFAULT              0
#define CYPDF_LINE_JOIN_DEFAULT             0
#define CYPDF_MITER_LIMIT_DEFAULT           10.0f


/* Unimplemented parameters are commented out. */
typedef struct CYPDF_GraphicsState {
    // CYPDF_ObjArray*     CTM; /* Current transformation matrix, which maps positions from user coordinates to device coordinates. */
    // UnknownType         clipping_path; /* The current clipping path, which defines the boundary against which all output is to be cropped. */
    CYPDF_ColorSpace    color_space; /* The current color space in which color values are to be interpreted. */
    // UnknownType         color; /* The current color to be used during painting operations. */
    // UnknownType         text_state; /* A set of nine graphics state parameters that pertain only to the painting of text. */
    CYPDF_ObjReal*      line_width; /* The thickness, in user space units, of paths to be stroked. */
    CYPDF_ObjNumber*    line_cap; /* A code specifying the shape of the endpoints for any open path that is stroked. */
    CYPDF_ObjNumber*    line_join; /* A code specifying the shape of joints between connected segments of a stroked path. */
    CYPDF_ObjReal*      miter_limit; /* The maximum length of mitered line joins for stroked paths. */
    struct {
        CYPDF_ObjArray*     pattern;
        CYPDF_ObjNumber*    phase;
    }                   dash_pattern; /* A description of the dash pattern to be used when paths are stroked. */
    // CYPDF_ObjName*      rendering_intent; /* The rendering intent to be used when converting CIE-based colors to device colors. */
    // CYPDF_ObjBool*      stroke_adjustment; /* A flag specifying whether to compensate for possible rasterization effects when stroking a path with a line width that is small relative to the pixel resolution of the output device. */
    // CYPDF_ObjArray*     blend_mode; /* The current blend mode to be used in the transparent imaging model. */
    // CYPDF_ObjDict*      soft_mask; /* A soft-mask dictionary specifying the mask shape or mask opacity values to be used in the transparent imaging model. */
    // CYPDF_ObjNumber*    alpha_constant; /* The constant shape or constant opacity value to be used in the transparent imaging model. */
    // CYPDF_ObjBool*      alpha_source; /* A flag specifying whether the current soft mask and alpha constant parameters are to be interpreted as shape values (true) or opacity values (false). */
} CYPDF_GFXState;


CYPDF_GFXState* CYPDF_NewGFXState(CYPDF_MMgr* const mmgr);

void CYPDF_FreeGFXState(CYPDF_GFXState* state);


void CYPDF_GFXStateSetColorSpace(CYPDF_GFXState* const state, const uint16_t color_space);

void CYPDF_GFXStateSetLineWidth(CYPDF_GFXState* const state, const float line_width);

void CYPDF_GFXStateSetLineCap(CYPDF_GFXState* const state, const int line_cap);

void CYPDF_GFXStateSetLineJoin(CYPDF_GFXState* const state, const int line_join);

void CYPDF_GFXStateSetMiterLimit(CYPDF_GFXState* const state, const float miter_limit);

void CYPDF_GFXStateSetDashPattern(CYPDF_GFXState* const state, const CYPDF_ObjArray* const pattern, const int phase);



#endif /* CYPDF_GRAPHICS_STATE_H */