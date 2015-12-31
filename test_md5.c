#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef unsigned char Uint8;

#include "zlog.h"
#include "zmd5.h"

void test_endian() {
    int a = 0x12345678;
    int *pa = &a;
    char *cpa = pa;

    printf("pa = %p, cpa = %p, cpa+1=%p, cpa+2=%p, cpa+3=%p\n", pa, cpa, cpa+1, cpa+2, cpa+3);
    printf("pa=%x\n*cpa=%x *cpa1=%x *cpa2=%x *cpa3=%x\n", *pa, *cpa, *(cpa+1), *(cpa+2), *(cpa+3));
    // its little endian, addr low->high with 78, 56, 34, 12
}

void test_bit() {
    unsigned int b = -0x001;
    unsigned int b1 = b<<1;
    unsigned int b2 = b>>2;
    printf("b=%x, b1=%x, b2=%x\n", b, b1, b2);
    // right shift, unsigned padding 0, signed pading 1
}

void test_math() {
    int i = 10;
    printf("Uint32 t[] = {\n");
    for (i=0;i<=65;i++) {
        int c = get_ti(i);
        printf("[%d] = 0x%08x,\n", i, c);
    }
}

char* to_hex(Uint8 *data, size_t len) {
    // 2 byte display for 1 byte data
    char *str = malloc(len*2+1);
    int i = 0;
    for (i=0;i<len;i++) {
        sprintf(str+i*2, "%02x", data[i]);
    }
    str[len*2] = '\0';
    return str;
}

void test_md5() {
}

int main(int argc, char* argv[]) {
    //zlog("HEEEL\n");
    //test_bit();
    //test_endian();
    //test_math();
    printf("argc=%d\n", argc);
    Uint8 sig[16] = {0};
    if (argc>1) {
        printf("argv[1] len=%d\n", strlen(argv[1]));
        z_md5(argv[1], strlen(argv[1]), sig);
    } else {
        printf("using input from stdin\n");
        size_t in_size = 512;
        char *inputs = malloc(in_size);
        if (!inputs) {
            zlog("fail to alloc %u bytes\n", in_size);
            exit(1);
        }
        int ch;
        int i = 0;
        while((ch=getchar()) != EOF) {
            inputs[i++] = ch;
            if (i>in_size) {
                in_size *= 2;
                inputs = realloc(inputs, in_size);
                if (!inputs) {
                    zlog("fail to alloc %u bytes\n", in_size);
                    exit(1);
                }
                zlog("realloced %u bytes\n", in_size);
            }
        }
        z_md5(inputs, i-1, sig);
        free(inputs);
    }
    char *str = to_hex(sig, 16);
    printf("result: %s\n", str);
    free(str);
    return 0;
}

