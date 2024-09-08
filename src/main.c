#include <stdio.h>

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


int main(void) {
    CYPDF_Doc* pdf = CYPDF_New_Doc();

    for (size_t i = 0; i < 1; ++i) {
        CYPDF_Append_Page(pdf);
    }

    FILE* fp = fopen("../out/test.txt", "wb");
    CYPDF_Write_Doc(fp, pdf, "CyPDF/test.txt");
    fclose(fp);
    CYPDF_Free_Doc(pdf);

    copy_file("../out/test.txt", "../out/test.pdf");

    return 0;
}
