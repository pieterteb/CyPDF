#ifndef CYPDF_GRAPHICS_STATE_H
#define CYPDF_GRAPHICS_STATE_H


#include "cypdf_dict.h"
#include "cypdf_memmgr.h"



#define CYPDF_LINE_WIDTH_DEFAULT            1.0f
#define CYPDF_MITER_LIMIT_DEFAULT           10.0f
#define CYPDF_DASH_PHASE_DEFAULT            0

/* Line Cap Styles */
#define CYPDF_LINE_CAP_BUTT                 0       /* The stroke is squared off at the endpoint of the path. There is no projection beyond the end of the path. */
#define CYPDF_LINE_CAP_ROUND                1       /* A semicircular arc with a diameter equal to the line width is drawn around the endpoint and filled in. */
#define CYPDF_LINE_CAP_PROJECTIVE_SQUARE    2       /* The stroke continues beyond the endpoint of the path for a distance equal to half the line width and is squared off. */
#define CYPDF_LINE_CAP_DEFAULT              CYPDF_LINE_CAP_BUTT

/* Line Join Styles */
#define CYPDF_LINE_JOIN_MITER               0       /* The outer edges of the strokes for the two segments are extended until they meet at an angle, as in a picture frame. If the segments meet at too sharp an angle, a bevel join is used instead. */
#define CYPDF_LINE_JOIN_ROUND               1       /* An arc of a circle with a diameter equal to the line width is drawn around the point where the two segments meet, connecting the outer edges of the strokes for the two segments. This pieslice-shaped figure is filled in, producing a rounded corner. */
#define CYPDF_LINE_JOIN_BEVEL               2       /* The two segments are finished with butt caps and the resulting notch beyond the ends of the segments is filled with a triangle. */
#define CYPDF_LINE_JOIN_DEFAULT             CYPDF_LINE_JOIN_MITER



typedef CYPDF_ObjDict CYPDF_ObjGraphicsState;
typedef CYPDF_ObjGraphicsState CYPDF_ObjGFXState;


CYPDF_ObjGFXState* CYPDF_NewGFXState(CYPDF_MemMgr* const restrict memmgr);


void CYPDF_GFXStateLineWidth(CYPDF_ObjGFXState* const restrict gfx_state, const float line_width);

void CYPDF_GFXStateLineCap(CYPDF_ObjGFXState* const restrict gfx_state, const int line_cap);

void CYPDF_GFXStateLineJoin(CYPDF_ObjGFXState* const restrict gfx_state, const int line_join);

void CYPDF_GFXStateMiterLimit(CYPDF_ObjGFXState* const restrict gfx_state, const float miter_limit);

void CYPDF_GFXStateDashPattern(CYPDF_ObjGFXState* const restrict gfx_state, const int* const dash_array, const size_t dash_array_size, const int dash_phase);



#endif /* CYPDF_GRAPHICS_STATE */
