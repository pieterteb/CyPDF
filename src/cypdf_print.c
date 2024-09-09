#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "cypdf_print.h"
#include "cypdf_consts.h"
#include "cypdf_types.h"
#include "cypdf_utils.h"



size_t CYPDF_fwrite_NL(const void* buffer, size_t element_size, size_t element_count, FILE* stream) {
    size_t ret = fwrite(buffer, element_size, element_count, stream) * element_size;
    ret += CYPDF_Write_NL(stream);

    return ret;
}

size_t CYPDF_Write_NL(FILE* fp) {
    return fwrite(CYPDF_NEW_LINE, sizeof(char), strlen(CYPDF_NEW_LINE), fp) * sizeof(char);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
int CYPDF_fprintf_NL(FILE* fp, const char* format, ...) {
    int char_count = 0;
    if (format) {
        va_list args;
        va_start(args, format);
        char_count += vfprintf(fp, format, args);
        va_end(args);
    }

    char_count += (int)CYPDF_Write_NL(fp);

    return char_count;
}

int CYPDF_sprintf_NL(char* dest, const char* format, ...) {
    int char_count = 0;
    if (format) {
        va_list args;
        va_start(args, format);
        char_count += vsprintf(dest, format, args);
        va_end(args);
    }

    char_count += sprintf(dest, "%s", CYPDF_NEW_LINE);

    return char_count;
}
#pragma GCC diagnostic pop

size_t CYPDF_Write_Comment(FILE* fp, const char* src) {
    size_t ret = 0;

    if (fputc('%', fp) != EOF) {
        ret = 1;
    }
    ret += CYPDF_fwrite_NL(src, sizeof(src[0]), strlen(src), fp);

    return ret;
}
