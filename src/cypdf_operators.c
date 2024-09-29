#include <stdbool.h>
#include <stdlib.h>

#include "cypdf_operators.h"
#include "cypdf_memmgr.h"
#include "cypdf_object.h"
#include "cypdf_print.h"
#include "cypdf_types.h"



/* Operator lookup table */
static char* operator_names[CYPDF_OPERATOR_COUNT] = {
    [CYPDF_OPERATOR_PATH_BEGIN] = CYPDF_OPERATOR_PATH_BEGIN_K,
    [CYPDF_OPERATOR_PATH_LINESEG] = CYPDF_OPERATOR_PATH_LINESEG_K,
    [CYPDF_OPERATOR_PATH_CBEZIER] = CYPDF_OPERATOR_PATH_CBEZIER_K,
    [CYPDF_OPERATOR_PATH_VBEZIER] = CYPDF_OPERATOR_PATH_VBEZIER_K,
    [CYPDF_OPERATOR_PATH_YBEZIER] = CYPDF_OPERATOR_PATH_YBEZIER_K,
    [CYPDF_OPERATOR_PATH_CLOSE] = CYPDF_OPERATOR_PATH_CLOSE_K,
    [CYPDF_OPERATOR_PATH_RECT] = CYPDF_OPERATOR_PATH_RECT_K,
    [CYPDF_OPERATOR_PATH_STROKE] = CYPDF_OPERATOR_PATH_STROKE_K,
    [CYPDF_OPERATOR_PATH_CLOSE_STROKE] = CYPDF_OPERATOR_PATH_CLOSE_STROKE_K,
    [CYPDF_OPERATOR_PATH_NWNRFILL] = CYPDF_OPERATOR_PATH_NWNRFILL_K,
    [CYPDF_OPERATOR_PATH_EORFILL] = CYPDF_OPERATOR_PATH_EORFILL_K,
    [CYPDF_OPERATOR_PATH_NWNRFILL_STROKE] = CYPDF_OPERATOR_PATH_NWNRFILL_STROKE_K,
    [CYPDF_OPERATOR_PATH_EORFILL_STROKE] = CYPDF_OPERATOR_PATH_EORFILL_STROKE_K,
    [CYPDF_OPERATOR_PATH_CLOSE_NWNRFILL_STROKE] = CYPDF_OPERATOR_PATH_CLOSE_NWNRFILL_STROKE_K,
    [CYPDF_OPERATOR_PATH_CLOSE_EORFILL_STROKE] = CYPDF_OPERATOR_PATH_CLOSE_EORFILL_STROKE_K,
    [CYPDF_OPERATOR_PATH_END] = CYPDF_OPERATOR_PATH_END_K,
    [CYPDF_OPERATOR_PATH_NWNRCLIP] = CYPDF_OPERATOR_PATH_NWNRCLIP_K,
    [CYPDF_OPERATOR_PATH_EORCLIP] = CYPDF_OPERATOR_PATH_EORCLIP_K,
    [CYPDF_OPERATOR_GFX_STATE_SAVE] = CYPDF_OPERATOR_GFX_STATE_SAVE_K,
    [CYPDF_OPERATOR_GFX_STATE_RESTORE] = CYPDF_OPERATOR_GFX_STATE_RESTORE_K,
    [CYPDF_OPERATOR_GFX_STATE_MATRIX] = CYPDF_OPERATOR_GFX_STATE_MATRIX_K,
    [CYPDF_OPERATOR_GFX_STATE_LINE_WIDTH] = CYPDF_OPERATOR_GFX_STATE_LINE_WIDTH_K,
    [CYPDF_OPERATOR_GFX_STATE_LINE_CAP] = CYPDF_OPERATOR_GFX_STATE_LINE_CAP_K,
    [CYPDF_OPERATOR_GFX_STATE_LINE_JOIN] = CYPDF_OPERATOR_GFX_STATE_LINE_JOIN_K,
    [CYPDF_OPERATOR_GFX_STATE_MITER_LIMIT] = CYPDF_OPERATOR_GFX_STATE_MITER_LIMIT_K,
    [CYPDF_OPERATOR_GFX_STATE_DASH_PATTERN] = CYPDF_OPERATOR_GFX_STATE_DASH_PATTERN_K,
    [CYPDF_OPERATOR_GFX_STATE_INTENT] = CYPDF_OPERATOR_GFX_STATE_INTENT_K,
    [CYPDF_OPERATOR_GFX_STATE_FLATNESS] = CYPDF_OPERATOR_GFX_STATE_FLATNESS_K,
    [CYPDF_OPERATOR_GFX_STATE_EXTGSTATE] = CYPDF_OPERATOR_GFX_STATE_EXTGSTATE_K,
    [CYPDF_OPERATOR_COLOR_SPACE_STROKING] = CYPDF_OPERATOR_COLOR_SPACE_STROKING_K,
    [CYPDF_OPERATOR_COLOR_SPACE_NONSTROKING] = CYPDF_OPERATOR_COLOR_SPACE_NONSTROKING_K,
    [CYPDF_OPERATOR_COLOR_STROKING] = CYPDF_OPERATOR_COLOR_STROKING_K,
    [CYPDF_OPERATOR_COLOR_STROKING_EXT] = CYPDF_OPERATOR_COLOR_STROKING_EXT_K,
    [CYPDF_OPERATOR_COLOR_NONSTROKING] = CYPDF_OPERATOR_COLOR_NONSTROKING_K,
    [CYPDF_OPERATOR_COLOR_NONSTROKING_EXT] = CYPDF_OPERATOR_COLOR_NONSTROKING_EXT_K,
    [CYPDF_OPERATOR_COLOR_STROKING_GRAY] = CYPDF_OPERATOR_COLOR_STROKING_GRAY_K,
    [CYPDF_OPERATOR_COLOR_NONSTROKING_GRAY] = CYPDF_OPERATOR_COLOR_NONSTROKING_GRAY_K,
    [CYPDF_OPERATOR_COLOR_STROKING_RGB] = CYPDF_OPERATOR_COLOR_STROKING_RGB_K,
    [CYPDF_OPERATOR_COLOR_NONSTROKING_RGB] = CYPDF_OPERATOR_COLOR_NONSTROKING_RGB_K,
    [CYPDF_OPERATOR_COLOR_STROKING_CMYK] = CYPDF_OPERATOR_COLOR_STROKING_CMYK_K,
    [CYPDF_OPERATOR_COLOR_NONSTROKING_CMYK] = CYPDF_OPERATOR_COLOR_NONSTROKING_CMYK_K
};


CYPDF_Operator* CYPDF_NewOperator(const enum CYPDF_OPERATOR_TYPE type) {
    CYPDF_Operator* operator = (CYPDF_Operator*)CYPDF_malloc(sizeof(CYPDF_Operator));

    if (operator) {
        operator->type = type;
        operator->operands = NULL;
        operator->operand_count = 0;
    }

    return operator;
}

void CYPDF_FreeOperator(CYPDF_Operator* operator) {
    if (operator) {
        free(operator->operands);

        free(operator);
    }
}

void CYPDF_PrintOperator(CYPDF_Channel* const restrict channel, const CYPDF_Operator* const operator) {
    if (operator) {
        for (size_t i = 0; i < operator->operand_count; ++i) {
            CYPDF_PrintObjDirect(channel, operator->operands[i]);
            CYPDF_ChannelPrint(channel, " ");
        }
        
        CYPDF_ChannelPrint(channel, "%s", CYPDF_OperatorGetKey(operator));
    }
}


char* CYPDF_OperatorGetKey(const CYPDF_Operator* const operator) {
    char* name = NULL;

    if (operator) {
        name = operator_names[operator->type];
    }

    return name;
}

void CYPDF_OperatorAppendOperand(CYPDF_Operator* const restrict operator, CYPDF_Object* const restrict operand) {
    if (operator && operand) {
        operator->operands = CYPDF_realloc(operator->operands, (operator->operand_count + 1) * sizeof(CYPDF_Object*));
        operator->operands[operator->operand_count] = operand;
        ++operator->operand_count;
    }
}


bool CYPDF_OperatorIsPainting(const CYPDF_Operator* const restrict operator) {
    if (operator) {
        return operator->type >= CYPDF_OPERATOR_PATH_STROKE && operator->type <= CYPDF_OPERATOR_PATH_END;
    }

    return false;
}
