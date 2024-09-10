#ifndef CYPDF_GRAPHICS_H
#define CYPDF_GRAPHICS_H


#include <stdio.h>

#include "cypdf_stream.h"
#include "cypdf_types.h"



/* Path Construction Operator Codes (PCOC) */
#define CYPDF_PCOC_BEGIN                    "m"
#define CYPDF_PCOC_LINESEG                  "l"
#define CYPDF_PCOC_CBEZIER                  "c"
#define CYPDF_PCOC_VBEZIER                  "v"
#define CYPDF_PCOC_YBEZIER                  "y"
#define CYPDF_PCOC_CLOSE                    "h"
#define CYPDF_PCOC_RECT                     "re"

/* Path-painting Operator Codes (PPOC) */
#define CYPDF_PPOC_STROKE                   "S"
#define CYPDF_PPOC_CLOSE_STROKE             "s"
#define CYPDF_PPOC_NWNRFILL                 "f"
// #define CYPDF_PPOC_FFILL                    "F" /* Should never be used. Only exists for compatibility. */
#define CYPDF_PPOC_EORFILL                  "f*"
#define CYPDF_PPOC_NWNRFILL_STROKE          "B"
#define CYPDF_PPOC_EORFILL_STROKE           "B*"
#define CYPDF_PPOC_CLOSE_NWNRFILL_STROKE    "b"
#define CYPDF_PPOC_CLOSE_EORFILL_STROKE     "b*"
#define CYPDF_PPOC_END                      "n"

/* Clipping Path Operator Codes (CPOC) */
#define CYPDF_CPOC_NWNRCLIP                 "W"
#define CYPDF_CPOC_EORCLIP                  "W*"


/* Path Construction Operators (PCO) */
enum CYPDF_PCO_TYPE {
    CYPDF_PCO_BEGIN = 0,            /* x y m | Begin a new subpath at (x,y). */
    CYPDF_PCO_LINESEG,              /* x y l | Append a straight line segment from the current point to (x,y). */
    CYPDF_PCO_CBEZIER,              /* x_1 y_1 x_2 y_2 x_3 y_3 c | Append a cubic Bézier curve using (x_1,y_1) and (x_2,y_2) as control points. The curve extends from the current point to (x_3,y_3). */
    CYPDF_PCO_VBEZIER,              /* x_2 y_2 x_3 y_3 v | Append a cubic Bézier curve using the current point and (x_2,y_2) as control points. The curve extends from the current point to (x_3,y_3). */
    CYPDF_PCO_YBEZIER,              /* x_1 y_1 x_3 y_3 y | Append a cubic Bézier curve using (x_1,y_1) and (x_3,y_3) as control points. The curve extends from the current point to (x_3,y_3). */
    CYPDF_PCO_CLOSE,                /* -- h | Close current subpath by appending a straight line segment from the current point to the starting point of the subpath. */
    CYPDF_PCO_RECT,                 /* x y width height re | Append a rectangle to the current path as a complete subpath, with lower-left corner (x,y) and dimensions width and height in user space. */

    CYPDF_PCO_COUNT,
};

/*
The operation x y width height re is equivalent to:

x y m
(x + width) y l
(x + width) (y + height) l
x (y + height) l
h
*/

/* Path-painting Operators (PPO) */
enum CYPDF_PPO_TYPE {
    CYPDF_PPO_STROKE = 0,               /* Stroke the path. */
    CYPDF_PPO_CLOSE_STROKE,             /* Close and stroke the path. Same effect as h S. */
    CYPDF_PPO_NWNRFILL,                 /* Fill the path, using the nonzero winding number rule (NWNR, see pdfreference1.7 page 232) to determine the region to fill. */
    // CYPDF_PPO_FFILL,
    CYPDF_PPO_EORFILL,                  /* Fill the path, using the even-odd rule (EOR, see pdfreference1.7 page 233) to determine the region to fill. */
    CYPDF_PPO_NWNRFILL_STROKE,          /* Fill and then stroke the path, using the nonzero winding number rule to determine the region to fill. */
    CYPDF_PPO_EORFILL_STROKE,           /* Fill and then stroke the path, using the even-odd rule to determine the region to fill. */
    CYPDF_PPO_CLOSE_NWNRFILL_STROKE,    /* Close, fill, and then stroke the path, using the nonzero winding number rule to determine the region to fill. Same effect as h B. */
    CYPDF_PPO_CLOSE_EORFILL_STROKE,     /* Close, fill, and then stroke the path, using the even-odd rule to determine the region to fill. Same effect as h B*. */
    CYPDF_PPO_END,                      /* End the path object without filling or stroking it. */

    CYPDF_PPO_COUNT,
};


/* Clipping Path Operators (CPO). */
enum CYPDF_CPO_TYPE {
    CYPDF_CPO_NONE = 0,
    CYPDF_CPO_NWNRCLIP,
    CYPDF_CPO_EORCLIP,

    CYPDF_CPO_COUNT,
};


/* CYPDF Path Construction Operator (PCO) */
typedef char* CYPDF_PCO;                                /* A CYPDF_PCO is represented by a null terminated string. */


typedef struct _CYPDF_Path {
    CYPDF_BYTE*                 path_str;               /* String representation of an arbitrary amount of Path Construction Operators. */
    CYPDF_SIZE                  path_str_size;          /* Size of pco_string. */
    CYPDF_SIZE                  pco_count;              /* Number of pco's represented pco_string. */
    enum CYPDF_PCO_TYPE*        pco_types;              /* They types of the pco's. */

    CYPDF_Point                 curr_start_point;       /* The point at which the current sub path started. In other words, the point that was passed in the most recent CYPDF_Path_Append_Begin call. */
    CYPDF_Point                 curr_point;             /* The point at which the next pco will start. */

    enum CYPDF_CPO_TYPE         cpo;                    /* Clipping path operator. */
    enum CYPDF_PPO_TYPE         ppo;                    /* Path-painting operator. */
} CYPDF_Path;


CYPDF_Path* CYPDF_New_Path(enum CYPDF_PPO_TYPE ppo, enum CYPDF_CPO_TYPE cpo);


/**
 * @brief Begin a new subpath by changing path->curr_point to @a start_point, omitting any connecting line segment. If the previous path construction operator in the current path was also CYPDF_PCO_BEGIN, the new CYPDF_PCO_BEGIN overrides it; no vestige of the previous CYPDF_PCO_BEGIN operation remains in the path. (from: https://opensource.adobe.com/dc-acrobat-sdk-docs/pdfstandards/PDF32000_2008.pdf Table 4.9)
 * 
 * @param path 
 * @param start_point Coordinates of start of new subpath in User Units.
 */
void CYPDF_Path_Append_Begin(CYPDF_Path* path, CYPDF_Point start_point);

/**
 * @brief Append a straight line segment from path->curr_point to @a end_point. The new path->curr_point is @a end_point. (from: https://opensource.adobe.com/dc-acrobat-sdk-docs/pdfstandards/PDF32000_2008.pdf Table 4.9)
 * 

 * 
 * @param path 
 * @param end_point End point of the line segment in User Units.
 */
void CYPDF_Path_Append_Lineseg(CYPDF_Path* path, CYPDF_Point end_point);

/**
 * @brief Append a cubic Bézier curve to the current path. The curve extends from path->curr_point to @a end_point, using @a ctrl_point1 and @a ctrl_point2 as the Bézier control points. The new path->curr_point is @a end_point. (from: https://opensource.adobe.com/dc-acrobat-sdk-docs/pdfstandards/PDF32000_2008.pdf Table 4.9)
 * 
 * @param path 
 * @param ctrl_point1 First Bézier control point in User Units.
 * @param ctrl_point2 Second Bézier control point in User Units.
 * @param end_point End point of the Bézier curve in User Units.
 */
void CYPDF_Path_Append_CBezier(CYPDF_Path* path, CYPDF_Point ctrl_point1, CYPDF_Point ctrl_point2, CYPDF_Point end_point);

/**
 * @brief Append a cubic Bézier curve to the current path. The curve extends from path->curr_point to @a end_point, using path->curr_point and @a ctrl_point2 as the Bézier control points. The new path->curr_point is @a end_point. (from: https://opensource.adobe.com/dc-acrobat-sdk-docs/pdfstandards/PDF32000_2008.pdf Table 4.9)
 * 
 * @param path 
 * @param ctrl_point2 Second Bézier control point in User Units.
 * @param end_point End point of the Bézier curve in User Units.
 */
void CYPDF_Path_Append_VBezier(CYPDF_Path* path, CYPDF_Point ctrl_point2, CYPDF_Point end_point);

/**
 * @brief Append a cubic Bézier curve to the current path. The curve extends from path->curr_point to @a end_point, using @a ctrl_point1 and @a end_point as the Bézier control points. The new path->curr_point is @a end_point. (from: https://opensource.adobe.com/dc-acrobat-sdk-docs/pdfstandards/PDF32000_2008.pdf Table 4.9)
 * 
 * @param path 
 * @param ctrl_point1 First Bézier control point in User Units.
 * @param end_point End point of the Bézier curve in User Units.
 */
void CYPDF_Path_Append_YBezier(CYPDF_Path* path, CYPDF_Point ctrl_point1, CYPDF_Point end_point);

/**
 * @brief Close the current subpath by appending a straight line segment from path->curr_point to path->curr_start_point. If the current subpath is already closed, CYPDF_PCO_CLOSE does nothing. This operator terminates the current subpath. Appending another segment to the current path begins a new subpath, even if the new segment begins at the endpoint reached by the h operation. (from: https://opensource.adobe.com/dc-acrobat-sdk-docs/pdfstandards/PDF32000_2008.pdf Table 4.9)
 * 
 * @param path 
 */
void CYPDF_Path_Append_Close(CYPDF_Path* path);

/**
 * @brief Append a rectangle to the current path as a complete subpath, with lower-left corner @a ll_corner and dimensions @a width and @a height in user space. (from: https://opensource.adobe.com/dc-acrobat-sdk-docs/pdfstandards/PDF32000_2008.pdf Table 4.9)
 * 
 * @param path 
 * @param ll_corner Lower-left corner of rectangle.
 * @param width Width of rectangle in User Units.
 * @param height Height of rectangle in User Units.
 */
void CYPDF_Path_Append_Rect(CYPDF_Path* path, CYPDF_Point ll_corner, CYPDF_REAL width, CYPDF_REAL height);


void CYPDF_Write_Path_To_Stream(CYPDF_Obj_Stream* stream, CYPDF_Path* path);

void CYPDF_Free_Path(CYPDF_Path* path);



#endif /* CYPDF_GRAPHICS_H */
