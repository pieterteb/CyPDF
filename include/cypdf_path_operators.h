#ifndef CYPDF_GRAPHICS_H
#define CYPDF_GRAPHICS_H


#include <stddef.h>

#include "cypdf_color.h"
#include "cypdf_graphics_state.h"
#include "cypdf_memmgr.h"
#include "cypdf_operators.h"
#include "cypdf_print.h"
#include "cypdf_types.h"



typedef struct CYPDF_Path {
    CYPDF_Operator**    operators;
    size_t              operator_count;

    CYPDF_Point         current_point;
    CYPDF_Point         current_subpath_point;

    CYPDF_MemMgr*       memmgr;
} CYPDF_Path;


CYPDF_Path* CYPDF_NewPath(void);

void CYPDF_FreePath(CYPDF_Path* path);

void CYPDF_PrintPath(CYPDF_Channel* const restrict channel, const CYPDF_Path* const restrict path);


void CYPDF_PathBegin(CYPDF_Path* const restrict path, const CYPDF_Point start_point);

void CYPDF_PathLineseg(CYPDF_Path* const restrict path, const CYPDF_Point end_point);

void CYPDF_PathCBezier(CYPDF_Path* const restrict path, const CYPDF_Point ctrl_point1, const CYPDF_Point ctrl_point2, const CYPDF_Point end_point);

void CYPDF_PathVBezier(CYPDF_Path* const restrict path, const CYPDF_Point ctrl_point2, const CYPDF_Point end_point);

void CYPDF_PathYBezier(CYPDF_Path* const restrict path, const CYPDF_Point ctrl_point1, const CYPDF_Point end_point);

void CYPDF_PathClose(CYPDF_Path* const restrict path);

void CYPDF_PathRect(CYPDF_Path* const restrict path, const CYPDF_Point lowleft_corner, const float width, const float height);


void CYPDF_PathClip(CYPDF_Path* const restrict path, const enum CYPDF_OPERATOR_TYPE clip_operator);

void CYPDF_PathPaint(CYPDF_Path* const restrict path, const enum CYPDF_OPERATOR_TYPE paint_operator);


void CYPDF_PathSave(CYPDF_Path* const restrict path);

void CYPDF_PathRestore(CYPDF_Path* const restrict path);

void CYPDF_PathTransformMatrix(CYPDF_Path* const restrict path, const float a, const float b, const float c, const float d, const float e, const float f);

void CYPDF_PathLineWidth(CYPDF_Path* const restrict path, const float line_width);

void CYPDF_PathLineCap(CYPDF_Path* const restrict path, const int line_cap);

void CYPDF_PathLineJoin(CYPDF_Path* const restrict path, const int line_join);

void CYPDF_PathMiterLimit(CYPDF_Path* const restrict path, const float miter_limit);

void CYPDF_PathDashPattern(CYPDF_Path* const restrict path, const int* const dash_array, const size_t dash_array_size, const int dash_phase);

void CYPDF_PathIntent(CYPDF_Path* const restrict path, const char intent[restrict static 1]);

void CYPDF_PathFlatness(CYPDF_Path* const restrict path, const float flatness);

void CYPDF_PathGFXState(CYPDF_Path* const restrict path, CYPDF_ObjGFXState* const restrict gfx_state);


void CYPDF_PathLineColorSpace(CYPDF_Path* const restrict path, const char color_space[restrict static 1]);

void CYPDF_PathFillColorSpace(CYPDF_Path* const restrict path, const char color_space[restrict static 1]);

void CYPDF_PathLineColor(CYPDF_Path* const restrict path, CYPDF_Object** const restrict operands, const size_t operand_count);

void CYPDF_PathFillColor(CYPDF_Path* const restrict path, CYPDF_Object** const restrict operands, const size_t operand_count);

void CYPDF_PathLineGray(CYPDF_Path* const restrict path, const float gray);

void CYPDF_PathFillGray(CYPDF_Path* const restrict path, const float gray);

void CYPDF_PathLineRGB(CYPDF_Path* const restrict path, const CYPDF_RGB rgb);

void CYPDF_PathFillRGB(CYPDF_Path* const restrict path, const CYPDF_RGB rgb);

void CYPDF_PathLineCMYK(CYPDF_Path* const restrict path, const CYPDF_CMYK cmyk);

void CYPDF_PathFillCMYK(CYPDF_Path* const restrict path, const CYPDF_CMYK cmyk);



#endif /* CYPDF_GRAPHICS_H */
