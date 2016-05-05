#include "zlog.h"
#include "merge_sort.h"
#include <memory.h>

/*
 * merge sort: stable
 */

void merge(int *arr, int *arr1, int len1, int *arr2, int len2);

void merge_sort(int *arr, size_t len) {
    if (len == 1) {
        return;
    }
    int mid = len/2;
    merge_sort(arr, mid);
    merge_sort(arr+mid, len-mid);
    int *tmp = malloc(sizeof(arr[0])*len);
    merge(tmp, arr, mid, arr+mid, len-mid);
    memcpy(arr, tmp, sizeof(arr[0])*len);
    free(tmp);
}

/*
 * merge two sorted array to dest
 */
void merge(int *arr, int *arr1, int len1, int *arr2, int len2) {
    int i=0, j=0, k=0;
    for (k=0;k<len1+len2;k++) {
        if (i<len1 && j<len2) {
            if (arr1[i]<arr2[j]) {
                arr[k] = arr1[i];
                i++;
            } else {
                arr[k] = arr2[j];
                j++;
            }
        } else if (i<len1) {
            arr[k] = arr1[i++];
        } else if (j<len2) {
            arr[k] = arr2[j++];
        }
    }
}

