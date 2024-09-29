#ifndef CYPDF_GRAPHICS_H
#define CYPDF_GRAPHICS_H


#include <stddef.h>

#include "cypdf_memmgr.h"
#include "cypdf_operators.h"
#include "cypdf_print.h"
#include "cypdf_types.h"



typedef struct CYPDF_Path {
    CYPDF_Operator**    operators;
    size_t              operator_count;

    CYPDF_Point         current_point;
    CYPDF_Point         current_subpath_point;

    CYPDF_MemMgr*       memmgr;
} CYPDF_Path;


CYPDF_Path* CYPDF_NewPath(void);

void CYPDF_FreePath(CYPDF_Path* path);

void CYPDF_PrintPath(CYPDF_Channel* const restrict channel, const CYPDF_Path* const restrict path);


void CYPDF_PathAppendBegin(CYPDF_Path* const restrict path, const CYPDF_Point start_point);

void CYPDF_PathAppendLineseg(CYPDF_Path* const restrict path, const CYPDF_Point end_point);

void CYPDF_PathAppendCBezier(CYPDF_Path* const restrict path, const CYPDF_Point ctrl_point1, const CYPDF_Point ctrl_point2, const CYPDF_Point end_point);

void CYPDF_PathAppendVBezier(CYPDF_Path* const restrict path, const CYPDF_Point ctrl_point2, const CYPDF_Point end_point);

void CYPDF_PathAppendYBezier(CYPDF_Path* const restrict path, const CYPDF_Point ctrl_point1, const CYPDF_Point end_point);

void CYPDF_PathAppendClose(CYPDF_Path* const restrict path);

void CYPDF_PathAppendRect(CYPDF_Path* const restrict path, const CYPDF_Point lowleft_corner, const float width, const float height);

void CYPDF_PathSetClip(CYPDF_Path* const restrict path, const enum CYPDF_OPERATOR_TYPE clip_operator);

void CYPDF_PathSetPaint(CYPDF_Path* const restrict path, const enum CYPDF_OPERATOR_TYPE paint_operator);



#endif /* CYPDF_GRAPHICS_H */
