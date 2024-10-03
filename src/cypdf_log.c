#include <stdio.h>

#include "cypdf_log.h"



void CYPDF_LogInit(void) {
    remove(CYPDF_LOG_OUTPUT);
}

void CYPDF_LogTrace(const char log_file[restrict static 1], const char func_location[restrict static 1], size_t line, const char func_name[restrict static 1]) {
    FILE* fp = fopen(log_file, "a");
    fprintf(fp, "In %s at line %zu: %s\n", func_location, line, func_name);
    fflush(fp);
    fclose(fp);
}
