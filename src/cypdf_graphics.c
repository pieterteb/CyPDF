#include <stdlib.h>

#include "cypdf_graphics.h"
#include "cypdf_array.h"
#include "cypdf_color.h"
#include "cypdf_consts.h"
#include "cypdf_dict_parameters.h"
#include "cypdf_doc.h"
#include "cypdf_graphics_state.h"
#include "cypdf_integer.h"
#include "cypdf_log.h"
#include "cypdf_memory.h"
#include "cypdf_name.h"
#include "cypdf_number.h"
#include "cypdf_operators.h"
#include "cypdf_print.h"
#include "cypdf_resource.h"
#include "cypdf_types.h"



static void CYPDF_GraphicAppend(CYPDF_Graphic* const graphic, CYPDF_Operator* const operator);


CYPDF_Graphic* CYPDF_NewGraphic(void) {
    CYPDF_TRACE;

    CYPDF_Graphic* graphic = (CYPDF_Graphic*)CYPDF_malloc(sizeof(CYPDF_Graphic));

    graphic->display_page = NULL;
    graphic->operator_list = CYPF_NewList(CYPDF_LIST_DEFAULT_BLOCK_SIZE);
    graphic->current_point = CYPDF_DEFAULT_POINT;
    graphic->current_subpath_point = CYPDF_DEFAULT_POINT;

    graphic->memmgr = CYPDF_NewMemMgr(CYPDF_FreeObj);

    return graphic;
}

void CYPDF_FreeGraphic(void* ptr) {
    CYPDF_TRACE;

    CYPDF_Graphic* graphic = (CYPDF_Graphic*)ptr;

    CYPDF_FreeList(graphic->operator_list);
    CYPDF_DestroyMemMgr(graphic->memmgr);

    free(graphic);
}

void CYPDF_PrintGraphic(CYPDF_Channel* const channel, const CYPDF_Graphic* const graphic) {
    CYPDF_TRACE;

    CYPDF_Operator* operator = NULL;
    size_t length = CYPDF_ListLength(graphic->operator_list);
    for (size_t i = 0; i < length; ++i) {
        operator = CYPDF_ListAtIndex(graphic->operator_list, i);
        CYPDF_PrintOperator(channel, operator);
        if (i == length - 1) {
            break;
        }
        CYPDF_ChannelPrintNL(channel);
    }
}


void CYPDF_GraphicSetPage(CYPDF_Graphic* const graphic, CYPDF_ObjPage* const page) {
    graphic->display_page = page;
}


static void CYPDF_GraphicAppend(CYPDF_Graphic* const graphic, CYPDF_Operator* const operator) {
    CYPDF_TRACE;

    CYPFD_ListAppend(graphic->operator_list, operator);
}

void CYPDF_GraphicBegin(CYPDF_Graphic* const graphic, const CYPDF_Point start_point) {
    CYPDF_TRACE;

    if (graphic) {
        CYPDF_Operator* operator = CYPDF_NewOperator(CYPDF_OPERATOR_PATH_BEGIN);

        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(graphic->memmgr, start_point.x));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(graphic->memmgr, start_point.y));

        CYPDF_GraphicAppend(graphic, operator);
        graphic->current_point = start_point;
        graphic->current_subpath_point = start_point;
    }
}

void CYPDF_GraphicLineseg(CYPDF_Graphic* const restrict graphic, const CYPDF_Point end_point) {
    CYPDF_TRACE;

    if (graphic) {
        CYPDF_Operator* operator = CYPDF_NewOperator(CYPDF_OPERATOR_PATH_LINESEG);

        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(graphic->memmgr, end_point.x));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(graphic->memmgr, end_point.y));

        CYPDF_GraphicAppend(graphic, operator);
        graphic->current_point = end_point;
    }
}

void CYPDF_GraphicCBezier(CYPDF_Graphic* const restrict graphic, const CYPDF_Point ctrl_point1, const CYPDF_Point ctrl_point2, const CYPDF_Point end_point) {
    CYPDF_TRACE;

    if (graphic) {
        CYPDF_Operator* operator = CYPDF_NewOperator(CYPDF_OPERATOR_PATH_CBEZIER);

        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(graphic->memmgr, ctrl_point1.x));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(graphic->memmgr, ctrl_point1.y));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(graphic->memmgr, ctrl_point2.x));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(graphic->memmgr, ctrl_point2.y));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(graphic->memmgr, end_point.x));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(graphic->memmgr, end_point.y));
        
        CYPDF_GraphicAppend(graphic, operator);
        graphic->current_point = end_point;
    }
}

void CYPDF_GraphicVBezier(CYPDF_Graphic* const restrict graphic, const CYPDF_Point ctrl_point2, const CYPDF_Point end_point) {
    CYPDF_TRACE;

    if (graphic) {
        CYPDF_Operator* operator = CYPDF_NewOperator(CYPDF_OPERATOR_PATH_VBEZIER);

        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(graphic->memmgr, ctrl_point2.x));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(graphic->memmgr, ctrl_point2.y));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(graphic->memmgr, end_point.x));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(graphic->memmgr, end_point.y));
        
        CYPDF_GraphicAppend(graphic, operator);
        graphic->current_point = end_point;
    }
}

void CYPDF_GraphicYBezier(CYPDF_Graphic* const restrict graphic, const CYPDF_Point ctrl_point1, const CYPDF_Point end_point) {
    CYPDF_TRACE;

    if (graphic) {
        CYPDF_Operator* operator = CYPDF_NewOperator(CYPDF_OPERATOR_PATH_YBEZIER);

        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(graphic->memmgr, ctrl_point1.x));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(graphic->memmgr, ctrl_point1.y));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(graphic->memmgr, end_point.x));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(graphic->memmgr, end_point.y));
        
        CYPDF_GraphicAppend(graphic, operator);
        graphic->current_point = end_point;
    }
}

void CYPDF_GraphicClose(CYPDF_Graphic* const restrict graphic) {
    CYPDF_TRACE;

    if (graphic) {
        CYPDF_GraphicAppend(graphic, CYPDF_NewOperator(CYPDF_OPERATOR_PATH_CLOSE));
        graphic->current_point = graphic->current_subpath_point;
    }
}

void CYPDF_GraphicRect(CYPDF_Graphic* const restrict graphic, const CYPDF_Point lowleft_corner, const float width, const float height) {
    CYPDF_TRACE;

    if (graphic) {
        CYPDF_Operator* operator = CYPDF_NewOperator(CYPDF_OPERATOR_PATH_RECT);

        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(graphic->memmgr, lowleft_corner.x));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(graphic->memmgr, lowleft_corner.y));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(graphic->memmgr, width));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(graphic->memmgr, height));

        CYPDF_GraphicAppend(graphic, operator);
        graphic->current_point = lowleft_corner;
    }
}

void CYPDF_GraphicClip(CYPDF_Graphic* const restrict graphic, const enum CYPDF_OPERATOR_TYPE clip_operator) {
    CYPDF_TRACE;

    if (graphic) {
        CYPDF_GraphicAppend(graphic, CYPDF_NewOperator(clip_operator));
    }
}

void CYPDF_GraphicPaint(CYPDF_Graphic* const restrict graphic, const enum CYPDF_OPERATOR_TYPE paint_operator) {
    CYPDF_TRACE;

    if (graphic) {
        CYPDF_GraphicAppend(graphic, CYPDF_NewOperator(paint_operator));
    }
}


void CYPDF_GraphicSave(CYPDF_Graphic* const restrict graphic) {
    CYPDF_TRACE;

    if (graphic) {
        CYPDF_GraphicAppend(graphic, CYPDF_NewOperator(CYPDF_OPERATOR_GFX_STATE_SAVE));
    }
}

void CYPDF_GraphicRestore(CYPDF_Graphic* const restrict graphic) {
    CYPDF_TRACE;

    if (graphic) {
        CYPDF_GraphicAppend(graphic, CYPDF_NewOperator(CYPDF_OPERATOR_GFX_STATE_RESTORE));
    }
}

void CYPDF_GraphicTransformMatrix(CYPDF_Graphic* const restrict graphic, const float a, const float b, const float c, const float d, const float e, const float f) {
    CYPDF_TRACE;

    if (graphic) {
        CYPDF_Operator* transform_matrix = CYPDF_NewOperator(CYPDF_OPERATOR_GFX_STATE_MATRIX);
        CYPDF_OperatorAppendOperand(transform_matrix, CYPDF_NewNumber(graphic->memmgr, a));
        CYPDF_OperatorAppendOperand(transform_matrix, CYPDF_NewNumber(graphic->memmgr, b));
        CYPDF_OperatorAppendOperand(transform_matrix, CYPDF_NewNumber(graphic->memmgr, c));
        CYPDF_OperatorAppendOperand(transform_matrix, CYPDF_NewNumber(graphic->memmgr, d));
        CYPDF_OperatorAppendOperand(transform_matrix, CYPDF_NewNumber(graphic->memmgr, e));
        CYPDF_OperatorAppendOperand(transform_matrix, CYPDF_NewNumber(graphic->memmgr, f));

        CYPDF_GraphicAppend(graphic, transform_matrix);
    }
}

void CYPDF_GraphicLineWidth(CYPDF_Graphic* const restrict graphic, const float line_width) {
    CYPDF_TRACE;

    if (graphic) {
        CYPDF_Operator* line_width_op = CYPDF_NewOperator(CYPDF_OPERATOR_GFX_STATE_LINE_WIDTH);
        CYPDF_OperatorAppendOperand(line_width_op, CYPDF_NewNumber(graphic->memmgr, line_width));

        CYPDF_GraphicAppend(graphic, line_width_op);
    }
}

void CYPDF_GraphicLineCap(CYPDF_Graphic* const restrict graphic, const int line_cap) {
    CYPDF_TRACE;

    if (graphic) {
        CYPDF_Operator* line_cap_op = CYPDF_NewOperator(CYPDF_OPERATOR_GFX_STATE_LINE_CAP);
        CYPDF_OperatorAppendOperand(line_cap_op, CYPDF_NewInteger(graphic->memmgr, line_cap));

        CYPDF_GraphicAppend(graphic, line_cap_op);
    }
}

void CYPDF_GraphicLineJoin(CYPDF_Graphic* const restrict graphic, const int line_join) {
    CYPDF_TRACE;

    if (graphic) {
        CYPDF_Operator* line_join_op = CYPDF_NewOperator(CYPDF_OPERATOR_GFX_STATE_LINE_JOIN);
        CYPDF_OperatorAppendOperand(line_join_op, CYPDF_NewInteger(graphic->memmgr, line_join));

        CYPDF_GraphicAppend(graphic, line_join_op);
    }
}

void CYPDF_GraphicMiterLimit(CYPDF_Graphic* const restrict graphic, const float miter_limit) {
    CYPDF_TRACE;

    if (graphic) {
        CYPDF_Operator* miter_limit_op = CYPDF_NewOperator(CYPDF_OPERATOR_GFX_STATE_MITER_LIMIT);
        CYPDF_OperatorAppendOperand(miter_limit_op, CYPDF_NewNumber(graphic->memmgr, miter_limit));

        CYPDF_GraphicAppend(graphic, miter_limit_op);
    }
}

void CYPDF_GraphicDashPattern(CYPDF_Graphic* const restrict graphic, const int* const dash_array, const size_t dash_array_size, const int dash_phase) {
    CYPDF_TRACE;

    if (graphic) {
        CYPDF_Operator* dash_pattern = CYPDF_NewOperator(CYPDF_OPERATOR_GFX_STATE_DASH_PATTERN);
        CYPDF_OperatorAppendOperand(dash_pattern, CYPDF_ArrayFromIntArray(graphic->memmgr, dash_array, dash_array_size));
        CYPDF_OperatorAppendOperand(dash_pattern, CYPDF_NewInteger(graphic->memmgr, dash_phase));

        CYPDF_GraphicAppend(graphic, dash_pattern);
    }
}

void CYPDF_GraphicIntent(CYPDF_Graphic* const restrict graphic, const char intent[restrict static 1]) {
    CYPDF_TRACE;

    if (graphic) {
        CYPDF_Operator* intent_op = CYPDF_NewOperator(CYPDF_OPERATOR_GFX_STATE_INTENT);
        CYPDF_OperatorAppendOperand(intent_op, CYPDF_NewName(graphic->memmgr, intent));

        CYPDF_GraphicAppend(graphic, intent_op);
    }
}

void CYPDF_GraphicFlatness(CYPDF_Graphic* const restrict graphic, const float flatness) {
    CYPDF_TRACE;

    if (graphic) {
        CYPDF_Operator* flatness_op = CYPDF_NewOperator(CYPDF_OPERATOR_GFX_STATE_FLATNESS);
        CYPDF_OperatorAppendOperand(flatness_op, CYPDF_NewNumber(graphic->memmgr, flatness));

        CYPDF_GraphicAppend(graphic, flatness_op);
    }
}

void CYPDF_GraphicGFXState(CYPDF_Graphic* const restrict graphic, CYPDF_ObjGFXState* const restrict gfx_state) {
    CYPDF_TRACE;

    if (graphic) {
        CYPDF_Operator* gfx_state_op = CYPDF_NewOperator(CYPDF_OPERATOR_GFX_STATE_EXTGSTATE);
        CYPDF_ObjName* gfx_state_name = CYPDF_ResourceGetName(CYPDF_DictValueAtIndex(graphic->display_page, CYPDF_PAGE_RESOURCES_I), CYPDF_RESOURCE_GFX_STATE_I, gfx_state);
        CYPDF_OperatorAppendOperand(gfx_state_op, gfx_state_name);

        CYPDF_GraphicAppend(graphic, gfx_state_op);
    }
}


void CYPDF_GraphicLineColorSpace(CYPDF_Graphic* const restrict graphic, const char color_space[restrict static 1]) {
    CYPDF_TRACE;

    if (graphic) {
        CYPDF_Operator* line_color_space = CYPDF_NewOperator(CYPDF_OPERATOR_COLOR_SPACE_STROKING);
        CYPDF_OperatorAppendOperand(line_color_space, CYPDF_NewName(graphic->memmgr, color_space));

        CYPDF_GraphicAppend(graphic, line_color_space);
    }
}

void CYPDF_GraphicFillColorSpace(CYPDF_Graphic* const restrict graphic, const char color_space[restrict static 1]) {
    CYPDF_TRACE;

    if (graphic) {
        CYPDF_Operator* fill_color_space = CYPDF_NewOperator(CYPDF_OPERATOR_COLOR_SPACE_NONSTROKING);
        CYPDF_OperatorAppendOperand(fill_color_space, CYPDF_NewName(graphic->memmgr, color_space));

        CYPDF_GraphicAppend(graphic, fill_color_space);
    }
}

void CYPDF_GraphicLineColor(CYPDF_Graphic* const restrict graphic, CYPDF_Object** const restrict operands, const size_t operand_count) {
    CYPDF_TRACE;

    if (graphic) {
        CYPDF_Operator* line_color;
        if (CYPDF_ObjGetClass(operands[operand_count - 1]) == CYPDF_OBJ_CLASS_NAME) {
            line_color = CYPDF_NewOperator(CYPDF_OPERATOR_COLOR_STROKING_EXT);
        } else {
            line_color = CYPDF_NewOperator(CYPDF_OPERATOR_COLOR_STROKING);
        }

        for (size_t i = 0; i < operand_count; ++i) {
            CYPDF_OperatorAppendOperand(line_color, operands[i]);
        }

        CYPDF_GraphicAppend(graphic, line_color);
    }
}

void CYPDF_GraphicFillColor(CYPDF_Graphic* const restrict graphic, CYPDF_Object** const restrict operands, const size_t operand_count) {
    CYPDF_TRACE;

    if (graphic) {
        CYPDF_Operator* fill_color;
        if (CYPDF_ObjGetClass(operands[operand_count - 1]) == CYPDF_OBJ_CLASS_NAME) {
            fill_color = CYPDF_NewOperator(CYPDF_OPERATOR_COLOR_NONSTROKING_EXT);
        } else {
            fill_color = CYPDF_NewOperator(CYPDF_OPERATOR_COLOR_NONSTROKING);
        }

        for (size_t i = 0; i < operand_count; ++i) {
            CYPDF_OperatorAppendOperand(fill_color, operands[i]);
        }

        CYPDF_GraphicAppend(graphic, fill_color);
    }
}

void CYPDF_GraphicLineGray(CYPDF_Graphic* const restrict graphic, const float gray) {
    CYPDF_TRACE;

    if (graphic) {
        CYPDF_Operator* line_gray = CYPDF_NewOperator(CYPDF_OPERATOR_COLOR_STROKING_GRAY);
        CYPDF_OperatorAppendOperand(line_gray, CYPDF_NewNumber(graphic->memmgr, gray));

        CYPDF_GraphicAppend(graphic, line_gray);
    }
}

void CYPDF_GraphicFillGray(CYPDF_Graphic* const restrict graphic, const float gray) {
    CYPDF_TRACE;

    if (graphic) {
        CYPDF_Operator* fill_gray = CYPDF_NewOperator(CYPDF_OPERATOR_COLOR_NONSTROKING_GRAY);
        CYPDF_OperatorAppendOperand(fill_gray, CYPDF_NewNumber(graphic->memmgr, gray));

        CYPDF_GraphicAppend(graphic, fill_gray);
    }
}

void CYPDF_GraphicLineRGB(CYPDF_Graphic* const restrict graphic, const CYPDF_RGB rgb) {
    CYPDF_TRACE;

    if (graphic) {
        CYPDF_Operator* line_rgb = CYPDF_NewOperator(CYPDF_OPERATOR_COLOR_STROKING_RGB);
        CYPDF_OperatorAppendOperand(line_rgb, CYPDF_NewNumber(graphic->memmgr, rgb.red));
        CYPDF_OperatorAppendOperand(line_rgb, CYPDF_NewNumber(graphic->memmgr, rgb.green));
        CYPDF_OperatorAppendOperand(line_rgb, CYPDF_NewNumber(graphic->memmgr, rgb.blue));

        CYPDF_GraphicAppend(graphic, line_rgb);
    }
}

void CYPDF_GraphicFillRGB(CYPDF_Graphic* const restrict graphic, const CYPDF_RGB rgb) {
    CYPDF_TRACE;

    if (graphic) {
        CYPDF_Operator* fill_rgb = CYPDF_NewOperator(CYPDF_OPERATOR_COLOR_NONSTROKING_RGB);
        CYPDF_OperatorAppendOperand(fill_rgb, CYPDF_NewNumber(graphic->memmgr, rgb.red));
        CYPDF_OperatorAppendOperand(fill_rgb, CYPDF_NewNumber(graphic->memmgr, rgb.green));
        CYPDF_OperatorAppendOperand(fill_rgb, CYPDF_NewNumber(graphic->memmgr, rgb.blue));

        CYPDF_GraphicAppend(graphic, fill_rgb);
    }
}

void CYPDF_GraphicLineCMYK(CYPDF_Graphic* const restrict graphic, const CYPDF_CMYK cmyk) {
    CYPDF_TRACE;

    if (graphic) {
        CYPDF_Operator* line_cmyk = CYPDF_NewOperator(CYPDF_OPERATOR_COLOR_STROKING_CMYK);
        CYPDF_OperatorAppendOperand(line_cmyk, CYPDF_NewNumber(graphic->memmgr, cmyk.cyan));
        CYPDF_OperatorAppendOperand(line_cmyk, CYPDF_NewNumber(graphic->memmgr, cmyk.magenta));
        CYPDF_OperatorAppendOperand(line_cmyk, CYPDF_NewNumber(graphic->memmgr, cmyk.yellow));
        CYPDF_OperatorAppendOperand(line_cmyk, CYPDF_NewNumber(graphic->memmgr, cmyk.black));

        CYPDF_GraphicAppend(graphic, line_cmyk);
    }
}

void CYPDF_GraphicFillCMYK(CYPDF_Graphic* const restrict graphic, const CYPDF_CMYK cmyk) {
    CYPDF_TRACE;
    
    if (graphic) {
        CYPDF_Operator* fill_cmyk = CYPDF_NewOperator(CYPDF_OPERATOR_COLOR_NONSTROKING_CMYK);
        CYPDF_OperatorAppendOperand(fill_cmyk, CYPDF_NewNumber(graphic->memmgr, cmyk.cyan));
        CYPDF_OperatorAppendOperand(fill_cmyk, CYPDF_NewNumber(graphic->memmgr, cmyk.magenta));
        CYPDF_OperatorAppendOperand(fill_cmyk, CYPDF_NewNumber(graphic->memmgr, cmyk.yellow));
        CYPDF_OperatorAppendOperand(fill_cmyk, CYPDF_NewNumber(graphic->memmgr, cmyk.black));

        CYPDF_GraphicAppend(graphic, fill_cmyk);
    }
}
