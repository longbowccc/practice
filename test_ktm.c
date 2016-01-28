#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef unsigned char Uint8;

#include "zlog.h"
#include "zmd5.h"

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

int main(int argc, char* argv[]) {
    return 0;
}

