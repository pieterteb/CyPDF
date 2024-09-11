#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cypdf_path_operators.h"
#include "cypdf_consts.h"
#include "cypdf_print.h"
#include "cypdf_stream.h"
#include "cypdf_utils.h"



CYPDF_Path* CYPDF_NewPath(enum CYPDF_PPO_TYPE ppo, enum CYPDF_CPO_TYPE cpo) {
    CYPDF_Path* path = CYPDF_scalloc(1, sizeof(CYPDF_Path));

    if (ppo >= CYPDF_PPO_COUNT) {
        ppo = CYPDF_PPO_STROKE;
    }
    if (cpo >= CYPDF_CPO_COUNT) {
        cpo = CYPDF_CPO_NONE;
    }
    path->ppo = ppo;
    path->cpo = cpo;

    return path;
}

static void CYPDF_PathAppend(CYPDF_Path* const path, const char pco[static 1], const enum CYPDF_PCO_TYPE type, const CYPDF_Point new_curr_point) {
    if (path) {
        size_t pco_len = strlen(pco);

        if (path->pco_count) {
            /* If the new pco is not the first of path, a new line sequence is inserted before the new pco. */
            path->path_str = CYPDF_srealloc(path->path_str, path->path_str_size + sizeof(CYPDF_NEW_LINE) - 1 + pco_len);
            CYPDF_sprintfNL(&path->path_str[path->path_str_size], NULL);
            path->path_str_size += sizeof(CYPDF_NEW_LINE) - 1;
        } else {
            path->path_str = CYPDF_smalloc(pco_len + 1);
        }

        strcpy(&path->path_str[path->path_str_size], pco);
        path->path_str_size += pco_len;
        ++path->pco_count;

        path->pco_types = CYPDF_srealloc(path->pco_types, path->pco_count * sizeof(enum CYPDF_PCO_TYPE));
        path->pco_types[path->pco_count - 1] = type;

        path->curr_point = new_curr_point;
    }
}

void CYPDF_PathAppendBegin(CYPDF_Path* const path, const CYPDF_Point start_point) {
    if (path) {
        char pco[CYPDF_PCO_SIZE] = { 0 };
        snprintf(pco, CYPDF_PCO_SIZE, "%g %g " CYPDF_PCOC_BEGIN, start_point.x, start_point.y);

        CYPDF_PathAppend(path, pco, CYPDF_PCO_BEGIN, start_point);
        path->curr_start_point = start_point;
    }
}

void CYPDF_PathAppendLineseg(CYPDF_Path* const path, const CYPDF_Point end_point) {
    if (path) {
        char pco[CYPDF_PCO_SIZE] = { 0 };
        snprintf(pco, CYPDF_PCO_SIZE, "%g %g " CYPDF_PCOC_LINESEG, end_point.x, end_point.y);

        CYPDF_PathAppend(path, pco, CYPDF_PCO_LINESEG, end_point);
    }
}

void CYPDF_PathAppendCBezier(CYPDF_Path* const path, const CYPDF_Point ctrl_point1, const CYPDF_Point ctrl_point2, const CYPDF_Point end_point) {
    if (path) {
        char pco[CYPDF_PCO_SIZE] = { 0 };
        snprintf(pco, CYPDF_PCO_SIZE, "%g %g %g %g %g %g " CYPDF_PCOC_CBEZIER, ctrl_point1.x, ctrl_point1.y, ctrl_point2.x, ctrl_point2.y, end_point.x, end_point.y);
        
        CYPDF_PathAppend(path, pco, CYPDF_PCO_CBEZIER, end_point);
    }
}

void CYPDF_PathAppendVBezier(CYPDF_Path* const path, const CYPDF_Point ctrl_point2, const CYPDF_Point end_point) {
    if (path) {
        char pco[CYPDF_PCO_SIZE] = { 0 };
        snprintf(pco, CYPDF_PCO_SIZE, "%g %g %g %g " CYPDF_PCOC_VBEZIER, ctrl_point2.x, ctrl_point2.y, end_point.x, end_point.y);

        CYPDF_PathAppend(path, pco, CYPDF_PCO_VBEZIER, end_point);
    }
}

void CYPDF_PathAppendYBezier(CYPDF_Path* const path, const CYPDF_Point ctrl_point1, const CYPDF_Point end_point) {
    if (path) {
        char pco[CYPDF_PCO_SIZE] = { 0 };
        snprintf(pco, CYPDF_PCO_SIZE, "%g %g %g %g " CYPDF_PCOC_YBEZIER, ctrl_point1.x, ctrl_point1.y, end_point.x, end_point.y);

        CYPDF_PathAppend(path, pco, CYPDF_PCO_YBEZIER, end_point);
    }
}

void CYPDF_PathAppendClose(CYPDF_Path* const path) {
    if (path) {
        CYPDF_PathAppend(path, CYPDF_PCOC_CLOSE, CYPDF_PCO_CLOSE, path->curr_start_point);
    }
}

void CYPDF_PathAppendRect(CYPDF_Path* const path, const CYPDF_Point ll_corner, const float width, const float height) {
    if (path) {
        char pco[CYPDF_PCO_SIZE] = { 0 };
        snprintf(pco, CYPDF_PCO_SIZE, "%g %g %g %g " CYPDF_PCOC_RECT, ll_corner.x, ll_corner.y, width, height);

        CYPDF_PathAppend(path, pco, CYPDF_PCO_RECT, ll_corner);
    }
}

void CYPDF_PrintPathToStream(CYPDF_ObjStream* const stream, const CYPDF_Path* const path) {
    if (path && stream) {
        CYPDF_PrintToStream(stream, path->path_str);

        switch (path->cpo)
        {
        case CYPDF_CPO_NWNRCLIP:
            CYPDF_PrintToStream(stream, " " CYPDF_CPOC_NWNRCLIP);
            break;
        case CYPDF_CPO_EORCLIP:
            CYPDF_PrintToStream(stream, " " CYPDF_CPOC_EORCLIP);
            break;
        default:
            break;
        }

        switch (path->ppo)
        {
        case CYPDF_PPO_STROKE:
            CYPDF_PrintToStream(stream, " " CYPDF_PPOC_STROKE);
            break;
        case CYPDF_PPO_CLOSE_STROKE:
            CYPDF_PrintToStream(stream, " " CYPDF_PPOC_CLOSE_STROKE);
            break;
        case CYPDF_PPO_NWNRFILL:
            CYPDF_PrintToStream(stream, " " CYPDF_PPOC_NWNRFILL);
            break;
        case CYPDF_PPO_EORFILL:
            CYPDF_PrintToStream(stream, " " CYPDF_PPOC_EORFILL);
            break;
        case CYPDF_PPO_NWNRFILL_STROKE:
            CYPDF_PrintToStream(stream, " " CYPDF_PPOC_NWNRFILL_STROKE);
            break;
        case CYPDF_PPO_EORFILL_STROKE:
            CYPDF_PrintToStream(stream, " " CYPDF_PPOC_EORFILL_STROKE);
            break;
        case CYPDF_PPO_CLOSE_NWNRFILL_STROKE:
            CYPDF_PrintToStream(stream, " " CYPDF_PPOC_CLOSE_NWNRFILL_STROKE);
            break;
        case CYPDF_PPO_CLOSE_EORFILL_STROKE:
            CYPDF_PrintToStream(stream, " " CYPDF_PPOC_CLOSE_EORFILL_STROKE);
            break;
        case CYPDF_PPO_END:
            CYPDF_PrintToStream(stream, " " CYPDF_PPOC_END);
            break;
        default:
            break;
        }
    }
}

void CYPDF_FreePath(CYPDF_Path* const path) {
    if (path) {
        free(path->path_str);
        free(path->pco_types);
        free(path);
    }
}
