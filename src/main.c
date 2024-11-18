#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef __unix__
    #include <sys/stat.h>
#elif defined(_WIN64) || defined(_WIN32)
    #include <direct.h>
    #define mkdir(path, mode)   _mkdir(path)
#endif

#include "cypdf.h"



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

// unsigned char* zlib_file_to_bytes(FILE* fp, size_t* size) {
//     fseek(fp, 0, SEEK_END);
//     *size = (size_t)ftell(fp) - 6;

//     fseek(fp, 2, SEEK_SET);

//     unsigned char* bytes = malloc(*size * sizeof(unsigned char));
//     fread(bytes, sizeof(unsigned char), *size, fp);

//     return bytes;
// }

void first_n_polygons(CYPDF_Doc* pdf, CYPDF_ObjPage* page, size_t n) {
    for (size_t i = 3; i < n + 3; ++i) {
        float centerx = CYPDF_A4_WIDTH / 2;
        float centery = CYPDF_A4_HEIGHT / 2;
        float radius = CYPDF_MM_TO_UU(100);

        CYPDF_Graphic* graphic = CYPDF_NewGraphic();
        CYPDF_GraphicBegin(graphic, CYPDF_TO_POINT(centerx + radius, centery));
        for (size_t j = 1; j < i; ++j) {
            CYPDF_GraphicLineseg(graphic, CYPDF_TO_POINT(centerx + radius * cos(2 * M_PI / (double)i * (double)j), centery + radius * sin(2 * M_PI / (double)i * (double)j)));
        }

        if (i == 5) {
            CYPDF_GraphicSave(graphic);
            CYPDF_GraphicFillRGB(graphic, (CYPDF_RGB){ 0.0, 1.0, 0.0 });
            CYPDF_GraphicPaint(graphic, CYPDF_OPERATOR_PATH_CLOSE_NWNRFILL_STROKE);
            CYPDF_GraphicRestore(graphic);
        } else {
            CYPDF_GraphicPaint(graphic, CYPDF_OPERATOR_PATH_CLOSE_STROKE);
        }
        
        CYPDF_DocAddGraphic(pdf, page, graphic);
    }
}

void bezier_circle(CYPDF_Doc* pdf, CYPDF_ObjPage* page) {
    CYPDF_Graphic* graphic = CYPDF_NewGraphic();

    CYPDF_GraphicBegin(graphic, CYPDF_TO_POINT(CYPDF_A4_WIDTH / 2 + CYPDF_MM_TO_UU(50), CYPDF_A4_HEIGHT / 2));
    CYPDF_GraphicCBezier(graphic, CYPDF_TO_POINT(CYPDF_A4_WIDTH / 2 + CYPDF_MM_TO_UU(50), CYPDF_A4_HEIGHT / 2 + 4 * CYPDF_MM_TO_UU(50) / 3), CYPDF_TO_POINT(CYPDF_A4_WIDTH / 2 - CYPDF_MM_TO_UU(50), CYPDF_A4_HEIGHT / 2 + 4 * CYPDF_MM_TO_UU(50) / 3), CYPDF_TO_POINT(CYPDF_A4_WIDTH / 2 - CYPDF_MM_TO_UU(50), CYPDF_A4_HEIGHT / 2));
    CYPDF_GraphicCBezier(graphic, CYPDF_TO_POINT(CYPDF_A4_WIDTH / 2 - CYPDF_MM_TO_UU(50), CYPDF_A4_HEIGHT / 2 - 4 * CYPDF_MM_TO_UU(50) / 3), CYPDF_TO_POINT(CYPDF_A4_WIDTH / 2 + CYPDF_MM_TO_UU(50), CYPDF_A4_HEIGHT / 2 - 4 * CYPDF_MM_TO_UU(50) / 3), CYPDF_TO_POINT(CYPDF_A4_WIDTH / 2 + CYPDF_MM_TO_UU(50), CYPDF_A4_HEIGHT / 2));
    CYPDF_GraphicPaint(graphic, CYPDF_OPERATOR_PATH_STROKE);

    CYPDF_DocAddGraphic(pdf, page, graphic);
}

void thick_v(CYPDF_Doc* pdf, CYPDF_ObjPage* page) {
    CYPDF_Graphic* graphic = CYPDF_NewGraphic();

    CYPDF_GraphicBegin(graphic, CYPDF_TO_POINT(0, CYPDF_A4_HEIGHT));
    CYPDF_GraphicLineseg(graphic, CYPDF_TO_POINT(CYPDF_A4_WIDTH / 2, CYPDF_MM_TO_UU(10)));
    CYPDF_GraphicLineseg(graphic, CYPDF_TO_POINT(CYPDF_A4_WIDTH, CYPDF_A4_HEIGHT));
    CYPDF_GraphicLineseg(graphic, CYPDF_TO_POINT(CYPDF_A4_WIDTH / 2, CYPDF_MM_TO_UU(10)));
    CYPDF_GraphicSave(graphic);
    CYPDF_GraphicLineWidth(graphic, 20.0);
    CYPDF_GraphicPaint(graphic, CYPDF_OPERATOR_PATH_CLOSE_STROKE);
    CYPDF_GraphicRestore(graphic);

    CYPDF_DocAddGraphic(pdf, page, graphic);
}


int main(void) {
    CYPDF_LogInit();

    CYPDF_Doc* pdf = CYPDF_NewDoc();

    CYPDF_ObjPage* page1 = CYPDF_AppendPage(pdf, CYPDF_A4_MEDIABOX);
    first_n_polygons(pdf, page1, 10);

    /* Draws an approximation of a circle using two Bézier curves. */
    CYPDF_ObjPage* page2 = CYPDF_AppendPage(pdf, CYPDF_A4_MEDIABOX);
    bezier_circle(pdf, page2);

    CYPDF_ObjPage* page3 = CYPDF_AppendPage(pdf, CYPDF_A4_MEDIABOX);
    thick_v(pdf, page3);

    mkdir("../out", 0700);

    CYPDF_PrintDoc(pdf, "../out/test.txt");
    CYPDF_FreeDoc(pdf);

    copy_file("../out/test.txt", "../out/test.pdf");

    return 0;
}
