
#include "zlog.h"
#include "bubble_sort.h"
#include "insert_sort.h"
#include "gen_num.h"


static const char* tests[]={"bubble"};

void test_sort();
int check_order(int*, size_t, int asc);


int main(int argc, char* args[]) {
    int seed=1;
    test_sort(10, 9);
    zlog(" ------ ");
    test_sort(10, 1);
    zlog(" ------ ");
    test_sort(10, 0);
    return 0;
}

void test_sort(size_t n, int seed) {
    zlog("test_sort(%d, %d) ====", n, seed);
    int *arr = NULL;
    arr = gen_num(n, seed);
    size_t i = 0;
    zarr_i(arr, n);
    //bubble_sort(arr, n);
    insert_sort(arr, n);
    zlog(">>>>>>>");
    zarr_i(arr, n);
    if (check_order(arr, n, 1)) {
        zlog("in order");
    } else {
        zlog("not in order");
    }
    free(arr);
}

/*
 * check the order of a array
 */
int check_order(int *arr, size_t n, int asc) {
    size_t i = 0;
    int in_order = 1;
    if (asc) {
        for (i=0;i<n-1;i++) {
            if (arr[i] > arr[i+1]) {
                in_order = 0;
                break;
            }
        }
    } else {
        for (i=0;i<n-1;i++) {
            if (arr[i] > arr[i+1]) {
                in_order = 0;
                break;
            }
        }
    }
    return in_order;
}
