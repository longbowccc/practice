#include <stdarg.h>
#include <stdlib.h>


#ifndef _ZLOG_H
#define _ZLOG_H

void zflog(const char* fmt, const char* func, ...);


#define zlog(fmt, args...) zflog(fmt"\n", __FUNCTION__, ##args)

#define zlognn(fmt, args...) zflog(fmt, __FUNCTION__, ##args)

void zfarr_i(const int* arr, size_t n, const char*);

#define zarr_i(arr, n) zfarr_i(arr, n, __FUNCTION__)


#endif


