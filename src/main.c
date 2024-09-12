#include <math.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "cypdf_consts.h"
#include "cypdf_doc.h"



void copy_file(const char* source_path, const char* dest_path) {
    FILE* source = fopen(source_path, "r");
    FILE* dest = fopen(dest_path, "w");

    char ch = 0;
    while ((ch = (char)fgetc(source)) != (char)EOF) {
        fputc(ch, dest);
    }

    fclose(source);
    fclose(dest);
}

void add_polygon(CYPDF_Doc* pdf, int page_number, size_t n) {
    float centerx = CYPDF_A4_WIDTH / 2;
    float centery = CYPDF_A4_HEIGHT / 2;
    float radius = CYPDF_MM_TO_UU(100);

    CYPDF_Path* path = CYPDF_NewPath(CYPDF_PPO_STROKE, CYPDF_CPO_NONE);
    CYPDF_PathAppendBegin(path, CYPDF_TO_POINT(centerx + radius, centery));
    for (size_t i = 1; i < n; ++i) {
        CYPDF_PathAppendLineseg(path, CYPDF_TO_POINT(centerx + radius * cos(2 * M_PI / (double)n * (double)i), centery + radius * sin(2 * M_PI / (double)n * (double)i)));
    }
    CYPDF_PathAppendClose(path);
    
    CYPDF_AddPath(pdf, page_number, path);
    CYPDF_FreePath(path);
}


int main(void) {
    CYPDF_Doc* pdf = CYPDF_NewDoc();

    CYPDF_AppendPage(pdf);
    for (size_t i = 0; i < 10; ++i) {
        add_polygon(pdf, 1, i + 3);
    }

    /* Draws an approximation of a circle using two Bézier curves. */
    CYPDF_AppendPage(pdf);
    CYPDF_Path* path = CYPDF_NewPath(CYPDF_PPO_STROKE, CYPDF_CPO_NONE);
    CYPDF_PathAppendBegin(path, CYPDF_TO_POINT(CYPDF_A4_WIDTH / 2 + CYPDF_MM_TO_UU(50), CYPDF_A4_HEIGHT / 2));
    CYPDF_PathAppendCBezier(path, CYPDF_TO_POINT(CYPDF_A4_WIDTH / 2 + CYPDF_MM_TO_UU(50), CYPDF_A4_HEIGHT / 2 + 4 * CYPDF_MM_TO_UU(50) / 3), CYPDF_TO_POINT(CYPDF_A4_WIDTH / 2 - CYPDF_MM_TO_UU(50), CYPDF_A4_HEIGHT / 2 + 4 * CYPDF_MM_TO_UU(50) / 3), CYPDF_TO_POINT(CYPDF_A4_WIDTH / 2 - CYPDF_MM_TO_UU(50), CYPDF_A4_HEIGHT / 2));
    CYPDF_PathAppendCBezier(path, CYPDF_TO_POINT(CYPDF_A4_WIDTH / 2 - CYPDF_MM_TO_UU(50), CYPDF_A4_HEIGHT / 2 - 4 * CYPDF_MM_TO_UU(50) / 3), CYPDF_TO_POINT(CYPDF_A4_WIDTH / 2 + CYPDF_MM_TO_UU(50), CYPDF_A4_HEIGHT / 2 - 4 * CYPDF_MM_TO_UU(50) / 3), CYPDF_TO_POINT(CYPDF_A4_WIDTH / 2 + CYPDF_MM_TO_UU(50), CYPDF_A4_HEIGHT / 2));
    CYPDF_AddPath(pdf, 2, path);
    CYPDF_FreePath(path);

    mkdir("../out", 0700);

    FILE* fp = fopen("../out/test.txt", "wb");
    CYPDF_PrintDoc(fp, pdf, "CyPDF/test.txt");
    fclose(fp);
    CYPDF_FreeDoc(pdf);

    copy_file("../out/test.txt", "../out/test.pdf");

    return 0;
}
