#include <stdarg.h>
#include <stdlib.h>


#ifndef _ZLOG_H
#define _ZLOG_H

void zflog(const char* fmt, const char* func, ...);


#define zlog(fmt, args...) zflog(fmt, __FUNCTION__, ##args)


#endif


