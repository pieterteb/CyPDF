#ifndef CYPDF_OPERATORS_H
#define CYPDF_OPERATORS_H


#include <stddef.h>
#include <stdint.h>



/*
This header file defines all graphic operators in PDF. Not all of them are necessarily implemented. The comments following the operator codes are of the form:

<operands> | <description>

If no operands are required:

-- | <description>

Operands enclosed in square braces "[]" are optional.
*/


/* Path Construction Names */
#define CYPDF_OPERATOR_PATH_BEGIN_N                 "m"
#define CYPDF_OPERATOR_PATH_LINESEG_N               "l"
#define CYPDF_OPERATOR_PATH_CBEZIER_N               "c"
#define CYPDF_OPERATOR_PATH_VBEZIER_N               "v"
#define CYPDF_OPERATOR_PATH_YBEZIER_N               "y"
#define CYPDF_OPERATOR_PATH_CLOSE_N                 "h"
#define CYPDF_OPERATOR_PATH_RECT_N                  "re"

/* Path Painting Names */
#define CYPDF_OPERATOR_PATH_STROKE_N                "S"
#define CYPDF_OPERATOR_PATH_CLOSE_STROKE_N          "s"
#define CYPDF_OPERATOR_PATH_NWNRFILL_N              "f"
#define CYPDF_OPERATOR_PATH_EORFILL_N               "f*"
#define CYPDF_OPERATOR_PATH_NWNRFILL_STROKE_N       "B"
#define CYPDF_OPERATOR_PATH_EORFILL_STROKE_N        "B*"
#define CYPDF_OPERATOR_PATH_CLOSE_NWNRFILL_STROKE_N "b"
#define CYPDF_OPERATOR_PATH_CLOSE_EORFILL_STROKE_N  "b*"
#define CYPDF_OPERATOR_PATH_END_N                   "n"

/* Path Clipping Names */
#define CYPDF_OPERATOR_PATH_NWNRCLIP_N              "W"
#define CYPDF_OPERATOR_PATH_EORCLIP_N               "W*"

/* NOTE
The operation "x y width height re" is equivalent to:

x y m
(x + width) y l
(x + width) (y + height) l
x (y + height) l
h
*/

/* Graphics State Names */
#define CYPDF_OPERATOR_GFX_STATE_SAVE_N             "q"
#define CYPDF_OPERATOR_GFX_STATE_RESTORE_N          "Q"
#define CYPDF_OPERATOR_GFX_STATE_MATRIX_N           "cm"
#define CYPDF_OPERATOR_GFX_STATE_LINE_WIDTH_N       "w"
#define CYPDF_OPERATOR_GFX_STATE_LINE_CAP_N         "J"
#define CYPDF_OPERATOR_GFX_STATE_LINE_JOIN_N        "j"
#define CYPDF_OPERATOR_GFX_STATE_MITER_LIMIT_N      "M"
#define CYPDF_OPERATOR_GFX_STATE_DASH_PATTERN_N     "d"
#define CYPDF_OPERATOR_GFX_STATE_INTENT_N           "ri"
#define CYPDF_OPERATOR_GFX_STATE_FLATNESS_N         "i"
#define CYPDF_OPERATOR_GFX_STATE_EXTGSTATE_N        "gs"

/* Color Names */
#define CYPDF_OPERATOR_COLOR_SPACE_STROKING_N       "CS"
#define CYPDF_OPERATOR_COLOR_SPACE_NONSTROKING_N    "cs"
#define CYPDF_OPERATOR_COLOR_STROKING_N             "SC"
#define CYPDF_OPERATOR_COLOR_STROKING_EXT_N         "SCN"
#define CYPDF_OPERATOR_COLOR_NONSTROKING_N          "sc"
#define CYPDF_OPERATOR_COLOR_NONSTROKING_EXT_N      "scn"
#define CYPDF_OPERATOR_COLOR_STROKING_GRAY_N        "G"
#define CYPDF_OPERATOR_COLOR_NONSTROKING_GRAY_N     "g"
#define CYPDF_OPERATOR_COLOR_STROKING_RGB_N         "RG"
#define CYPDF_OPERATOR_COLOR_NONSTROKING_RGB_N      "rg"
#define CYPDF_OPERATOR_COLOR_STROKING_CMYK_N        "K"
#define CYPDF_OPERATOR_COLOR_NONSTROKING_CMYK_N     "k"



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

    CYPDF_OPERATOR_COUNT,
};



typedef struct CYPDF_Operator {
    enum CYPDF_OPERATOR_TYPE    type;

    void**                      operands;
    size_t                      operand_count;
} CYPDF_Operator;


/**
 * @brief Create a new operator. Initializes the new operator with operands and operand_count. If operands is equal to NULL, operand_count is set to 0. Assumes type is a valid operator type.
 * 
 * @param type 
 * @param operands 
 * @param operand_count 
 * @return CYPDF_Operator* 
 */
CYPDF_Operator* CYPDF_NewOperator(const uint32_t type, const void* const* const operands, size_t operand_count);

void CYPDF_FreeOperator(CYPDF_Operator* operator);


const char* CYPDF_OperatorGetName(const CYPDF_Operator* const operator);

void CYPDF_OperatorAppendOperand(CYPDF_Operator* const operator, const void* const operand);



#endif /* CYPDF_OPERATORS_H */
