#include <stdio.h>
#include <stdlib.h>

#include "cypdf_graphics.h"
#include "cypdf_print.h"
#include "cypdf_utils.h"



CYPDF_PCO* CYPDF_PCO_New(enum CYPDF_PCO_TYPE operator, CYPDF_Point endpoint,  CYPDF_Point operand1,  CYPDF_Point operand2) {
    CYPDF_PCO* pco = CYPDF_smalloc(sizeof(CYPDF_PCO));

    pco->operator = operator;
    pco->endpoint = endpoint;
    pco->operand1 = operand1;
    pco->operand2 = operand2;

    return pco;
}

CYPDF_Path* CYPDF_Path_New(CYPDF_PCO** pcos, CYPDF_SIZE pco_count) {
    CYPDF_Path* path = CYPDF_smalloc(sizeof(CYPDF_Path));

    if (pco_count) {
        path->pcos = pcos;
    } else {
        path->pcos = NULL;
    }
    path->pco_count = pco_count;

    return path;
}

static void CYPDF_PCO_Print(FILE* fp, CYPDF_PCO* pco) {
    if (pco) {
        switch (pco->operator)
        {
        case CYPDF_PCO_NEW:
            fprintf(fp, "%f %f m", pco->endpoint.x, pco->endpoint.y);
            break;
        case CYPDF_PCO_LINESEG:
            fprintf(fp, "%f %f l", pco->endpoint.x, pco->endpoint.y);
            break;
        case CYPDF_PCO_CBEZIER:
            fprintf(fp, "%f %f %f %f %f %f c", pco->operand1.x, pco->operand1.y, pco->operand2.x, pco->operand2.y, pco->endpoint.x, pco->endpoint.y);
            break;
        case CYPDF_PCO_VBEZIER:
            fprintf(fp, "%f %f %f %f v", pco->operand2.x, pco->operand2.y, pco->endpoint.x, pco->endpoint.y);
            break;
        case CYPDF_PCO_YBEZIER:
            fprintf(fp, "%f %f %f %f y", pco->operand1.x, pco->operand1.y, pco->endpoint.x, pco->endpoint.y);
            break;
        case CYPDF_PCO_CLOSE:
            fputc('h', fp);
            break;
        case CYPDF_PCO_RECT:
            fprintf(fp, "%f %f %f %f re", pco->endpoint.x, pco->endpoint.y, pco->operand1.x, pco->operand1.y);
            break;
        default:
            break;
        }
    }
}

void CYPDF_Path_Print(FILE* fp, CYPDF_Path* path) {
    if (path) {
        for (size_t i = 0; i < path->pco_count; ++i) {
            CYPDF_PCO_Print(fp, path->pcos[i]);
            CYPDF_Write_NL(fp);
        }
    }
}

void CYPDF_Path_Append(CYPDF_Path* path, CYPDF_PCO* pco) {
    if (path) {
        if (!pco) {
            return;
        }

        ++path->pco_count;
        path->pcos = CYPDF_srealloc(path->pcos, path->pco_count * sizeof(CYPDF_PCO));
        path->pcos[path->pco_count - 1] = pco;
    }
}

void CYPDF_Path_Free(CYPDF_Path* path) {
    if (path) {
        for (size_t i = 0; i < path->pco_count; ++i) {
            free(path->pcos[i]);
        }
        free(path->pcos);
        free(path);
    }
}
