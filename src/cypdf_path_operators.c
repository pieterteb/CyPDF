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

static void CYPDF_PathAppend(CYPDF_Path* path, CYPDF_PCO pco, enum CYPDF_PCO_TYPE type, CYPDF_Point new_curr_point) {
    if (path) {       
        /* If the pco is not an empty string, it is appended to path->path_str. */
        if (pco[0]) {
            size_t pco_len = strlen(pco);

            if (path->pco_count) {
                /* If the new pco is not the first of path, a new line sequence is inserted before the new pco. */
                path->path_str = CYPDF_srealloc(path->path_str, (path->path_str_size + (sizeof(CYPDF_NEW_LINE) - 1) + pco_len) * sizeof(unsigned char));
                CYPDF_sprintfNL((char*)&path->path_str[path->path_str_size], NULL);
                path->path_str_size += sizeof(CYPDF_NEW_LINE) - 1;
            } else {
                path->path_str = CYPDF_srealloc(path->path_str, (path->path_str_size + pco_len) * sizeof(unsigned char));
            }

            memcpy(&path->path_str[path->path_str_size], pco, pco_len);
            path->path_str_size += pco_len;
            ++path->pco_count;

            path->pco_types = CYPDF_srealloc(path->pco_types, path->pco_count * sizeof(enum CYPDF_PCO_TYPE));
            path->pco_types[path->pco_count - 1] = type;

            path->curr_point = new_curr_point;
        }
    }
}

void CYPDF_PathAppendBegin(CYPDF_Path* path, CYPDF_Point start_point) {
    if (path) {
        CYPDF_PCO pco = CYPDF_scalloc(64, sizeof(char)); /* A buffer of 63 chars is enough unless one of the PCOC's becomes a lot lengthier. */
        sprintf(pco, "%g %g " CYPDF_PCOC_BEGIN, start_point.x, start_point.y);

        CYPDF_PathAppend(path, pco, CYPDF_PCO_BEGIN, start_point);
        path->curr_start_point = start_point;

        free(pco);
    }
}

void CYPDF_PathAppendLineseg(CYPDF_Path* path, CYPDF_Point end_point) {
    if (path) {
        CYPDF_PCO pco = CYPDF_scalloc(64, sizeof(char)); /* A buffer of 63 chars is enough unless one of the PCOC's becomes a lot lengthier. */
        sprintf(pco, "%g %g " CYPDF_PCOC_LINESEG, end_point.x, end_point.y);

        CYPDF_PathAppend(path, pco, CYPDF_PCO_LINESEG, end_point);

        free(pco);
    }
}

void CYPDF_PathAppendCBezier(CYPDF_Path* path, CYPDF_Point ctrl_point1, CYPDF_Point ctrl_point2, CYPDF_Point end_point) {
    if (path) {
        CYPDF_PCO pco = CYPDF_scalloc(64, sizeof(char)); /* A buffer of 63 chars is enough unless one of the PCOC's becomes a lot lengthier. */
        sprintf(pco, "%g %g %g %g %g %g " CYPDF_PCOC_CBEZIER, ctrl_point1.x, ctrl_point1.y, ctrl_point2.x, ctrl_point2.y, end_point.x, end_point.y);
        
        CYPDF_PathAppend(path, pco, CYPDF_PCO_CBEZIER, end_point);

        free(pco);
    }
}

void CYPDF_PathAppendVBezier(CYPDF_Path* path, CYPDF_Point ctrl_point2, CYPDF_Point end_point) {
    if (path) {
        CYPDF_PCO pco = CYPDF_scalloc(64, sizeof(char)); /* A buffer of 63 chars is enough unless one of the PCOC's becomes a lot lengthier. */
        sprintf(pco, "%g %g %g %g " CYPDF_PCOC_VBEZIER, ctrl_point2.x, ctrl_point2.y, end_point.x, end_point.y);

        CYPDF_PathAppend(path, pco, CYPDF_PCO_VBEZIER, end_point);

        free(pco);
    }
}

void CYPDF_PathAppendYBezier(CYPDF_Path* path, CYPDF_Point ctrl_point1, CYPDF_Point end_point) {
    if (path) {
        CYPDF_PCO pco = CYPDF_scalloc(64, sizeof(char)); /* A buffer of 63 chars is enough unless one of the PCOC's becomes a lot lengthier. */
        sprintf(pco, "%g %g %g %g " CYPDF_PCOC_YBEZIER, ctrl_point1.x, ctrl_point1.y, end_point.x, end_point.y);

        CYPDF_PathAppend(path, pco, CYPDF_PCO_YBEZIER, end_point);

        free(pco);
    }
}

void CYPDF_PathAppendClose(CYPDF_Path* path) {
    if (path) {
        CYPDF_PathAppend(path, CYPDF_PCOC_CLOSE, CYPDF_PCO_CLOSE, path->curr_start_point);
    }
}

void CYPDF_PathAppendRect(CYPDF_Path* path, CYPDF_Point ll_corner, float width, float height) {
    if (path) {
        CYPDF_PCO pco = CYPDF_scalloc(64, sizeof(char)); /* A buffer of 63 chars is enough unless one of the PCOC's becomes a lot lengthier. */
        sprintf(pco, "%g %g %g %g " CYPDF_PCOC_RECT, ll_corner.x, ll_corner.y, width, height);

        CYPDF_PathAppend(path, pco, CYPDF_PCO_RECT, ll_corner);

        free(pco);
    }
}

void CYPDF_PrintPathToStream(CYPDF_ObjStream* stream, CYPDF_Path* path) {
    if (path && stream) {
        char* cpo_ppo = CYPDF_scalloc(64, sizeof(char)); /* A buffer of 63 characters is enough unless one of the PCOC's becomes a lot lengthier. */
        switch (path->cpo)
        {
        case CYPDF_CPO_NWNRCLIP:
            sprintf(cpo_ppo, " " CYPDF_CPOC_NWNRCLIP);
            break;
        case CYPDF_CPO_EORCLIP:
            sprintf(cpo_ppo, " " CYPDF_CPOC_EORCLIP);
            break;
        default:
            break;
        }
        switch (path->ppo)
        {
        case CYPDF_PPO_STROKE:
            sprintf(cpo_ppo, " " CYPDF_PPOC_STROKE);
            break;
        case CYPDF_PPO_CLOSE_STROKE:
            sprintf(cpo_ppo, " " CYPDF_PPOC_CLOSE_STROKE);
            break;
        case CYPDF_PPO_NWNRFILL:
            sprintf(cpo_ppo, " " CYPDF_PPOC_NWNRFILL);
            break;
        case CYPDF_PPO_EORFILL:
            sprintf(cpo_ppo, " " CYPDF_PPOC_EORFILL);
            break;
        case CYPDF_PPO_NWNRFILL_STROKE:
            sprintf(cpo_ppo, " " CYPDF_PPOC_NWNRFILL_STROKE);
            break;
        case CYPDF_PPO_EORFILL_STROKE:
            sprintf(cpo_ppo, " " CYPDF_PPOC_EORFILL_STROKE);
            break;
        case CYPDF_PPO_CLOSE_NWNRFILL_STROKE:
            sprintf(cpo_ppo, " " CYPDF_PPOC_CLOSE_NWNRFILL_STROKE);
            break;
        case CYPDF_PPO_CLOSE_EORFILL_STROKE:
            sprintf(cpo_ppo, " " CYPDF_PPOC_CLOSE_EORFILL_STROKE);
            break;
        case CYPDF_PPO_END:
            sprintf(cpo_ppo, " " CYPDF_PPOC_END);
            break;
        default:
            break;
        }
        size_t cpo_ppo_len = strlen(cpo_ppo);

        /* If the cpo_ppo is not an empty string, it is appended to path->path_str. */
        if (cpo_ppo[0]) {
            path->path_str = CYPDF_srealloc(path->path_str, (path->path_str_size + cpo_ppo_len) * sizeof(unsigned char));
            memcpy(&path->path_str[path->path_str_size], cpo_ppo, cpo_ppo_len);
            path->path_str_size += cpo_ppo_len;
        }
        free(cpo_ppo);

        CYPDF_PrintToStream(stream, path->path_str, path->path_str_size);
    }
}

void CYPDF_FreePath(CYPDF_Path* path) {
    if (path) {
        free(path->path_str);
        free(path->pco_types);
        free(path);
    }
}
