#ifndef CYPDF_GRAPHICS_H
#define CYPDF_GRAPHICS_H


#include <stddef.h>

#include "cypdf_color.h"
#include "cypdf_graphics_state.h"
#include "cypdf_image.h"
#include "cypdf_list.h"
#include "cypdf_memory.h"
#include "cypdf_operators.h"
#include "cypdf_pages.h"
#include "cypdf_print.h"
#include "cypdf_types.h"



typedef struct CYPDF_Graphic {
    CYPDF_List*     operator_list;

    CYPDF_MemMgr*   memmgr;
} CYPDF_Graphic;


CYPDF_Graphic* CYPDF_NewGraphic(void);

void CYPDF_FreeGraphic(void* _graphic);

void CYPDF_PrintGraphic(CYPDF_Channel* const channel, const CYPDF_Graphic* const graphic);


void CYPDF_GraphicSetPage(CYPDF_Graphic* const graphic, CYPDF_ObjPage* const page);


void CYPDF_GraphicBegin(CYPDF_Graphic* const graphic, const CYPDF_Point start_point);

void CYPDF_GraphicLineseg(CYPDF_Graphic* const restrict graphic, const CYPDF_Point end_point);

void CYPDF_GraphicCBezier(CYPDF_Graphic* const restrict graphic, const CYPDF_Point ctrl_point1, const CYPDF_Point ctrl_point2, const CYPDF_Point end_point);

void CYPDF_GraphicVBezier(CYPDF_Graphic* const restrict graphic, const CYPDF_Point ctrl_point2, const CYPDF_Point end_point);

void CYPDF_GraphicYBezier(CYPDF_Graphic* const restrict graphic, const CYPDF_Point ctrl_point1, const CYPDF_Point end_point);

void CYPDF_GraphicClose(CYPDF_Graphic* const restrict graphic);

void CYPDF_GraphicRect(CYPDF_Graphic* const restrict graphic, const CYPDF_Point lowleft_corner, const float width, const float height);


void CYPDF_GraphicClip(CYPDF_Graphic* const restrict graphic, const enum CYPDF_OPERATOR_TYPE clip_operator);

void CYPDF_GraphicPaint(CYPDF_Graphic* const restrict graphic, const enum CYPDF_OPERATOR_TYPE paint_operator);


void CYPDF_GraphicSave(CYPDF_Graphic* const restrict graphic);

void CYPDF_GraphicRestore(CYPDF_Graphic* const restrict graphic);

void CYPDF_GraphicTransMatrix(CYPDF_Graphic* const restrict graphic, const CYPDF_TransMatrix cm);

void CYPDF_GraphicLineWidth(CYPDF_Graphic* const restrict graphic, const float line_width);

void CYPDF_GraphicLineCap(CYPDF_Graphic* const restrict graphic, const int line_cap);

void CYPDF_GraphicLineJoin(CYPDF_Graphic* const restrict graphic, const int line_join);

void CYPDF_GraphicMiterLimit(CYPDF_Graphic* const restrict graphic, const float miter_limit);

void CYPDF_GraphicDashPattern(CYPDF_Graphic* const restrict graphic, const int* const dash_array, const size_t dash_array_size, const int dash_phase);

void CYPDF_GraphicIntent(CYPDF_Graphic* const restrict graphic, const char intent[restrict static 1]);

void CYPDF_GraphicFlatness(CYPDF_Graphic* const restrict graphic, const float flatness);

void CYPDF_GraphicGFXState(CYPDF_Graphic* const restrict graphic, CYPDF_ObjGFXState* const restrict gfx_state);


void CYPDF_GraphicLineColorSpace(CYPDF_Graphic* const restrict graphic, const char color_space[restrict static 1]);

void CYPDF_GraphicFillColorSpace(CYPDF_Graphic* const restrict graphic, const char color_space[restrict static 1]);

void CYPDF_GraphicLineColor(CYPDF_Graphic* const restrict graphic, CYPDF_Object** const restrict operands, const size_t operand_count);

void CYPDF_GraphicFillColor(CYPDF_Graphic* const restrict graphic, CYPDF_Object** const restrict operands, const size_t operand_count);

void CYPDF_GraphicLineGray(CYPDF_Graphic* const restrict graphic, const float gray);

void CYPDF_GraphicFillGray(CYPDF_Graphic* const restrict graphic, const float gray);

void CYPDF_GraphicLineRGB(CYPDF_Graphic* const restrict graphic, const CYPDF_RGB rgb);

void CYPDF_GraphicFillRGB(CYPDF_Graphic* const restrict graphic, const CYPDF_RGB rgb);

void CYPDF_GraphicLineCMYK(CYPDF_Graphic* const restrict graphic, const CYPDF_CMYK cmyk);

void CYPDF_GraphicFillCMYK(CYPDF_Graphic* const restrict graphic, const CYPDF_CMYK cmyk);


void CYPDF_GraphicImage(CYPDF_Graphic* const graphic, CYPDF_ObjImage* const image, const CYPDF_TransMatrix matrix);



#endif /* CYPDF_GRAPHICS_H */
