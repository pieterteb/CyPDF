#include "cypdf_text.h"
#include "cypdf_integer.h"
#include "cypdf_list.h"
#include "cypdf_log.h"
#include "cypdf_number.h"
#include "cypdf_operators.h"



static void CYPDF_TextAppend(CYPDF_Text* const text, CYPDF_Operator* const operator);


CYPDF_Text* CYPDF_NewText(void) {
    CYPDF_TRACE;

    return CYPDF_NewGraphic();
}

void CYPDF_FreeText(CYPDF_Text* text) {
    CYPDF_TRACE;

    CYPDF_FreeGraphic(text);
}


static void CYPDF_TextAppend(CYPDF_Text* const text, CYPDF_Operator* const operator) {
    CYPDF_TRACE;

    CYPFD_ListAppend(text->operator_list, operator);
}

void CYPDF_TextBegin(CYPDF_Text* const text) {
    CYPDF_TRACE;

    CYPDF_TextAppend(text, CYPDF_NewOperator(CYPDF_TEXT_BEGIN));
}

void CYPDF_TextEnd(CYPDF_Text* const text) {
    CYPDF_TRACE;

    CYPDF_TextAppend(text, CYPDF_NewOperator(CYPDF_TEXT_END));
}

void CYPDF_TextCharSpace(CYPDF_Text* const text, const float char_space) {
    CYPDF_TRACE;

    CYPDF_Operator* char_space_op = CYPDF_NewOperator(CYPDF_TEXT_CHAR_SPACE);
    CYPDF_OperatorAppend(char_space_op, CYPDF_NewNumber(text->memmgr, char_space));

    CYPDF_TextAppend(text, char_space_op);
}

void CYPDF_TextWordSpace(CYPDF_Text* const text, const float word_space) {
    CYPDF_TRACE;

    CYPDF_Operator* word_space_op = CYPDF_NewOperator(CYPDF_TEXT_WORD_SPACE);
    CYPDF_OperatorAppend(word_space_op, CYPDF_NewNumber(text->memmgr, word_space));

    CYPDF_TextAppend(text, word_space_op);
}

void CYPDF_TextScale(CYPDF_Text* const text, const float scale) {
    CYPDF_TRACE;

    CYPDF_Operator* scale_op = CYPDF_NewOperator(CYPDF_TEXT_SCALE);
    CYPDF_OperatorAppend(scale_op, CYPDF_NewNumber(text->memmgr, scale));

    CYPDF_TextAppend(text, scale_op);
}

void CYPDF_TextLeading(CYPDF_Text* const text, const float leading) {
    CYPDF_TRACE;

    CYPDF_Operator* leading_op = CYPDF_NewOperator(CYPDF_TEXT_LEADING);
    CYPDF_OperatorAppend(leading_op, CYPDF_NewNumber(text->memmgr, leading));

    CYPDF_TextAppend(text, leading_op);
}

/* Need to implement fonts. */
// void CYPDF_TextFont(CYPDF_Text* const text, CYPDF_Font* const font, const float size) {
//     CYPDF_TRACE;

//     CYPDF_Operator* font_op = CYPDF_NewOperator(CYPDF_TEXT_FONT);
//     CYPDF_OperatorAppend(font_op, font);
//     CYPDF_OperatorAppend(font_op, CYPDF_NewNumber(text->memmgr, size));

//     CYPDF_TextAppend(text, font_op);
// }

void CYPDF_TextRender(CYPDF_Text* const text, const int render) {
    CYPDF_TRACE;

    CYPDF_Operator* render_op = CYPDF_NewOperator(CYPDF_TEXT_RENDER);
    CYPDF_OperatorAppend(render_op, CYPDF_NewInteger(text->memmgr, render));

    CYPDF_TextAppend(text, render_op);
}

void CYPDF_TextRise(CYPDF_Text* const text, const float rise) {
    CYPDF_TRACE;

    CYPDF_Operator* rise_op = CYPDF_NewOperator(CYPDF_TEXT_RISE);
    CYPDF_OperatorAppend(rise_op, CYPDF_NewNumber(text->memmgr, rise));

    CYPDF_TextAppend(text, rise_op);
}

void CYPDF_TextOffset(CYPDF_Text* const text, const float x_offset, const float y_offset) {
    CYPDF_TRACE;

    CYPDF_Operator* offset_op = CYPDF_NewOperator(CYPDF_TEXT_OFFSET);
    CYPDF_OperatorAppend(offset_op, CYPDF_NewNumber(text->memmgr, x_offset));
    CYPDF_OperatorAppend(offset_op, CYPDF_NewNumber(text->memmgr, y_offset));

    CYPDF_TextAppend(text, offset_op);
}

void CYPDF_TextOffsetPersistent(CYPDF_Text* const text, const float x_offset, const float y_offset) {
    CYPDF_TRACE;

    CYPDF_Operator* offset_op = CYPDF_NewOperator(CYPDF_TEXT_OFFSET_PERSISTENT);
    CYPDF_OperatorAppend(offset_op, CYPDF_NewNumber(text->memmgr, x_offset));
    CYPDF_OperatorAppend(offset_op, CYPDF_NewNumber(text->memmgr, y_offset));

    CYPDF_TextAppend(text, offset_op);
}
