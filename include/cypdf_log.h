#ifndef CYPDF_LOGGER_H
#define CYPDF_LOGGER_H


#include <stddef.h>

#include "cypdf.h"



#define CYPDF_LOG_OUTPUT    "../out/trace.txt"

#ifdef DEBUG
    #define CYPDF_TRACE     CYPDF_LogTrace((CYPDF_LOG_OUTPUT), (__FILE__), (__LINE__), (__func__))
#else
    #define CYPDF_TRACE
#endif


void CYPDF_LogInit(void);

void CYPDF_LogTrace(const char log_file[restrict static 1], const char func_location[restrict static 1], size_t line, const char func_name[restrict static 1]);



#endif /* CYPDF_LOGGER_H */