#include "zlog.h"
#include "insert_sort.h"

static inline void swap(int *i, int *j) {
    int tmp = *i;
    *i = *j;
    *j = tmp;
}

void insert_sort(int *arr, size_t len) {
    int i=0,j=0;
    int min, idx_min;
    for (i=0;i<len;i++) {
        // find mininum
        idx_min = i;
        min = arr[i];
        for (j=i+1;j<len;j++) {
            if (arr[j] < min) {
                idx_min = j;
                min = arr[j];
            }
        }
        // swap mininum to first
        if (idx_min != i) {
            swap(&arr[i], &arr[idx_min]);
        }
    }
}
