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



/* Path Operators */

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

/* Path Construction */
#define CYPDF_OPERATOR_PATH_BEGIN                   0x00000001      /* x y | Begin a new subpath by moving the current point to coordinates (x, y), omitting any connecting line segment. */
#define CYPDF_OPERATOR_PATH_LINESEG                 0x00000002      /* x y | Append a straight line segment from the current point to the point (x, y). */
#define CYPDF_OPERATOR_PATH_CBEZIER                 0x00000003      /* x1 y1 x2 y2 x3 y3 | Append a cubic Bézier curve to the current path. The curve extends from the current point to the point (x3, y3), using (x1, y1) and (x2, y2) as the Bézier control points. */
#define CYPDF_OPERATOR_PATH_VBEZIER                 0x00000004      /* x2 y2 x3 y3 | Append a cubic Bézier curve to the current path. The curve extends from the current point to the point (x3, y3), using the current point and (x2, y2) as the Bézier control points. */
#define CYPDF_OPERATOR_PATH_YBEZIER                 0x00000005      /* x1 y1 x3 y3 | Append a cubic Bézier curve to the current path. The curve extends from the current point to the point (x3, y3), using (x1, y1) and (x3, y3) as the Bézier control points. */
#define CYPDF_OPERATOR_PATH_CLOSE                   0x00000006      /* -- | Close the current subpath by appending a straight line segment from the current point to the starting point of the subpath. */
#define CYPDF_OPERATOR_PATH_RECT                    0x00000007      /* x y width height | Append a rectangle to the current path as a complete subpath, with lower-left corner (x, y) and dimensions width and height in user space. */

/* Path Painting */
#define CYPDF_OPERATOR_PATH_STROKE                  0x00000010      /* -- | Stroke the path. */
#define CYPDF_OPERATOR_PATH_CLOSE_STROKE            0x00000020      /* -- | Close and stroke the path. Same effect as h S. */
#define CYPDF_OPERATOR_PATH_NWNRFILL                0x00000030      /* -- | Fill the path, using the nonzero winding number rule (NWNR, see pdfreference1.7 page 232) to determine the region to fill. */
#define CYPDF_OPERATOR_PATH_EORFILL                 0x00000040      /* -- | Fill the path, using the even-odd rule (EOR, see pdfreference1.7 page 233) to determine the region to fill. */
#define CYPDF_OPERATOR_PATH_NWNRFILL_STROKE         0x00000050      /* -- | Fill and then stroke the path, using the nonzero winding number rule to determine the region to fill. */
#define CYPDF_OPERATOR_PATH_EORFILL_STROKE          0x00000060      /* -- | Fill and then stroke the path, using the even-odd rule to determine the region to fill. */
#define CYPDF_OPERATOR_PATH_CLOSE_NWNRFILL_STROKE   0x00000070      /* -- | Close, fill, and then stroke the path, using the nonzero winding number rule to determine the region to fill. Same effect as h B. */
#define CYPDF_OPERATOR_PATH_CLOSE_EORFILL_STROKE    0x00000080      /* -- | Close, fill, and then stroke the path, using the even-odd rule to determine the region to fill. Same effect as h B. */
#define CYPDF_OPERATOR_PATH_END                     0x00000090      /* -- | End the path object without filling or stroking it. */

/* Path Clipping */
#define CYPDF_OPERATOR_PATH_NWNRCLIP                0x00000100      /* -- | Modify the current clipping path by intersecting it with the current path, using the nonzero winding number rule to determine which regions lie inside the clipping path. */
#define CYPDF_OPERATOR_PATH_EORCLIP                 0x00000200      /* -- | Modify the current clipping path by intersecting it with the current path, using the even-odd rule to determine which regions lie inside the clipping path. */

#define CYPDF_OPERATOR_PATH_TYPE_CONSTRUCTION       0x0000000F
#define CYPDF_OPERATOR_PATH_TYPE_PAINTING           0x000000F0
#define CYPDF_OPERATOR_PATH_TYPE_CLIPPING           0x00000F00


/* Graphics State Operators */

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

/* Graphics State */
#define CYPDF_OPERATOR_GFX_STATE_SAVE               0x00001000      /* -- | Save the current graphics state on the graphics state stack. */
#define CYPDF_OPERATOR_GFX_STATE_RESTORE            0x00002000      /* -- | Restore the graphics state by removing the most recently saved state from the stack and making it the current state . */
#define CYPDF_OPERATOR_GFX_STATE_MATRIX             0x00003000      /* a b c d e f | Modify the current transformation matrix (CTM) by concatenating the specified matrix. */
#define CYPDF_OPERATOR_GFX_STATE_LINE_WIDTH         0x00004000      /* lineWidth | Set the line width in the graphics state. */
#define CYPDF_OPERATOR_GFX_STATE_LINE_CAP           0x00005000      /* lineCap | Set the line cap style in the graphics state. */
#define CYPDF_OPERATOR_GFX_STATE_LINE_JOIN          0x00006000      /* lineJoin | Set the line join style in the graphics state. */
#define CYPDF_OPERATOR_GFX_STATE_MITER_LIMIT        0x00007000      /* miterLimit | Set the miter limit in the graphics state. */
#define CYPDF_OPERATOR_GFX_STATE_DASH_PATTERN       0x00008000      /* dashArray dashPhase | Set the line dash pattern in the graphics state. */
#define CYPDF_OPERATOR_GFX_STATE_INTENT             0x00009000      /* intent | Set the color rendering intent in the graphics state. */
#define CYPDF_OPERATOR_GFX_STATE_FLATNESS           0x0000A000      /* flatness | Set the flatness tolerance in the graphics state. */
#define CYPDF_OPERATOR_GFX_STATE_EXTGSTATE          0x0000B000      /* dictName | Set the specified parameters in the graphics state. dictName is the name of a graphics state parameter dictionary in the ExtGState subdictionary of the current resource dictionary. */

#define CYPDF_OPERATOR_GFX_STATE                    0x0000F000



/* Color Operators */

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

/* Color */
#define CYPDF_OPERATOR_COLOR_SPACE_STROKING         0x00010000      /* name | Set the current color space to use for stroking operations. */
#define CYPDF_OPERATOR_COLOR_SPACE_NONSTROKING      0x00020000      /* name | Set the current color space to use for nonstroking operations. */
#define CYPDF_OPERATOR_COLOR_STROKING               0x00030000      /* c1 ... cn | Set the color to use for stroking operations in a device, CIE-based (other than ICCBased), or Indexed color space. */
#define CYPDF_OPERATOR_COLOR_STROKING_EXT           0x00040000      /* c1 ... cn [name] | Same as above but also supports Pattern, Separation, DeviceN, and ICCBased color spaces. */
#define CYPDF_OPERATOR_COLOR_NONSTROKING            0x00050000      /* c1 ... cn | Set the color to use for nonstroking operations in a device, CIE-based (other than ICCBased), or Indexed color space. */
#define CYPDF_OPERATOR_COLOR_NONSTROKING_EXT        0x00060000      /* c1 ... cn [name] | Same as above but also supports Pattern, Separation, DeviceN, and ICCBased color spaces. */
#define CYPDF_OPERATOR_COLOR_STROKING_GRAY          0x00070000      /* gray | Set the stroking color space to DeviceGray and set the gray level to use for stroking operations. */
#define CYPDF_OPERATOR_COLOR_NONSTROKING_GRAY       0x00080000      /* gray | Set the nonstroking color space to DeviceGray and set the gray level to use for stroking operations. */
#define CYPDF_OPERATOR_COLOR_STROKING_RGB           0x00090000      /* r g b | Set the stroking color space to DeviceRGB and set the color to use for stroking operations. */
#define CYPDF_OPERATOR_COLOR_NONSTROKING_RGB        0x000A0000      /* r g b | Set the nonstroking color space to DeviceRGB and set the color to use for stroking operations. */
#define CYPDF_OPERATOR_COLOR_STROKING_CMYK          0x000B0000      /* c m y k | Set the stroking color space to DeviceCMYK and set the color to use for stroking operations. */
#define CYPDF_OPERATOR_COLOR_NONSTROKING_CMYK       0x000C0000      /* c m y k | Set the nonstroking color space to DeviceCMYK and set the color to use for stroking operations. */

#define CYPDF_OPERATOR_COLOR                        0x000F0000



typedef struct CYPDF_Operator {
    uint32_t    type;

    void**      operands;
    size_t      operand_count;
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

void CYPDF_OperatorSetOperands(CYPDF_Operator* const operator, const void* const* const operands, size_t operand_count);

void CYPDF_FreeOperator(CYPDF_Operator* operator);



#endif /* CYPDF_OPERATORS_H */
