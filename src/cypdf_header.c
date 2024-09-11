#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cypdf_header.h"
#include "cypdf_print.h"
#include "cypdf_utils.h"
#include "cypdf_version.h"


CYPDF_FileHeader* CYPDF_NewFileHeader() {
    CYPDF_FileHeader* file_header = CYPDF_smalloc(sizeof(CYPDF_FileHeader));
    if (file_header) {
        strcpy(file_header->version, CYPDF_PDF_VERSION);
        strcpy(file_header->hival_bytes, CYPDF_HIVAL_BYTES);
    }

    return file_header;
}

void CYPDF_PrintFileHeader(FILE* fp, CYPDF_FileHeader* file_header) {
    CYPDF_PrintComment(fp, file_header->version);
    CYPDF_PrintComment(fp, file_header->hival_bytes);
}

void CYPDF_FreeFileHeader(CYPDF_FileHeader* file_header) {
    if (file_header) {
        free(file_header);
    }
}
