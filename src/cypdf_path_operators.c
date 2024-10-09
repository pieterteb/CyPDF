#include <stdlib.h>

#include "cypdf_path_operators.h"
#include "cypdf_array.h"
#include "cypdf_color.h"
#include "cypdf_consts.h"
#include "cypdf_graphics_state.h"
#include "cypdf_integer.h"
#include "cypdf_log.h"
#include "cypdf_memmgr.h"
#include "cypdf_name.h"
#include "cypdf_number.h"
#include "cypdf_operators.h"
#include "cypdf_print.h"
#include "cypdf_types.h"



static void CYPDF_PathAppend(CYPDF_Path* const restrict path, CYPDF_Operator* const restrict operator);


CYPDF_Path* CYPDF_NewPath(void) {
    CYPDF_TRACE;

    CYPDF_Path* path = (CYPDF_Path*)CYPDF_malloc(sizeof(CYPDF_Path));

    if (path) {
        path->operators = NULL;
        path->operator_count = 0;

        path->current_point = CYPDF_DEFAULT_POINT;
        path->current_subpath_point = CYPDF_DEFAULT_POINT;

        path->memmgr = CYPDF_NewMemMgr(CYPDF_FreeObj);
    }

    return path;
}

void CYPDF_FreePath(CYPDF_Path* path) {
    CYPDF_TRACE;

    if (path) {
        CYPDF_DestroyMemMgr(path->memmgr);
        for (size_t i = 0; i < path->operator_count; ++i) {
            CYPDF_FreeOperator(path->operators[i]);
        }
        free(path->operators);

        free(path);
    }
}

void CYPDF_PrintPath(CYPDF_Channel* const restrict channel, const CYPDF_Path* const restrict path) {
    CYPDF_TRACE;

    if (path && channel) {
        CYPDF_Operator* operator = NULL;
        for (size_t i = 0; i < path->operator_count; ++i) {
            operator = path->operators[i];
            CYPDF_PrintOperator(channel, operator);
            if (i == path->operator_count - 1) {
                break;
            }
            CYPDF_ChannelPrintNL(channel);
        }
    }
}


static void CYPDF_PathAppend(CYPDF_Path* const restrict path, CYPDF_Operator* const restrict operator) {
    CYPDF_TRACE;

    if (path && operator) {
        path->operators = CYPDF_realloc(path->operators, (path->operator_count + 1) * sizeof(CYPDF_Operator*));
        path->operators[path->operator_count] = operator;
        ++path->operator_count;
    }
}

void CYPDF_PathBegin(CYPDF_Path* const restrict path, const CYPDF_Point start_point) {
    CYPDF_TRACE;

    if (path) {
        CYPDF_Operator* operator = CYPDF_NewOperator(CYPDF_OPERATOR_PATH_BEGIN);

        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, start_point.x));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, start_point.y));

        CYPDF_PathAppend(path, operator);
        path->current_point = start_point;
        path->current_subpath_point = start_point;
    }
}

void CYPDF_PathLineseg(CYPDF_Path* const restrict path, const CYPDF_Point end_point) {
    CYPDF_TRACE;

    if (path) {
        CYPDF_Operator* operator = CYPDF_NewOperator(CYPDF_OPERATOR_PATH_LINESEG);

        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, end_point.x));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, end_point.y));

        CYPDF_PathAppend(path, operator);
        path->current_point = end_point;
    }
}

void CYPDF_PathCBezier(CYPDF_Path* const restrict path, const CYPDF_Point ctrl_point1, const CYPDF_Point ctrl_point2, const CYPDF_Point end_point) {
    CYPDF_TRACE;

    if (path) {
        CYPDF_Operator* operator = CYPDF_NewOperator(CYPDF_OPERATOR_PATH_CBEZIER);

        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, ctrl_point1.x));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, ctrl_point1.y));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, ctrl_point2.x));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, ctrl_point2.y));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, end_point.x));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, end_point.y));
        
        CYPDF_PathAppend(path, operator);
        path->current_point = end_point;
    }
}

void CYPDF_PathVBezier(CYPDF_Path* const restrict path, const CYPDF_Point ctrl_point2, const CYPDF_Point end_point) {
    CYPDF_TRACE;

    if (path) {
        CYPDF_Operator* operator = CYPDF_NewOperator(CYPDF_OPERATOR_PATH_VBEZIER);

        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, ctrl_point2.x));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, ctrl_point2.y));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, end_point.x));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, end_point.y));
        
        CYPDF_PathAppend(path, operator);
        path->current_point = end_point;
    }
}

void CYPDF_PathYBezier(CYPDF_Path* const restrict path, const CYPDF_Point ctrl_point1, const CYPDF_Point end_point) {
    CYPDF_TRACE;

    if (path) {
        CYPDF_Operator* operator = CYPDF_NewOperator(CYPDF_OPERATOR_PATH_YBEZIER);

        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, ctrl_point1.x));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, ctrl_point1.y));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, end_point.x));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, end_point.y));
        
        CYPDF_PathAppend(path, operator);
        path->current_point = end_point;
    }
}

void CYPDF_PathClose(CYPDF_Path* const restrict path) {
    CYPDF_TRACE;

    if (path) {
        CYPDF_PathAppend(path, CYPDF_NewOperator(CYPDF_OPERATOR_PATH_CLOSE));
        path->current_point = path->current_subpath_point;
    }
}

void CYPDF_PathRect(CYPDF_Path* const restrict path, const CYPDF_Point lowleft_corner, const float width, const float height) {
    CYPDF_TRACE;

    if (path) {
        CYPDF_Operator* operator = CYPDF_NewOperator(CYPDF_OPERATOR_PATH_RECT);

        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, lowleft_corner.x));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, lowleft_corner.y));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, width));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, height));

        CYPDF_PathAppend(path, operator);
        path->current_point = lowleft_corner;
    }
}

void CYPDF_PathClip(CYPDF_Path* const restrict path, const enum CYPDF_OPERATOR_TYPE clip_operator) {
    CYPDF_TRACE;

    if (path) {
        CYPDF_PathAppend(path, CYPDF_NewOperator(clip_operator));
    }
}

void CYPDF_PathPaint(CYPDF_Path* const restrict path, const enum CYPDF_OPERATOR_TYPE paint_operator) {
    CYPDF_TRACE;

    if (path) {
        CYPDF_PathAppend(path, CYPDF_NewOperator(paint_operator));
    }
}


void CYPDF_PathSave(CYPDF_Path* const restrict path) {
    CYPDF_TRACE;

    if (path) {
        CYPDF_PathAppend(path, CYPDF_NewOperator(CYPDF_OPERATOR_GFX_STATE_SAVE));
    }
}

void CYPDF_PathRestore(CYPDF_Path* const restrict path) {
    CYPDF_TRACE;

    if (path) {
        CYPDF_PathAppend(path, CYPDF_NewOperator(CYPDF_OPERATOR_GFX_STATE_RESTORE));
    }
}

void CYPDF_PathTransformMatrix(CYPDF_Path* const restrict path, const float a, const float b, const float c, const float d, const float e, const float f) {
    CYPDF_TRACE;

    if (path) {
        CYPDF_Operator* transform_matrix = CYPDF_NewOperator(CYPDF_OPERATOR_GFX_STATE_MATRIX);
        CYPDF_OperatorAppendOperand(transform_matrix, CYPDF_NewNumber(path->memmgr, a));
        CYPDF_OperatorAppendOperand(transform_matrix, CYPDF_NewNumber(path->memmgr, b));
        CYPDF_OperatorAppendOperand(transform_matrix, CYPDF_NewNumber(path->memmgr, c));
        CYPDF_OperatorAppendOperand(transform_matrix, CYPDF_NewNumber(path->memmgr, d));
        CYPDF_OperatorAppendOperand(transform_matrix, CYPDF_NewNumber(path->memmgr, e));
        CYPDF_OperatorAppendOperand(transform_matrix, CYPDF_NewNumber(path->memmgr, f));

        CYPDF_PathAppend(path, transform_matrix);
    }
}

void CYPDF_PathLineWidth(CYPDF_Path* const restrict path, const float line_width) {
    CYPDF_TRACE;

    if (path) {
        CYPDF_Operator* line_width_op = CYPDF_NewOperator(CYPDF_OPERATOR_GFX_STATE_LINE_WIDTH);
        CYPDF_OperatorAppendOperand(line_width_op, CYPDF_NewNumber(path->memmgr, line_width));

        CYPDF_PathAppend(path, line_width_op);
    }
}

void CYPDF_PathLineCap(CYPDF_Path* const restrict path, const int line_cap) {
    CYPDF_TRACE;

    if (path) {
        CYPDF_Operator* line_cap_op = CYPDF_NewOperator(CYPDF_OPERATOR_GFX_STATE_LINE_CAP);
        CYPDF_OperatorAppendOperand(line_cap_op, CYPDF_NewInteger(path->memmgr, line_cap));

        CYPDF_PathAppend(path, line_cap_op);
    }
}

void CYPDF_PathLineJoin(CYPDF_Path* const restrict path, const int line_join) {
    CYPDF_TRACE;

    if (path) {
        CYPDF_Operator* line_join_op = CYPDF_NewOperator(CYPDF_OPERATOR_GFX_STATE_LINE_JOIN);
        CYPDF_OperatorAppendOperand(line_join_op, CYPDF_NewInteger(path->memmgr, line_join));

        CYPDF_PathAppend(path, line_join_op);
    }
}

void CYPDF_PathMiterLimit(CYPDF_Path* const restrict path, const float miter_limit) {
    CYPDF_TRACE;

    if (path) {
        CYPDF_Operator* miter_limit_op = CYPDF_NewOperator(CYPDF_OPERATOR_GFX_STATE_MITER_LIMIT);
        CYPDF_OperatorAppendOperand(miter_limit_op, CYPDF_NewNumber(path->memmgr, miter_limit));

        CYPDF_PathAppend(path, miter_limit_op);
    }
}

void CYPDF_PathDashPattern(CYPDF_Path* const restrict path, const int* const dash_array, const size_t dash_array_size, const int dash_phase) {
    CYPDF_TRACE;

    if (path) {
        CYPDF_Operator* dash_pattern = CYPDF_NewOperator(CYPDF_OPERATOR_GFX_STATE_DASH_PATTERN);
        CYPDF_OperatorAppendOperand(dash_pattern, CYPDF_ArrayFromIntArray(path->memmgr, dash_array, dash_array_size));
        CYPDF_OperatorAppendOperand(dash_pattern, CYPDF_NewInteger(path->memmgr, dash_phase));

        CYPDF_PathAppend(path, dash_pattern);
    }
}

void CYPDF_PathIntent(CYPDF_Path* const restrict path, const char intent[restrict static 1]) {
    CYPDF_TRACE;

    if (path) {
        CYPDF_Operator* intent_op = CYPDF_NewOperator(CYPDF_OPERATOR_GFX_STATE_INTENT);
        CYPDF_OperatorAppendOperand(intent_op, CYPDF_NewName(path->memmgr, intent));

        CYPDF_PathAppend(path, intent_op);
    }
}

void CYPDF_PathFlatness(CYPDF_Path* const restrict path, const float flatness) {
    CYPDF_TRACE;

    if (path) {
        CYPDF_Operator* flatness_op = CYPDF_NewOperator(CYPDF_OPERATOR_GFX_STATE_FLATNESS);
        CYPDF_OperatorAppendOperand(flatness_op, CYPDF_NewNumber(path->memmgr, flatness));

        CYPDF_PathAppend(path, flatness_op);
    }
}

void CYPDF_PathGFXState(CYPDF_Path* const restrict path, CYPDF_ObjGFXState* const restrict gfx_state) {
    CYPDF_TRACE;

    if (path) {
        CYPDF_Operator* gfx_state_op = CYPDF_NewOperator(CYPDF_OPERATOR_GFX_STATE_EXTGSTATE);
        CYPDF_OperatorAppendOperand(gfx_state_op, gfx_state);

        CYPDF_PathAppend(path, gfx_state_op);
    }
}


void CYPDF_PathLineColorSpace(CYPDF_Path* const restrict path, const char color_space[restrict static 1]) {
    CYPDF_TRACE;

    if (path) {
        CYPDF_Operator* line_color_space = CYPDF_NewOperator(CYPDF_OPERATOR_COLOR_SPACE_STROKING);
        CYPDF_OperatorAppendOperand(line_color_space, CYPDF_NewName(path->memmgr, color_space));

        CYPDF_PathAppend(path, line_color_space);
    }
}

void CYPDF_PathFillColorSpace(CYPDF_Path* const restrict path, const char color_space[restrict static 1]) {
    CYPDF_TRACE;

    if (path) {
        CYPDF_Operator* fill_color_space = CYPDF_NewOperator(CYPDF_OPERATOR_COLOR_SPACE_NONSTROKING);
        CYPDF_OperatorAppendOperand(fill_color_space, CYPDF_NewName(path->memmgr, color_space));

        CYPDF_PathAppend(path, fill_color_space);
    }
}

void CYPDF_PathLineColor(CYPDF_Path* const restrict path, CYPDF_Object** const restrict operands, const size_t operand_count) {
    CYPDF_TRACE;

    if (path) {
        CYPDF_Operator* line_color;
        if (CYPDF_ObjGetClass(operands[operand_count - 1]) == CYPDF_OBJ_CLASS_NAME) {
            line_color = CYPDF_NewOperator(CYPDF_OPERATOR_COLOR_STROKING_EXT);
        } else {
            line_color = CYPDF_NewOperator(CYPDF_OPERATOR_COLOR_STROKING);
        }

        for (size_t i = 0; i < operand_count; ++i) {
            CYPDF_OperatorAppendOperand(line_color, operands[i]);
        }

        CYPDF_PathAppend(path, line_color);
    }
}

void CYPDF_PathFillColor(CYPDF_Path* const restrict path, CYPDF_Object** const restrict operands, const size_t operand_count) {
    CYPDF_TRACE;

    if (path) {
        CYPDF_Operator* fill_color;
        if (CYPDF_ObjGetClass(operands[operand_count - 1]) == CYPDF_OBJ_CLASS_NAME) {
            fill_color = CYPDF_NewOperator(CYPDF_OPERATOR_COLOR_NONSTROKING_EXT);
        } else {
            fill_color = CYPDF_NewOperator(CYPDF_OPERATOR_COLOR_NONSTROKING);
        }

        for (size_t i = 0; i < operand_count; ++i) {
            CYPDF_OperatorAppendOperand(fill_color, operands[i]);
        }

        CYPDF_PathAppend(path, fill_color);
    }
}

void CYPDF_PathLineGray(CYPDF_Path* const restrict path, const float gray) {
    CYPDF_TRACE;

    if (path) {
        CYPDF_Operator* line_gray = CYPDF_NewOperator(CYPDF_OPERATOR_COLOR_STROKING_GRAY);
        CYPDF_OperatorAppendOperand(line_gray, CYPDF_NewNumber(path->memmgr, gray));

        CYPDF_PathAppend(path, line_gray);
    }
}

void CYPDF_PathFillGray(CYPDF_Path* const restrict path, const float gray) {
    CYPDF_TRACE;

    if (path) {
        CYPDF_Operator* fill_gray = CYPDF_NewOperator(CYPDF_OPERATOR_COLOR_NONSTROKING_GRAY);
        CYPDF_OperatorAppendOperand(fill_gray, CYPDF_NewNumber(path->memmgr, gray));

        CYPDF_PathAppend(path, fill_gray);
    }
}

void CYPDF_PathLineRGB(CYPDF_Path* const restrict path, const CYPDF_RGB rgb) {
    CYPDF_TRACE;

    if (path) {
        CYPDF_Operator* line_rgb = CYPDF_NewOperator(CYPDF_OPERATOR_COLOR_STROKING_RGB);
        CYPDF_OperatorAppendOperand(line_rgb, CYPDF_NewNumber(path->memmgr, rgb.red));
        CYPDF_OperatorAppendOperand(line_rgb, CYPDF_NewNumber(path->memmgr, rgb.green));
        CYPDF_OperatorAppendOperand(line_rgb, CYPDF_NewNumber(path->memmgr, rgb.blue));

        CYPDF_PathAppend(path, line_rgb);
    }
}

void CYPDF_PathFillRGB(CYPDF_Path* const restrict path, const CYPDF_RGB rgb) {
    CYPDF_TRACE;

    if (path) {
        CYPDF_Operator* fill_rgb = CYPDF_NewOperator(CYPDF_OPERATOR_COLOR_NONSTROKING_RGB);
        CYPDF_OperatorAppendOperand(fill_rgb, CYPDF_NewNumber(path->memmgr, rgb.red));
        CYPDF_OperatorAppendOperand(fill_rgb, CYPDF_NewNumber(path->memmgr, rgb.green));
        CYPDF_OperatorAppendOperand(fill_rgb, CYPDF_NewNumber(path->memmgr, rgb.blue));

        CYPDF_PathAppend(path, fill_rgb);
    }
}

void CYPDF_PathLineCMYK(CYPDF_Path* const restrict path, const CYPDF_CMYK cmyk) {
    CYPDF_TRACE;

    if (path) {
        CYPDF_Operator* line_cmyk = CYPDF_NewOperator(CYPDF_OPERATOR_COLOR_STROKING_CMYK);
        CYPDF_OperatorAppendOperand(line_cmyk, CYPDF_NewNumber(path->memmgr, cmyk.cyan));
        CYPDF_OperatorAppendOperand(line_cmyk, CYPDF_NewNumber(path->memmgr, cmyk.magenta));
        CYPDF_OperatorAppendOperand(line_cmyk, CYPDF_NewNumber(path->memmgr, cmyk.yellow));
        CYPDF_OperatorAppendOperand(line_cmyk, CYPDF_NewNumber(path->memmgr, cmyk.black));

        CYPDF_PathAppend(path, line_cmyk);
    }
}

void CYPDF_PathFillCMYK(CYPDF_Path* const restrict path, const CYPDF_CMYK cmyk) {
    CYPDF_TRACE;
    
    if (path) {
        CYPDF_Operator* fill_cmyk = CYPDF_NewOperator(CYPDF_OPERATOR_COLOR_NONSTROKING_CMYK);
        CYPDF_OperatorAppendOperand(fill_cmyk, CYPDF_NewNumber(path->memmgr, cmyk.cyan));
        CYPDF_OperatorAppendOperand(fill_cmyk, CYPDF_NewNumber(path->memmgr, cmyk.magenta));
        CYPDF_OperatorAppendOperand(fill_cmyk, CYPDF_NewNumber(path->memmgr, cmyk.yellow));
        CYPDF_OperatorAppendOperand(fill_cmyk, CYPDF_NewNumber(path->memmgr, cmyk.black));

        CYPDF_PathAppend(path, fill_cmyk);
    }
}
