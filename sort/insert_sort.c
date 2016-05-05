#include "zlog.h"
#include "insert_sort.h"

/*
 * insert sort: stable
 */

void insert_sort(int *arr, size_t len) {
    int i=0,j=0;
    int tmp;
    for (i=0;i<len-1;i++) {
        tmp = arr[i+1];
        for (j=i;j>=0;j--) {
            if (tmp < arr[j]) {
                arr[j+1] = arr[j];
            } else {
                arr[j+1] = tmp;
                break;
            }
        }
        if (j < 0) {
            arr[0] = tmp;
        }
    }
}
