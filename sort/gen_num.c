#include "zlog.h" 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int* gen_num(size_t n, int seed) {
    size_t size = n*sizeof(int);
    int *arr = malloc(size);
    if (!arr) {
        zlog("fail to allocate %d bytes", size);
        return (int*)0;
    }
    memset(arr, 0, size);
    size_t i = 0;
    if (seed == 0) {
        for (i=0;i<n;i++) {
            arr[i] = 10;
        }
    } else {
        srand(seed);
        for (i=0;i<n;i++) {
            arr[i] = rand()%100;
        }
    }
    return arr;
}

