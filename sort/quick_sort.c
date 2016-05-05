#include "zlog.h"
#include "quick_sort.h"

/*
 * quick sort: unstable
 */

int partition(int* arr, int start, int end);

inline void swap(int* arr, int i, int j) {
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

void quick_sort(int* arr, size_t len) {
    if ((int)len<0) return;
    int m = partition(arr, 0, len);
    if (m>1) {
        quick_sort(arr, m);
    }
    if (m+1 < len) {
        quick_sort(arr+m+1, len-m-1);
    }
}

int partition(int* arr, int start, int end) {
    int mid, i, j, m;
    int sentinel;
    if (start >= end-1) {
        return start;
    }
    sentinel = arr[end-1];
    i = start;
    j = end-1;
    while (i<j) {
        while (i<j && arr[i]<sentinel) {
            i++;
        }
        // arr[i] >= sentinel
        while (j>i && arr[j]>=sentinel) {
            j--;
        }
        // j==i or arr[j]<sentinel
        swap(arr, i, j);
    }
    swap(arr, i, end-1);
    return i;
}

