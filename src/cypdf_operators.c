#include <stddef.h>
#include <stdint.h>

#include "cypdf_operators.h"
#include "cypdf_utils.h"



CYPDF_Operator* CYPDF_NewOperator(const uint32_t type, const void* const* const operands, size_t operand_count) {
    CYPDF_Operator* operator = (CYPDF_Operator*)CYPDF_smalloc(sizeof(CYPDF_Operator));

    if (operator) {
        operator->type = type;
        operator->operands = operands;

        if (!operands) {
            operand_count = 0;
        }
        operator->operand_count = operand_count;
    }

    return operator;
}

void CYPDF_OperatorSetOperands(CYPDF_Operator* const operator, const void* const* const operands, size_t operand_count) {
    if (operator) {
        free(operator->operands);
        operator->operands = operands;

        if (!operands) {
            operand_count = 0;
        }
        operator->operand_count = operand_count;
    }
}

void CYPDF_FreeOperator(CYPDF_Operator* operator) {
    if (operator) {
        free(operator->operands);

        free(operator);
    }
}
