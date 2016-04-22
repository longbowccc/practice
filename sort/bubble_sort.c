#include "zlog.h"
#include "bubble_sort.h"

static inline void swap(int *i, int *j) {
    int tmp = *i;
    *i = *j;
    *j = tmp;
}

void bubble_sort(int *arr, size_t len) {
    int i=0,j=0;
    for (i=0;i<len;i++) {
        for (j=0;j<len-i-1;j++) {
            // swap larger to behind
            if (arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}
