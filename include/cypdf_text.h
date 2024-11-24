#ifndef CYPDF_TEXT_H
#define CYPDF_TEXT_H


#include "cypdf_graphics.h"
#include "cypdf_operators.h"



typedef CYPDF_Graphic CYPDF_Text;


CYPDF_Text* CYPDF_NewText(void);

void CYPDF_FreeText(CYPDF_Text* text);


void CYPDF_TextBegin(CYPDF_Text* const text);

void CYPDF_TextEnd(CYPDF_Text* const text);

void CYPDF_TextCharSpace(CYPDF_Text* const text, const float char_space);

void CYPDF_TextWordSpace(CYPDF_Text* const text, const float word_space);

void CYPDF_TextScale(CYPDF_Text* const text, const float scale);

void CYPDF_TextLeading(CYPDF_Text* const text, const float leading);

/* Need to implement fonts. */
// void CYPDF_TextFont(CYPDF_Text* const text, CYPDF_Font* const font, const float size);

void CYPDF_TextRender(CYPDF_Text* const text, const int render);

void CYPDF_TextRise(CYPDF_Text* const text, const float rise);

void CYPDF_TextOffset(CYPDF_Text* const text, const float x_offset, const float y_offset);

void CYPDF_TextOffsetPersistent(CYPDF_Text* const text, const float x_offset, const float y_offset);



#endif /* CYPDF_TEXT_H */
