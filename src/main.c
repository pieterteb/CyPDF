#include <math.h>
#include <stdio.h>

#include "cypdf_consts.h"
#include "cypdf_doc.h"


void copy_file(const char* source_path, const char* dest_path) {
    FILE* source = fopen(source_path, "r");
    FILE* dest = fopen(dest_path, "w");

    char ch = 0;
    while ((ch = (char)fgetc(source)) != EOF) {
        fputc(ch, dest);
    }

    fclose(source);
    fclose(dest);
}

void add_polygon(CYPDF_Doc* pdf, CYPDF_INT page_number, size_t n) {
    float centerx = CYPDF_A4_WIDTH / 2;
    float centery = CYPDF_A4_HEIGHT / 2;
    float radius = CYPDF_MM_TO_UU(100);

    CYPDF_Path* path = CYPDF_New_Path(CYPDF_PPO_STROKE);
    CYPDF_Path_Append_Begin(path, CYPDF_TO_POINT(centerx + radius, centery));
    for (size_t i = 1; i < n; ++i) {
        CYPDF_Path_Append_Lineseg(path, CYPDF_TO_POINT(centerx + radius * cos(2 * M_PI / (double)n * (double)i), centery + radius * sin(2 * M_PI / (double)n * (double)i)));
    }
    CYPDF_Path_Append_Close(path);
    
    CYPDF_Add_Path(pdf, page_number, path);
    CYPDF_Free_Path(path);
}


int main(void) {
    CYPDF_Doc* pdf = CYPDF_New_Doc();

    CYPDF_Append_Page(pdf);
    for (size_t i = 0; i < 10; ++i) {
        add_polygon(pdf, /*(CYPDF_INT)i*/ + 1, i + 3);
    }

    FILE* fp = fopen("../out/test.txt", "wb");
    CYPDF_Write_Doc(fp, pdf, "CyPDF/test.txt");
    fclose(fp);
    CYPDF_Free_Doc(pdf);

    copy_file("../out/test.txt", "../out/test.pdf");

    return 0;
}
