#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cypdf_graphics.h"
#include "cypdf_consts.h"
#include "cypdf_print.h"
#include "cypdf_stream.h"
#include "cypdf_utils.h"



CYPDF_Path* CYPDF_New_Path(enum CYPDF_PPO_TYPE ppo) {
    CYPDF_Path* path = CYPDF_scalloc(1, sizeof(CYPDF_Path));

    if (ppo >= CYPDF_PPO_COUNT) {
        ppo = CYPDF_PPO_UNKNOWN;
    }
    path->ppo = ppo;

    return path;
}

void CYPDF_Path_Append(CYPDF_Path* path, enum CYPDF_PCO_TYPE operator, CYPDF_Point endpoint, CYPDF_Point point1, CYPDF_Point point2) {
    if (path) {
        CYPDF_PCO pco = CYPDF_scalloc(128, sizeof(char)); /* A buffer of 127 characters is enough unless one of the PCOC's becomes a lot lengthier. */
        switch (operator)
        {
        case CYPDF_PCO_NEW:
            sprintf(pco, "%g %g " CYPDF_PCOC_NEW, endpoint.x, endpoint.y);
            break;
        case CYPDF_PCO_LINESEG:
            sprintf(pco, "%g %g " CYPDF_PCOC_LINESEG, endpoint.x, endpoint.y);
            break;
        case CYPDF_PCO_CBEZIER:
            sprintf(pco, "%g %g %g %g %g %g " CYPDF_PCOC_YBEZIER, point1.x, point1.y, point2.x, point2.y, endpoint.x, endpoint.y);
            break;
        case CYPDF_PCO_VBEZIER:
            sprintf(pco, "%g %g %g %g " CYPDF_PCOC_VBEZIER, point2.x, point2.y, endpoint.x, endpoint.y);
            break;
        case CYPDF_PCO_YBEZIER:
            sprintf(pco, "%g %g %g %g " CYPDF_PCOC_YBEZIER, point1.x, point1.y, endpoint.x, endpoint.y);
            break;
        case CYPDF_PCO_CLOSE:
            sprintf(pco, CYPDF_PCOC_CLOSE);
            break;
        case CYPDF_PCO_RECT:
            sprintf(pco, "%g %g %g %g " CYPDF_PCOC_RECT, endpoint.x, endpoint.y, point1.x, point1.y);
            break;
        default:
            break;
        }
        CYPDF_SIZE pco_len = strlen(pco);
        
        /* If the pco is not an empty string, it is appended to path->path_str. */
        if (pco[0]) {
            if (path->pco_count) {
                /* If the new pco is not the first of path, a new line sequence is inserted before the new pco. */
                path->path_str = CYPDF_srealloc(path->path_str, (path->path_str_size + sizeof(CYPDF_NEW_LINE) + pco_len) * sizeof(CYPDF_BYTE));
                path->path_str_size += (CYPDF_SIZE)CYPDF_sprintf_NL((char*)&path->path_str[path->path_str_size], NULL);
            } else {
                path->path_str = CYPDF_srealloc(path->path_str, (path->path_str_size + pco_len) * sizeof(CYPDF_BYTE));
            }
            memcpy(&path->path_str[path->path_str_size], pco, pco_len);
            path->path_str_size += pco_len;
            ++path->pco_count;
        }
        free(pco);
    }
}

void CYPDF_Write_Path_To_Stream(CYPDF_Obj_Stream* stream, CYPDF_Path* path) {
    if (path && stream) {
        char* ppo = CYPDF_scalloc(128, sizeof(char)); /* A buffer of 127 characters is enough unless one of the PCOC's becomes a lot lengthier. */
        switch (path->ppo)
        {
        case CYPDF_PPO_STROKE:
            sprintf(ppo, " " CYPDF_PPOC_STROKE);
            break;
        case CYPDF_PPO_CLOSE_STROKE:
            sprintf(ppo, " " CYPDF_PPOC_CLOSE_STROKE);
            break;
        case CYPDF_PPO_NWNRFILL:
            sprintf(ppo, " " CYPDF_PPOC_NWNRFILL);
            break;
        case CYPDF_PPO_EORFILL:
            sprintf(ppo, " " CYPDF_PPOC_EORFILL);
            break;
        case CYPDF_PPO_NWNRFILL_STROKE:
            sprintf(ppo, " " CYPDF_PPOC_NWNRFILL_STROKE);
            break;
        case CYPDF_PPO_EORFILL_STROKE:
            sprintf(ppo, " " CYPDF_PPOC_EORFILL_STROKE);
            break;
        case CYPDF_PPO_CLOSE_NWNRFILL_STROKE:
            sprintf(ppo, " " CYPDF_PPOC_CLOSE_NWNRFILL_STROKE);
            break;
        case CYPDF_PPO_CLOSE_EORFILL_STROKE:
            sprintf(ppo, " " CYPDF_PPOC_CLOSE_EORFILL_STROKE);
            break;
        case CYPDF_PPO_END:
            sprintf(ppo, " " CYPDF_PPOC_END);
            break;
        default:
            break;
        }
        CYPDF_SIZE ppo_len = strlen(ppo);

        /* If the ppo is not an empty string, it is appended to path->path_str. */
        if (ppo[0]) {
            path->path_str = CYPDF_srealloc(path->path_str, (path->path_str_size + ppo_len) * sizeof(CYPDF_BYTE));
            memcpy(&path->path_str[path->path_str_size], ppo, ppo_len);
            path->path_str_size += ppo_len;
        }
        free(ppo);

        CYPDF_Write_To_Stream(stream, path->path_str, path->path_str_size);
    }
}

void CYPDF_Free_Path(CYPDF_Path* path) {
    if (path) {
        free(path->path_str);
        free(path);
    }
}
