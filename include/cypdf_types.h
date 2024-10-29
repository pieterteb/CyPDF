#ifndef CYPDF_TYPES_H
#define CYPDF_TYPES_H


#include "cypdf_print.h"



/* CYPDF_Point struct */
typedef struct _CYPDF_Point {
    float x;
    float y;
} CYPDF_Point;

#define CYPDF_TO_POINT(x, y)                (CYPDF_Point){ (float)(x), (float)(y) }


/* CYPDF_Rect struct */
typedef struct _CYPDF_Rect {
    CYPDF_Point lower_left;
    CYPDF_Point upper_right;
} CYPDF_Rect;

#define CYPDF_TO_RECT(x1, y1, x2, y2)       (CYPDF_Rect){ CYPDF_TO_POINT((x1), (y1)), CYPDF_TO_POINT((x2), (y2)) }


typedef void CYPDF_Object;


/* CYPDF function types */
typedef void (*CYPDF_FreeFunc)(void*);
typedef void (*CYPDF_PrintFunc)(CYPDF_Channel* const, const void* const);



#endif
