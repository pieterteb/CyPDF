#ifndef CYPDF_OPERATORS_H
#define CYPDF_OPERATORS_H


#include <stddef.h>
#include <stdbool.h>

#include "cypdf_list.h"
#include "cypdf_types.h"



/*
This header file defines graphic operators in PDF. The comments following the operator codes are of the form:

<operands> | <description>

If no operands are required:

-- | <description>

Operands enclosed in square braces "[]" are optional.
*/


/* Path Construction Keywords */
#define CYPDF_OPERATOR_PATH_BEGIN_K                 "m"
#define CYPDF_OPERATOR_PATH_LINESEG_K               "l"
#define CYPDF_OPERATOR_PATH_CBEZIER_K               "c"
#define CYPDF_OPERATOR_PATH_VBEZIER_K               "v"
#define CYPDF_OPERATOR_PATH_YBEZIER_K               "y"
#define CYPDF_OPERATOR_PATH_CLOSE_K                 "h"
#define CYPDF_OPERATOR_PATH_RECT_K                  "re"

/* Path Painting Keywords */
#define CYPDF_OPERATOR_PATH_STROKE_K                "S"
#define CYPDF_OPERATOR_PATH_CLOSE_STROKE_K          "s"
#define CYPDF_OPERATOR_PATH_NWNRFILL_K              "f"
#define CYPDF_OPERATOR_PATH_EORFILL_K               "f*"
#define CYPDF_OPERATOR_PATH_NWNRFILL_STROKE_K       "B"
#define CYPDF_OPERATOR_PATH_EORFILL_STROKE_K        "B*"
#define CYPDF_OPERATOR_PATH_CLOSE_NWNRFILL_STROKE_K "b"
#define CYPDF_OPERATOR_PATH_CLOSE_EORFILL_STROKE_K  "b*"
#define CYPDF_OPERATOR_PATH_END_K                   "n"

/* Path Clipping Keywords */
#define CYPDF_OPERATOR_PATH_NWNRCLIP_K              "W"
#define CYPDF_OPERATOR_PATH_EORCLIP_K               "W*"

/* NOTE
The operation "x y width height re" is equivalent to:

x y m
(x + width) y l
(x + width) (y + height) l
x (y + height) l
h
*/

/* Graphics State Keywords */
#define CYPDF_OPERATOR_GFX_STATE_SAVE_K             "q"
#define CYPDF_OPERATOR_GFX_STATE_RESTORE_K          "Q"
#define CYPDF_OPERATOR_GFX_STATE_MATRIX_K           "cm"
#define CYPDF_OPERATOR_GFX_STATE_LINE_WIDTH_K       "w"
#define CYPDF_OPERATOR_GFX_STATE_LINE_CAP_K         "J"
#define CYPDF_OPERATOR_GFX_STATE_LINE_JOIN_K        "j"
#define CYPDF_OPERATOR_GFX_STATE_MITER_LIMIT_K      "M"
#define CYPDF_OPERATOR_GFX_STATE_DASH_PATTERN_K     "d"
#define CYPDF_OPERATOR_GFX_STATE_INTENT_K           "ri"
#define CYPDF_OPERATOR_GFX_STATE_FLATNESS_K         "i"
#define CYPDF_OPERATOR_GFX_STATE_EXTGSTATE_K        "gs"

/* Color Keywords */
#define CYPDF_OPERATOR_COLOR_SPACE_STROKING_K       "CS"
#define CYPDF_OPERATOR_COLOR_SPACE_NONSTROKING_K    "cs"
#define CYPDF_OPERATOR_COLOR_STROKING_K             "SC"
#define CYPDF_OPERATOR_COLOR_STROKING_EXT_K         "SCN"
#define CYPDF_OPERATOR_COLOR_NONSTROKING_K          "sc"
#define CYPDF_OPERATOR_COLOR_NONSTROKING_EXT_K      "scn"
#define CYPDF_OPERATOR_COLOR_STROKING_GRAY_K        "G"
#define CYPDF_OPERATOR_COLOR_NONSTROKING_GRAY_K     "g"
#define CYPDF_OPERATOR_COLOR_STROKING_RGB_K         "RG"
#define CYPDF_OPERATOR_COLOR_NONSTROKING_RGB_K      "rg"
#define CYPDF_OPERATOR_COLOR_STROKING_CMYK_K        "K"
#define CYPDF_OPERATOR_COLOR_NONSTROKING_CMYK_K     "k"

/* Text Operators */
#define CYPDF_OP_TEXT_BEGIN                         "BT"
#define CYPDF_OP_TEXT_END                           "ET"
#define CYPDF_OP_TEXT_CHAR_SPACE                    "Tc"
#define CYPDF_OP_TEXT_WORD_SPACE                    "Tw"
#define CYPDF_OP_TEXT_SCALE                         "Tz"
#define CYPDF_OP_TEXT_LEADING                       "TL"
#define CYPDF_OP_TEXT_FONT                          "Tf"
#define CYPDF_OP_TEXT_RENDER                        "Tr"
#define CYPDF_OP_TEXT_RISE                          "Ts"

/* Text Positioning Operators */
#define CYPDF_OP_TEXT_OFFSET                        "Td"
#define CYPDF_OP_TEXT_OFFSET_PERSISTENT             "TD"
#define CYPDF_OP_TEXT_MATRIX                        "Tm"
#define CYPDF_OP_TEXT_NEXT_LINE                     "T*"

/* Text Showing Operators */
#define CYPDF_OP_TEXT_SHOW                          "Tj"
#define CYPDF_OP_TEXT_SHOW_NEXT_LINE                "\'"
#define CYPDF_OP_TEXT_MOD_SHOW_NEXT_LINE            "\""
#define CYPDF_OP_TEXT_SHOW_MULT                     "TJ"



enum CYPDF_OPERATOR_TYPE {
    /* Path Construction */
    CYPDF_OPERATOR_PATH_BEGIN = 0,                  /* x y | Begin a new subpath by moving the current point to coordinates (x, y), omitting any connecting line segment. */
    CYPDF_OPERATOR_PATH_LINESEG,                    /* x y | Append a straight line segment from the current point to the point (x, y). */
    CYPDF_OPERATOR_PATH_CBEZIER,                    /* x1 y1 x2 y2 x3 y3 | Append a cubic Bézier curve to the current path. The curve extends from the current point to the point (x3, y3), using (x1, y1) and (x2, y2) as the Bézier control points. */
    CYPDF_OPERATOR_PATH_VBEZIER,                    /* x2 y2 x3 y3 | Append a cubic Bézier curve to the current path. The curve extends from the current point to the point (x3, y3), using the current point and (x2, y2) as the Bézier control points. */
    CYPDF_OPERATOR_PATH_YBEZIER,                    /* x1 y1 x3 y3 | Append a cubic Bézier curve to the current path. The curve extends from the current point to the point (x3, y3), using (x1, y1) and (x3, y3) as the Bézier control points. */
    CYPDF_OPERATOR_PATH_CLOSE,                      /* -- | Close the current subpath by appending a straight line segment from the current point to the starting point of the subpath. */
    CYPDF_OPERATOR_PATH_RECT,                       /* x y width height | Append a rectangle to the current path as a complete subpath, with lower-left corner (x, y) and dimensions width and height in user space. */

    /* Path Painting */
    CYPDF_OPERATOR_PATH_STROKE,                     /* -- | Stroke the path. */
    CYPDF_OPERATOR_PATH_CLOSE_STROKE,               /* -- | Close and stroke the path. Same effect as h S. */
    CYPDF_OPERATOR_PATH_NWNRFILL,                   /* -- | Fill the path, using the nonzero winding number rule (NWNR, see pdfreference1.7 page 232) to determine the region to fill. */
    CYPDF_OPERATOR_PATH_EORFILL,                    /* -- | Fill the path, using the even-odd rule (EOR, see pdfreference1.7 page 233) to determine the region to fill. */
    CYPDF_OPERATOR_PATH_NWNRFILL_STROKE,            /* -- | Fill and then stroke the path, using the nonzero winding number rule to determine the region to fill. */
    CYPDF_OPERATOR_PATH_EORFILL_STROKE,             /* -- | Fill and then stroke the path, using the even-odd rule to determine the region to fill. */
    CYPDF_OPERATOR_PATH_CLOSE_NWNRFILL_STROKE,      /* -- | Close, fill, and then stroke the path, using the nonzero winding number rule to determine the region to fill. Same effect as h B. */
    CYPDF_OPERATOR_PATH_CLOSE_EORFILL_STROKE,       /* -- | Close, fill, and then stroke the path, using the even-odd rule to determine the region to fill. Same effect as h B. */
    CYPDF_OPERATOR_PATH_END,                        /* -- | End the path object without filling or stroking it. */

    /* Path Clipping */
    CYPDF_OPERATOR_PATH_NWNRCLIP,                   /* -- | Modify the current clipping path by intersecting it with the current path, using the nonzero winding number rule to determine which regions lie inside the clipping path. */
    CYPDF_OPERATOR_PATH_EORCLIP,                    /* -- | Modify the current clipping path by intersecting it with the current path, using the even-odd rule to determine which regions lie inside the clipping path. */

    /* Graphics State */
    CYPDF_OPERATOR_GFX_STATE_SAVE,                  /* -- | Save the current graphics state on the graphics state stack. */
    CYPDF_OPERATOR_GFX_STATE_RESTORE,               /* -- | Restore the graphics state by removing the most recently saved state from the stack and making it the current state . */
    CYPDF_OPERATOR_GFX_STATE_MATRIX,                /* a b c d e f | Modify the current transformation matrix (CTM) by concatenating the specified matrix. */
    CYPDF_OPERATOR_GFX_STATE_LINE_WIDTH,            /* lineWidth | Set the line width in the graphics state. */
    CYPDF_OPERATOR_GFX_STATE_LINE_CAP,              /* lineCap | Set the line cap style in the graphics state. */
    CYPDF_OPERATOR_GFX_STATE_LINE_JOIN,             /* lineJoin | Set the line join style in the graphics state. */
    CYPDF_OPERATOR_GFX_STATE_MITER_LIMIT,           /* miterLimit | Set the miter limit in the graphics state. */
    CYPDF_OPERATOR_GFX_STATE_DASH_PATTERN,          /* dashArray dashPhase | Set the line dash pattern in the graphics state. */
    CYPDF_OPERATOR_GFX_STATE_INTENT,                /* intent | Set the color rendering intent in the graphics state. */
    CYPDF_OPERATOR_GFX_STATE_FLATNESS,              /* flatness | Set the flatness tolerance in the graphics state. */
    CYPDF_OPERATOR_GFX_STATE_EXTGSTATE,             /* dictName | Set the specified parameters in the graphics state. dictName is the name of a graphics state parameter dictionary in the ExtGState subdictionary of the current resource dictionary. */

    /* Color */
    CYPDF_OPERATOR_COLOR_SPACE_STROKING,            /* name | Set the current color space to use for stroking operations. */
    CYPDF_OPERATOR_COLOR_SPACE_NONSTROKING,         /* name | Set the current color space to use for nonstroking operations. */
    CYPDF_OPERATOR_COLOR_STROKING,                  /* c1 ... cn | Set the color to use for stroking operations in a device, CIE-based (other than ICCBased), or Indexed color space. */
    CYPDF_OPERATOR_COLOR_STROKING_EXT,              /* c1 ... cn [name] | Same as above but also supports Pattern, Separation, DeviceN, and ICCBased color spaces. */
    CYPDF_OPERATOR_COLOR_NONSTROKING,               /* c1 ... cn | Set the color to use for nonstroking operations in a device, CIE-based (other than ICCBased), or Indexed color space. */
    CYPDF_OPERATOR_COLOR_NONSTROKING_EXT,           /* c1 ... cn [name] | Same as above but also supports Pattern, Separation, DeviceN, and ICCBased color spaces. */
    CYPDF_OPERATOR_COLOR_STROKING_GRAY,             /* gray | Set the stroking color space to DeviceGray and set the gray level to use for stroking operations. */
    CYPDF_OPERATOR_COLOR_NONSTROKING_GRAY,          /* gray | Set the nonstroking color space to DeviceGray and set the gray level to use for stroking operations. */
    CYPDF_OPERATOR_COLOR_STROKING_RGB,              /* r g b | Set the stroking color space to DeviceRGB and set the color to use for stroking operations. */
    CYPDF_OPERATOR_COLOR_NONSTROKING_RGB,           /* r g b | Set the nonstroking color space to DeviceRGB and set the color to use for stroking operations. */
    CYPDF_OPERATOR_COLOR_STROKING_CMYK,             /* c m y k | Set the stroking color space to DeviceCMYK and set the color to use for stroking operations. */
    CYPDF_OPERATOR_COLOR_NONSTROKING_CMYK,          /* c m y k | Set the nonstroking color space to DeviceCMYK and set the color to use for stroking operations. */

    /* Text */
    CYPDF_TEXT_BEGIN,                               /* -- | Begin a text object, initializing the text matrix, T_m, and the text line matrix, T_lm, to the identity matrix. Text objects cannot be nested; a second BT cannot appear before an ET. */
    CYPDF_TEXT_END,                                 /* -- | End a text object, discarding the text matrix. */
    CYPDF_TEXT_CHAR_SPACE,                          /* charSpace | Set the character spacing, T_c, to charSpace, which is a number expressed in unscaled text space units. */
    CYPDF_TEXT_WORD_SPACE,                          /* wordSpace | Set the word spacing, T_w, to wordSpace, which is a number expressed in unscaled text space units. */
    CYPDF_TEXT_SCALE,                               /* scale | Set the horizontal scaling, T_h, to (scale ÷ 100). scale is a number specifying the percentage of the normal width. */
    CYPDF_TEXT_LEADING,                             /* leading | Set the text leading, T_l, to leading, which is a number expressed in unscaled text space units. */
    CYPDF_TEXT_FONT,                                /* font size | Set the text font, T_f, to font and the text font size, T_fs, to size. font is the name of a font resource in the Font subdictionary of the current resource dictionary; size is a number representing a scale factor. */
    CYPDF_TEXT_RENDER,                              /* render | Set the text rendering mode, T_mode , to render, which is an integer. */
    CYPDF_TEXT_RISE,                                /* rise | Set the text rise, T_rise, to rise, which is a number expressed in unscaled text space units. */

    CYPDF_TEXT_OFFSET,                              /* t_x t_y | Move to the start of the next line, offset from the start of the current line by (t_x, t_y). t_x and t_y are numbers expressed in unscaled text space units. */
    CYPDF_TEXT_OFFSET_PERSISTENT,                   /* t_x t_y | Move to the start of the next line, offset from the start of the current line by (t_x, t_y). As a side effect, this operator sets the leading parameter in the text state. */
    CYPDF_TEXT_MATRIX,                              /* a b c d e f | Set the text matrix, T_m, and the text line matrix, T_lm. */
    CYPDF_TEXT_NEXT_LINE,                           /* -- | Move to the start of the next line. */

    CYPDF_TEXT_SHOW,                                /* string | Show a text string. */
    CYPDF_TEXT_SHOW_NEXT_LINE,                      /* string | Move to the next line and show a text string. */
    CYPDF_TEXT_MOD_SHOW_NEXT_LINE,                  /* a_w a_c string | Move to the next line and show a text string, using a_w as the word spacing and a_c as the character spacing (setting the corresponding parameters in the text state). */
    CYPDF_TEXT_SHOW_MULT,                           /* array | Show one or more text strings, allowing individual glyph positioning. */

    CYPDF_OPERATOR_COUNT
};



typedef struct CYPDF_Operator {
    enum CYPDF_OPERATOR_TYPE    type;

    CYPDF_List*                 operand_list;
} CYPDF_Operator;


CYPDF_Operator* CYPDF_NewOperator(const enum CYPDF_OPERATOR_TYPE type);

void CYPDF_FreeOperator(CYPDF_Operator* operator);

void CYPDF_PrintOperator(CYPDF_Channel* const channel, const CYPDF_Operator* const operator);


char* CYPDF_OperatorGetKey(const CYPDF_Operator* const operator);

void CYPDF_OperatorAppendOperand(CYPDF_Operator* const operator, CYPDF_Object* const operand);


bool CYPDF_OperatorIsPainting(const CYPDF_Operator* const restrict operator);



#endif /* CYPDF_OPERATORS_H */
