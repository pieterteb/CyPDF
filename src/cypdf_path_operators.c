#include <stdlib.h>

#include "cypdf_path_operators.h"
#include "cypdf_consts.h"
#include "cypdf_memmgr.h"
#include "cypdf_number.h"
#include "cypdf_print.h"



static void CYPDF_PathAppend(CYPDF_Path* const restrict path, CYPDF_Operator* const restrict operator, const CYPDF_Point new_current_point);


CYPDF_Path* CYPDF_NewPath(void) {
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


static void CYPDF_PathAppend(CYPDF_Path* const restrict path, CYPDF_Operator* const restrict operator, const CYPDF_Point new_current_point) {
    if (path && operator) {
        path->operators = CYPDF_realloc(path->operators, (path->operator_count + 1) * sizeof(CYPDF_Operator*));
        path->operators[path->operator_count] = operator;
        ++path->operator_count;

        path->current_point = new_current_point;
    }
}

void CYPDF_PathAppendBegin(CYPDF_Path* const restrict path, const CYPDF_Point start_point) {
    if (path) {
        CYPDF_Operator* operator = CYPDF_NewOperator(CYPDF_OPERATOR_PATH_BEGIN);

        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, start_point.x));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, start_point.y));

        CYPDF_PathAppend(path, operator, start_point);
        path->current_subpath_point = start_point;
    }
}

void CYPDF_PathAppendLineseg(CYPDF_Path* const restrict path, const CYPDF_Point end_point) {
    if (path) {
        CYPDF_Operator* operator = CYPDF_NewOperator(CYPDF_OPERATOR_PATH_LINESEG);

        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, end_point.x));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, end_point.y));

        CYPDF_PathAppend(path, operator, end_point);
    }
}

void CYPDF_PathAppendCBezier(CYPDF_Path* const restrict path, const CYPDF_Point ctrl_point1, const CYPDF_Point ctrl_point2, const CYPDF_Point end_point) {
    if (path) {
        CYPDF_Operator* operator = CYPDF_NewOperator(CYPDF_OPERATOR_PATH_CBEZIER);

        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, ctrl_point1.x));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, ctrl_point1.y));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, ctrl_point2.x));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, ctrl_point2.y));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, end_point.x));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, end_point.y));
        
        CYPDF_PathAppend(path, operator, end_point);
    }
}

void CYPDF_PathAppendVBezier(CYPDF_Path* const restrict path, const CYPDF_Point ctrl_point2, const CYPDF_Point end_point) {
    if (path) {
        CYPDF_Operator* operator = CYPDF_NewOperator(CYPDF_OPERATOR_PATH_VBEZIER);

        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, ctrl_point2.x));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, ctrl_point2.y));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, end_point.x));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, end_point.y));
        
        CYPDF_PathAppend(path, operator, end_point);
    }
}

void CYPDF_PathAppendYBezier(CYPDF_Path* const restrict path, const CYPDF_Point ctrl_point1, const CYPDF_Point end_point) {
    if (path) {
        CYPDF_Operator* operator = CYPDF_NewOperator(CYPDF_OPERATOR_PATH_YBEZIER);

        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, ctrl_point1.x));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, ctrl_point1.y));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, end_point.x));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, end_point.y));
        
        CYPDF_PathAppend(path, operator, end_point);
    }
}

void CYPDF_PathAppendClose(CYPDF_Path* const restrict path) {
    if (path) {
        CYPDF_PathAppend(path, CYPDF_NewOperator(CYPDF_OPERATOR_PATH_CLOSE), path->current_subpath_point);
    }
}

void CYPDF_PathAppendRect(CYPDF_Path* const restrict path, const CYPDF_Point lowleft_corner, const float width, const float height) {
    if (path) {
        CYPDF_Operator* operator = CYPDF_NewOperator(CYPDF_OPERATOR_PATH_RECT);

        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, lowleft_corner.x));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, lowleft_corner.y));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, width));
        CYPDF_OperatorAppendOperand(operator, CYPDF_NewNumber(path->memmgr, height));

        CYPDF_PathAppend(path, operator, lowleft_corner);
    }
}

void CYPDF_PathSetClip(CYPDF_Path* const restrict path, const enum CYPDF_OPERATOR_TYPE clip_operator) {
    if (path) {
        CYPDF_PathAppend(path, CYPDF_NewOperator(clip_operator), path->current_point);
    }
}

void CYPDF_PathSetPaint(CYPDF_Path* const restrict path, const enum CYPDF_OPERATOR_TYPE paint_operator) {
    if (path) {
        CYPDF_PathAppend(path, CYPDF_NewOperator(paint_operator), path->current_point);
    }
}
