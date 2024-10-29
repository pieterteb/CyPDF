#include <stdio.h>
#include <stdlib.h>

#include "cypdf_log.h"



void CYPDF_LogInit(void) {
    remove(CYPDF_TRACE_OUTPUT);
}

void CYPDF_LogTrace(const char trace_file[restrict static 1], const char func_location[restrict static 1], const size_t line, const char func_name[restrict static 1]) {
    FILE* fp = fopen(trace_file, "a");
    fprintf(fp, "%s\t\t%s:%zu\n", func_name, func_location, line);
    fclose(fp);
}
