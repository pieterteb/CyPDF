#ifndef CYPDF_GRAPHICS_H
#define CYPDF_GRAPHICS_H


#include <stdio.h>

#include "cypdf_stream.h"
#include "cypdf_types.h"



/* Path Construction Operator Codes (PCOC) */
#define CYPDF_PCOC_NEW                      "m"
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


/* Path Construction Operators (PCO) */
enum CYPDF_PCO_TYPE {
    CYPDF_PCO_NEW = 0,              /* x y m | Begin a new subpath at (x,y). */
    CYPDF_PCO_LINESEG,              /* x y l | Append a straight line segment from the current point to (x,y). */
    CYPDF_PCO_CBEZIER,              /* x_1 y_1 x_2 y_2 x_3 y_3 c | Append a cubic Bézier curve using (x_1,y_1) and (x_2,y_2) as control points. The curve extends from the current point to (x_3,y_3). */
    CYPDF_PCO_VBEZIER,              /* x_2 y_2 x_3 y_3 v | Append a cubic Bézier curve using the current point and (x_2,y_2) as control points. The curve extends from the current point to (x_3,y_3). */
    CYPDF_PCO_YBEZIER,              /* x_1 y_1 x_3 y_3 y | Append a cubic Bézier curve using (x_1,y_1) and (x_3,y_3) as control points. The curve extends from the current point to (x_3,y_3). */
    CYPDF_PCO_CLOSE,                /* -- h | Close current subpath by appending a straight line segment from the current point to the starting point of the subpath. */
    CYPDF_PCO_RECT,                 /* x y width height re | Append a rectangle to the current path as a complete subpath, with lower-left corner (x,y) and dimensions width and height in user space. */

    CYPDF_PCO_COUNT,

    CYPDF_PCO_UNKNOWN,
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

    CYPDF_PPO_UNKNOWN,
};


/* CYPDF Path Construction Operator (PCO) */
typedef char* CYPDF_PCO;                            /* A CYPDF_PCO is represented by a null terminated string. */


typedef struct _CYPDF_Path {
    CYPDF_BYTE*                 path_str;           /* String representation of an arbitrary amount of Path Construction Operators. */
    CYPDF_SIZE                  path_str_size;      /* Size of pco_string. */
    CYPDF_SIZE                  pco_count;          /* Number of pco's represented pco_string. */

    enum CYPDF_PPO_TYPE         ppo;                /* Path-painting operator. */
} CYPDF_Path;


CYPDF_Path* CYPDF_New_Path(enum CYPDF_PPO_TYPE ppo);

/**
 * @brief Appends a PCO (Path Construction Operator) to path.
 * 
 * @param path 
 * @param endpoint Used for CYPDF_PCO_NEW, CYPDF_PCO_LINESEG, CYPDF_PCO_CBEZIER, CYPDF_PCO_VBEZIER, CYPDF_PCO_YBEZIER and CYPDF_PCO_RECT.
 * @param point1 Used for CYPDF_PCO_CBEZIER and CYPDF_PCO_YBEZIER as Bézier control point. Used for CYPDF_PCO_RECT as (width,height).
 * @param point2  Used for CYPDF_PCO_CBEZIER and CYPDF_PCO_VBEZIER as Bézier control point.
 */
void CYPDF_Path_Append(CYPDF_Path* path, enum CYPDF_PCO_TYPE operator, CYPDF_Point endpoint, CYPDF_Point point1, CYPDF_Point point2);

void CYPDF_Write_Path_To_Stream(CYPDF_Obj_Stream* stream, CYPDF_Path* path);

void CYPDF_Free_Path(CYPDF_Path* path);



#endif /* CYPDF_GRAPHICS_H */
