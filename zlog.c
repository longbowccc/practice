#include "zlog.h"
#include <time.h>
#include <stdio.h>

#define LOG_HDR_LEN 256

char loghdr[LOG_HDR_LEN];

void zflog(const char* fmt, const char* func, ...) {
    va_list vargs;
    time_t cur_time;
    struct tm t;
    time(&cur_time);
    localtime_r(&cur_time, &t);
    snprintf(loghdr, LOG_HDR_LEN, "%d-%02d-%02d %02d:%02d:%02d [%d] (%s) ",
        1900+t.tm_year, t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec,
        getpid(), func);
    printf(loghdr);

    va_start(vargs, func);
    vprintf(fmt, vargs);
    va_end(vargs);
}
