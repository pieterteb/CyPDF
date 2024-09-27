#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cypdf_path_operators.h"
#include "cypdf_consts.h"
#include "cypdf_print.h"
#include "cypdf_stream.h"
#include "cypdf_utils.h"



static void CYPDF_PathAppend(CYPDF_Path* const path, CYPDF_Operator* const operator, const CYPDF_Point new_current_point);


CYPDF_Path* CYPDF_NewPath(void) {
    CYPDF_Path* path = (CYPDF_Path*)CYPDF_smalloc(sizeof(CYPDF_Path));

    if (path) {
        path->construction_operators = NULL;
        path->construction_operator_count = 0;

        path->current_point = CYPDF_DEFAULT_POINT;
        path->current_subpath_point = CYPDF_DEFAULT_POINT;

        path->paint_operator = NULL;
        path->clip_operator = NULL;
    }

    return path;
}

void CYPDF_FreePath(CYPDF_Path* path) {
    if (path) {
        for (size_t i = 0; i < path->construction_operator_count; ++i) {
            CYPDF_FreeOperator(path->construction_operators[i]);
        }
        free(path->construction_operators);

        free(path);
    }
}

static void CYPDF_PathAppend(CYPDF_Path* const path, CYPDF_Operator* const operator, const CYPDF_Point new_current_point) {
    if (path && operator) {
        path->construction_operators = CYPDF_srealloc(path->construction_operators, (path->construction_operator_count + 1) * sizeof(CYPDF_Operator*));
        path->construction_operators[path->construction_operator_count] = operator;
        ++path->construction_operator_count;

        path->current_point = new_current_point;
    }
}

void CYPDF_PathAppendBegin(CYPDF_Path* const path, const CYPDF_Point start_point) {
    if (path) {
        float* operand1 = CYPDF_smalloc(sizeof(float));
        *operand1 = start_point.x;
        float* operand2 = CYPDF_smalloc(sizeof(float));
        *operand2 = start_point.y;

        CYPDF_Operator* operator = CYPDF_NewOperator(CYPDF_OPERATOR_PATH_BEGIN);
        CYPDF_OperatorAppendOperand(operator, operand1);
        CYPDF_OperatorAppendOperand(operator, operand2);

        CYPDF_PathAppend(path, operator, start_point);
        path->current_subpath_point = start_point;
    }
}

void CYPDF_PathAppendLineseg(CYPDF_Path* const path, const CYPDF_Point end_point) {
    if (path) {
        float* operand1 = CYPDF_smalloc(sizeof(float));
        *operand1 = end_point.x;
        float* operand2 = CYPDF_smalloc(sizeof(float));
        *operand2 = end_point.y;

        CYPDF_Operator* operator = CYPDF_NewOperator(CYPDF_OPERATOR_PATH_LINESEG);
        CYPDF_OperatorAppendOperand(operator, operand1);
        CYPDF_OperatorAppendOperand(operator, operand2);

        CYPDF_PathAppend(path, operator, end_point);
    }
}

void CYPDF_PathAppendCBezier(CYPDF_Path* const path, const CYPDF_Point ctrl_point1, const CYPDF_Point ctrl_point2, const CYPDF_Point end_point) {
    if (path) {
        float* operand1 = CYPDF_smalloc(sizeof(float));
        *operand1 = ctrl_point1.x;
        float* operand2 = CYPDF_smalloc(sizeof(float));
        *operand2 = ctrl_point1.y;
        float* operand3 = CYPDF_smalloc(sizeof(float));
        *operand3 = ctrl_point2.x;
        float* operand4 = CYPDF_smalloc(sizeof(float));
        *operand4 = ctrl_point2.y;
        float* operand5 = CYPDF_smalloc(sizeof(float));
        *operand5 = end_point.x;
        float* operand6 = CYPDF_smalloc(sizeof(float));
        *operand6 = end_point.y;

        CYPDF_Operator* operator = CYPDF_NewOperator(CYPDF_OPERATOR_PATH_CBEZIER);
        CYPDF_OperatorAppendOperand(operator, operand1);
        CYPDF_OperatorAppendOperand(operator, operand2);
        CYPDF_OperatorAppendOperand(operator, operand3);
        CYPDF_OperatorAppendOperand(operator, operand4);
        CYPDF_OperatorAppendOperand(operator, operand5);
        CYPDF_OperatorAppendOperand(operator, operand6);
        
        CYPDF_PathAppend(path, operator, end_point);
    }
}

void CYPDF_PathAppendVBezier(CYPDF_Path* const path, const CYPDF_Point ctrl_point2, const CYPDF_Point end_point) {
    if (path) {
        float* operand1 = CYPDF_smalloc(sizeof(float));
        *operand1 = ctrl_point2.x;
        float* operand2 = CYPDF_smalloc(sizeof(float));
        *operand2 = ctrl_point2.y;
        float* operand3 = CYPDF_smalloc(sizeof(float));
        *operand3 = end_point.x;
        float* operand4 = CYPDF_smalloc(sizeof(float));
        *operand4 = end_point.y;

        CYPDF_Operator* operator = CYPDF_NewOperator(CYPDF_OPERATOR_PATH_VBEZIER);
        CYPDF_OperatorAppendOperand(operator, operand1);
        CYPDF_OperatorAppendOperand(operator, operand2);
        CYPDF_OperatorAppendOperand(operator, operand3);
        CYPDF_OperatorAppendOperand(operator, operand4);
        
        CYPDF_PathAppend(path, operator, end_point);
    }
}

void CYPDF_PathAppendYBezier(CYPDF_Path* const path, const CYPDF_Point ctrl_point1, const CYPDF_Point end_point) {
    if (path) {
        float* operand1 = CYPDF_smalloc(sizeof(float));
        *operand1 = ctrl_point1.x;
        float* operand2 = CYPDF_smalloc(sizeof(float));
        *operand2 = ctrl_point1.y;
        float* operand3 = CYPDF_smalloc(sizeof(float));
        *operand3 = end_point.x;
        float* operand4 = CYPDF_smalloc(sizeof(float));
        *operand4 = end_point.y;

        CYPDF_Operator* operator = CYPDF_NewOperator(CYPDF_OPERATOR_PATH_YBEZIER);
        CYPDF_OperatorAppendOperand(operator, operand1);
        CYPDF_OperatorAppendOperand(operator, operand2);
        CYPDF_OperatorAppendOperand(operator, operand3);
        CYPDF_OperatorAppendOperand(operator, operand4);
        
        CYPDF_PathAppend(path, operator, end_point);
    }
}

void CYPDF_PathAppendClose(CYPDF_Path* const path) {
    if (path) {
        CYPDF_Operator* operator = CYPDF_NewOperator(CYPDF_OPERATOR_PATH_CLOSE);

        CYPDF_PathAppend(path, operator, path->current_subpath_point);
    }
}

void CYPDF_PathAppendRect(CYPDF_Path* const path, const CYPDF_Point lowleft_corner, const float width, const float height) {
    if (path) {
        float* operand1 = CYPDF_smalloc(sizeof(float));
        *operand1 = lowleft_corner.x;
        float* operand2 = CYPDF_smalloc(sizeof(float));
        *operand2 = lowleft_corner.y;
        float* operand3 = CYPDF_smalloc(sizeof(float));
        *operand3 = width;
        float* operand4 = CYPDF_smalloc(sizeof(float));
        *operand4 = height;

        CYPDF_Operator* operator = CYPDF_NewOperator(CYPDF_OPERATOR_PATH_RECT);
        CYPDF_OperatorAppendOperand(operator, operand1);
        CYPDF_OperatorAppendOperand(operator, operand2);
        CYPDF_OperatorAppendOperand(operator, operand3);
        CYPDF_OperatorAppendOperand(operator, operand4);

        CYPDF_PathAppend(path, operator, lowleft_corner);
    }
}

void CYPDF_PathSetPaint(CYPDF_Path* const path, const enum CYPDF_OPERATOR_TYPE paint_operator) {
    if (path) {
        path->paint_operator = CYPDF_NewOperator(paint_operator);
    }
}

void CYPDF_PathSetClip(CYPDF_Path* const path, const enum CYPDF_OPERATOR_TYPE clip_operator) {
    if (path) {
        path->clip_operator = CYPDF_NewOperator(clip_operator);
    }
}

void CYPDF_PrintPathToStream(CYPDF_ObjStream* const stream, const CYPDF_Path* const path) {
    if (path && stream) {
        CYPDF_Operator* operator = NULL;

        for (size_t i = 0; i < path->construction_operator_count; ++i) {
            operator = path->construction_operators[i];
            switch (operator->type)
            {
            case CYPDF_OPERATOR_PATH_BEGIN:
            case CYPDF_OPERATOR_PATH_LINESEG:
                CYPDF_PrintToStream(stream, "%f %f ", *(float*)operator->operands[0], *(float*)operator->operands[1]);
                break;
            case CYPDF_OPERATOR_PATH_CBEZIER:
                CYPDF_PrintToStream(stream, "%f %f %f %f %f %f ", *(float*)operator->operands[0], *(float*)operator->operands[1], *(float*)operator->operands[2], *(float*)operator->operands[3], *(float*)operator->operands[4], *(float*)operator->operands[5]);
                break;
            case CYPDF_OPERATOR_PATH_VBEZIER:
            case CYPDF_OPERATOR_PATH_YBEZIER:
            case CYPDF_OPERATOR_PATH_RECT:
                CYPDF_PrintToStream(stream, "%f %f %f %f ", *(float*)operator->operands[0], *(float*)operator->operands[1], *(float*)operator->operands[2], *(float*)operator->operands[3]);
                break;
            default:
                break;
            }
            
            CYPDF_PrintToStream(stream, "%s\n", CYPDF_OperatorGetName(operator));
        }

        /* Check for clipping operator */
        if (path->clip_operator) {
            CYPDF_PrintToStream(stream, "%s\n", CYPDF_OperatorGetName(path->clip_operator));
        }

        CYPDF_PrintToStream(stream, "%s", CYPDF_OperatorGetName(path->paint_operator));
    }
}
