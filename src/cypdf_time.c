#include <stdio.h>
#include <time.h>

#include "cypdf_memmgr.h"
#include "cypdf_time.h"



char* CYPDF_Date(void) {
    char* date = CYPDF_calloc(128, sizeof(char));
    time_t currtime = time(NULL);
    time_t UTC = mktime(gmtime(&currtime));
    struct tm* local = localtime(&currtime);

    char relationship = 'Z';
    int diff_seconds = (int)difftime(mktime(local), UTC);
    if (diff_seconds < 0) {
        relationship = '-';
    } else if (diff_seconds > 0) {
        relationship = '+';
    }
    int diff_hours = diff_seconds / 3600;
    int diff_minutes = (diff_seconds - diff_hours * 3600) / 60;

    sprintf(date, "D:%04d%02d%02d%02d%02d%02d%c%02d\'%02d\'", local->tm_year + 1900, local->tm_mon + 1, local->tm_mday, local->tm_hour, local->tm_min, local->tm_sec, relationship, diff_hours, diff_minutes);

    return date;
}
