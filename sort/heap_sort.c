
#include "zlog.h"
#include "heap_sort.h"

#define LEFT(i) ((i<<1)+1)
#define RIGHT(i) ((i<<1)+2)

/*
 * heap sort
 * stable: false
 * complexity: n*lg(n)
 */

void build_heap(int *arr, size_t len);
void heapify(int *arr, int top, int len);
void heap_to_sort(int *arr, size_t len);

static inline void swap(int *a1, int *a2) {
    int tmp = *a1;
    *a1 = *a2;
    *a2 = tmp;
}

int z_cmp(int *a1, int *a2) {
    if (*a1 == *a2) {
        return 0;
    }
    return *a1>*a2?1:-1;
}

void heap_sort(int *arr, size_t len) {
    build_heap(arr, len);
    heap_to_sort(arr, len);
}

/*
 * put the top element into the heap hierarchy
 */
void heapify(int *arr, int top, int len) {
    int left, right, max_c;
    while (1) {
        left = LEFT(top);
        if (left>=len) {
            break;
        }
        right = RIGHT(top);
        if (right<len) {
            max_c = z_cmp(&arr[left], &arr[right])==1 ? left : right;
        } else {
            max_c = left;
        }
        if (z_cmp(&arr[max_c], &arr[top])==1) {
            swap(&arr[max_c], &arr[top]);
            top = max_c;
        } else {
            break;
        }
    }
}

/* max heapify */
void build_heap(int *arr, size_t len) {
    int i, max_c;
    for (i=(len-1)/2;i>=0;i--) {
        heapify(arr, i, len);
    }
}

/*
 * sort
 */
void heap_to_sort(int *arr, size_t len) {
    int i,k,t;
    // take one element from top
    for (k=len-1;k>0;k--) {
        swap(&arr[0], &arr[k]);
        heapify(arr, 0, k);
    }
}

