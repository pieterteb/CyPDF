#include <math.h>
#include <stdio.h>
#ifdef __unix__
    #include <sys/stat.h>
#elif defined(_WIN64) || defined(_WIN32)
    #include <direct.h>
    #define mkdir(path, mode)   _mkdir(path)
#endif

#include "cypdf_consts.h"
#include "cypdf_doc.h"
#include "cypdf_operators.h"



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

void add_polygon(CYPDF_Doc* pdf, CYPDF_ObjPage* page, size_t n) {
    float centerx = CYPDF_A4_WIDTH / 2;
    float centery = CYPDF_A4_HEIGHT / 2;
    float radius = CYPDF_MM_TO_UU(100);

    CYPDF_Path* path = CYPDF_NewPath();
    CYPDF_PathAppendBegin(path, CYPDF_TO_POINT(centerx + radius, centery));
    for (size_t i = 1; i < n; ++i) {
        CYPDF_PathAppendLineseg(path, CYPDF_TO_POINT(centerx + radius * cos(2 * M_PI / (double)n * (double)i), centery + radius * sin(2 * M_PI / (double)n * (double)i)));
    }

    if (n == 5) {
        CYPDF_PathSetPaint(path, CYPDF_OPERATOR_PATH_CLOSE_NWNRFILL_STROKE);
    } else {
        CYPDF_PathSetPaint(path, CYPDF_OPERATOR_PATH_CLOSE_STROKE);
    }
    
    CYPDF_AddPathToPage(pdf, page, path);
    CYPDF_FreePath(path);
}


int main(void) {
    CYPDF_Doc* pdf = CYPDF_NewDoc();

    CYPDF_ObjPage* page1 = CYPDF_AppendPage(pdf);
    for (size_t i = 0; i < 10; ++i) {
        add_polygon(pdf, page1, i + 2);
    }

    /* Draws an approximation of a circle using two Bézier curves. */
    CYPDF_ObjPage* page2 = CYPDF_AppendPage(pdf);
    CYPDF_Path* path = CYPDF_NewPath();
    CYPDF_PathAppendBegin(path, CYPDF_TO_POINT(CYPDF_A4_WIDTH / 2 + CYPDF_MM_TO_UU(50), CYPDF_A4_HEIGHT / 2));
    CYPDF_PathAppendCBezier(path, CYPDF_TO_POINT(CYPDF_A4_WIDTH / 2 + CYPDF_MM_TO_UU(50), CYPDF_A4_HEIGHT / 2 + 4 * CYPDF_MM_TO_UU(50) / 3), CYPDF_TO_POINT(CYPDF_A4_WIDTH / 2 - CYPDF_MM_TO_UU(50), CYPDF_A4_HEIGHT / 2 + 4 * CYPDF_MM_TO_UU(50) / 3), CYPDF_TO_POINT(CYPDF_A4_WIDTH / 2 - CYPDF_MM_TO_UU(50), CYPDF_A4_HEIGHT / 2));
    CYPDF_PathAppendCBezier(path, CYPDF_TO_POINT(CYPDF_A4_WIDTH / 2 - CYPDF_MM_TO_UU(50), CYPDF_A4_HEIGHT / 2 - 4 * CYPDF_MM_TO_UU(50) / 3), CYPDF_TO_POINT(CYPDF_A4_WIDTH / 2 + CYPDF_MM_TO_UU(50), CYPDF_A4_HEIGHT / 2 - 4 * CYPDF_MM_TO_UU(50) / 3), CYPDF_TO_POINT(CYPDF_A4_WIDTH / 2 + CYPDF_MM_TO_UU(50), CYPDF_A4_HEIGHT / 2));
    CYPDF_PathSetPaint(path, CYPDF_OPERATOR_PATH_STROKE);
    CYPDF_AddPathToPage(pdf, page2, path);
    CYPDF_FreePath(path);

    mkdir("../out", 0700);

    CYPDF_PrintDoc(pdf, "../out/test.txt");
    CYPDF_FreeDoc(pdf);

    copy_file("../out/test.txt", "../out/test.pdf");

    return 0;
}
