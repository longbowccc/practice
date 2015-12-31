#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "zmd5.h"

typedef unsigned long long Uint64;
typedef unsigned int Uint32;
typedef unsigned char Uint8;

Uint64 A=0x67452301;
Uint64 B=0xefcdab89;
Uint64 C=0x98badcfe;
Uint64 D=0x10325476;

/*
 * t[i] = (1UL<<32)*fabs(sin(i+1));
 */
Uint32 t[] = {
    [0] = 0xd76aa478,
    [1] = 0xe8c7b756,
    [2] = 0x242070db,
    [3] = 0xc1bdceee,
    [4] = 0xf57c0faf,
    [5] = 0x4787c62a,
    [6] = 0xa8304613,
    [7] = 0xfd469501,
    [8] = 0x698098d8,
    [9] = 0x8b44f7af,
    [10] = 0xffff5bb1,
    [11] = 0x895cd7be,
    [12] = 0x6b901122,
    [13] = 0xfd987193,
    [14] = 0xa679438e,
    [15] = 0x49b40821,
    [16] = 0xf61e2562,
    [17] = 0xc040b340,
    [18] = 0x265e5a51,
    [19] = 0xe9b6c7aa,
    [20] = 0xd62f105d,
    [21] = 0x02441453,
    [22] = 0xd8a1e681,
    [23] = 0xe7d3fbc8,
    [24] = 0x21e1cde6,
    [25] = 0xc33707d6,
    [26] = 0xf4d50d87,
    [27] = 0x455a14ed,
    [28] = 0xa9e3e905,
    [29] = 0xfcefa3f8,
    [30] = 0x676f02d9,
    [31] = 0x8d2a4c8a,
    [32] = 0xfffa3942,
    [33] = 0x8771f681,
    [34] = 0x6d9d6122,
    [35] = 0xfde5380c,
    [36] = 0xa4beea44,
    [37] = 0x4bdecfa9,
    [38] = 0xf6bb4b60,
    [39] = 0xbebfbc70,
    [40] = 0x289b7ec6,
    [41] = 0xeaa127fa,
    [42] = 0xd4ef3085,
    [43] = 0x04881d05,
    [44] = 0xd9d4d039,
    [45] = 0xe6db99e5,
    [46] = 0x1fa27cf8,
    [47] = 0xc4ac5665,
    [48] = 0xf4292244,
    [49] = 0x432aff97,
    [50] = 0xab9423a7,
    [51] = 0xfc93a039,
    [52] = 0x655b59c3,
    [53] = 0x8f0ccc92,
    [54] = 0xffeff47d,
    [55] = 0x85845dd1,
    [56] = 0x6fa87e4f,
    [57] = 0xfe2ce6e0,
    [58] = 0xa3014314,
    [59] = 0x4e0811a1,
    [60] = 0xf7537e82,
    [61] = 0xbd3af235,
    [62] = 0x2ad7d2bb,
    [63] = 0xeb86d391,
};

Uint32 get_ti(int i) {
    return (1UL<<32)*fabs(sin(i+1));
}

inline Uint32 F(Uint32 X, Uint32 Y, Uint32 Z) {
    return (X&Y)|(~X&Z);
}

inline Uint32 G(Uint32 X, Uint32 Y, Uint32 Z) {
    return (X&Z)|(Y&(~Z));
}
inline Uint32 H(Uint32 X, Uint32 Y, Uint32 Z) {
    return X^Y^Z;
}
inline Uint32 I(Uint32 X, Uint32 Y, Uint32 Z) {
    return Y^(X|~Z);
}

// 循环左移
inline Uint32 rotate_left_shift(Uint32 a, Uint32 s) {
    return (a<<s)|(a>>(32-s));
}

inline void ff(Uint32 *a, Uint32 b, Uint32 c, Uint32 d, Uint32 Mj, Uint32 s, Uint32 ti) {
    *a = b + rotate_left_shift((*a + F(b, c, d) + Mj + ti), s);
}
inline void gg(Uint32 *a, Uint32 b, Uint32 c, Uint32 d, Uint32 Mj, Uint32 s, Uint32 ti) {
    *a = b + rotate_left_shift((*a + G(b, c, d) + Mj + ti), s);
}
inline void hh(Uint32 *a, Uint32 b, Uint32 c, Uint32 d, Uint32 Mj, Uint32 s, Uint32 ti) {
    *a = b + rotate_left_shift((*a + H(b, c, d) + Mj + ti), s);
}
inline void ii(Uint32 *a, Uint32 b, Uint32 c, Uint32 d, Uint32 Mj, Uint32 s, Uint32 ti) {
    *a = b + rotate_left_shift((*a + I(b, c, d) + Mj + ti), s);
}

#define FF(a, b, c, d, Mj, s, ti) ff(&a, b, c, d, Mj, s, ti)
#define GG(a, b, c, d, Mj, s, ti) gg(&a, b, c, d, Mj, s, ti)
#define HH(a, b, c, d, Mj, s, ti) hh(&a, b, c, d, Mj, s, ti)
#define II(a, b, c, d, Mj, s, ti) ii(&a, b, c, d, Mj, s, ti)

void z_md5(const char* content, Uint32 len, Uint8* result) {
    //Uint32 len = strlen(content);
    printf("len=%d\n", len);
    // 64 byte == 512 bit
    Uint32 remain = len%64;
    int n_block = len/64 + 1;
    if (remain >= 56) n_block++;    // 448/32=56 "=" is important
    Uint32 size = (n_block) * 64;
    Uint32 *m = malloc(size);
    if (!m) {
        return;
    }
    Uint8 *cp = m; 
    Uint32 n_int = n_block * 16;
    memset(cp, 0, size);
    memcpy(cp, content, len);
    cp[len] = 0x80;
    memset(cp+len+1, 0, size-len-1);
    m[n_int-2] = len * 8;
    int i;
    Uint32 a = A, b = B, c = C, d = D;
    for (i=0;i<n_block;i++) {
        mprocess(m+i*16, &a, &b, &c, &d);
    }
    // output
    Uint32 *pr = (Uint32*) result;
    pr[0] = a;
    pr[1] = b;
    pr[2] = c;
    pr[3] = d;

    free(m);
}

void mprocess(Uint32 *M, Uint32* pa, Uint32* pb, Uint32* pc, Uint32* pd) {
    Uint64 a = *pa, b = *pb, c = *pc, d = *pd;
    //传说中的对M[j]的第一轮循环
    FF(a,b,c,d,M[0],7,0xd76aa478);
    FF(d,a,b,c,M[1],12,0xe8c7b756);
    FF(c,d,a,b,M[2],17,0x242070db);
    FF(b,c,d,a,M[3],22,0xc1bdceee);
    FF(a,b,c,d,M[4],7,0xf57c0faf);
    FF(d,a,b,c,M[5],12,0x4787c62a);
    FF(c,d,a,b,M[6],17,0xa8304613);
    FF(b,c,d,a,M[7],22,0xfd469501);
    FF(a,b,c,d,M[8],7,0x698098d8);
    FF(d,a,b,c,M[9],12,0x8b44f7af);
    FF(c,d,a,b,M[10],17,0xffff5bb1);
    FF(b,c,d,a,M[11],22,0x895cd7be);
    FF(a,b,c,d,M[12],7,0x6b901122);
    FF(d,a,b,c,M[13],12,0xfd987193);
    FF(c,d,a,b,M[14],17,0xa679438e);
    FF(b,c,d,a,M[15],22,0x49b40821);

    //传说中对M[j]的第二轮循环
    GG(a,b,c,d,M[1],5,0xf61e2562);
    GG(d,a,b,c,M[6],9,0xc040b340);
    GG(c,d,a,b,M[11],14,0x265e5a51);
    GG(b,c,d,a,M[0],20,0xe9b6c7aa);
    GG(a,b,c,d,M[5],5,0xd62f105d);
    GG(d,a,b,c,M[10],9,0x02441453);
    GG(c,d,a,b,M[15],14,0xd8a1e681);
    GG(b,c,d,a,M[4],20,0xe7d3fbc8);
    GG(a,b,c,d,M[9],5,0x21e1cde6);
    GG(d,a,b,c,M[14],9,0xc33707d6);
    GG(c,d,a,b,M[3],14,0xf4d50d87);
    GG(b,c,d,a,M[8],20,0x455a14ed);
    GG(a,b,c,d,M[13],5,0xa9e3e905);
    GG(d,a,b,c,M[2],9,0xfcefa3f8);
    GG(c,d,a,b,M[7],14,0x676f02d9);
    GG(b,c,d,a,M[12],20,0x8d2a4c8a);

    //传说中对M[j]的第三轮循环
    HH(a,b,c,d,M[5],4,0xfffa3942);
    HH(d,a,b,c,M[8],11,0x8771f681);
    HH(c,d,a,b,M[11],16,0x6d9d6122);
    HH(b,c,d,a,M[14],23,0xfde5380c);
    HH(a,b,c,d,M[1],4,0xa4beea44);
    HH(d,a,b,c,M[4],11,0x4bdecfa9);
    HH(c,d,a,b,M[7],16,0xf6bb4b60);
    HH(b,c,d,a,M[10],23,0xbebfbc70);
    HH(a,b,c,d,M[13],4,0x289b7ec6);
    HH(d,a,b,c,M[0],11,0xeaa127fa);
    HH(c,d,a,b,M[3],16,0xd4ef3085);
    HH(b,c,d,a,M[6],23,0x04881d05);
    HH(a,b,c,d,M[9],4,0xd9d4d039);
    HH(d,a,b,c,M[12],11,0xe6db99e5);
    HH(c,d,a,b,M[15],16,0x1fa27cf8);
    HH(b,c,d,a,M[2],23,0xc4ac5665);

    //传说中对M[j]的第四轮循环
    II(a,b,c,d,M[0],6,0xf4292244);
    II(d,a,b,c,M[7],10,0x432aff97);
    II(c,d,a,b,M[14],15,0xab9423a7);
    II(b,c,d,a,M[5],21,0xfc93a039);
    II(a,b,c,d,M[12],6,0x655b59c3);
    II(d,a,b,c,M[3],10,0x8f0ccc92);
    II(c,d,a,b,M[10],15,0xffeff47d);
    II(b,c,d,a,M[1],21,0x85845dd1);
    II(a,b,c,d,M[8],6,0x6fa87e4f);
    II(d,a,b,c,M[15],10,0xfe2ce6e0);
    II(c,d,a,b,M[6],15,0xa3014314);
    II(b,c,d,a,M[13],21,0x4e0811a1);
    II(a,b,c,d,M[4],6,0xf7537e82);
    II(d,a,b,c,M[11],10,0xbd3af235);
    II(c,d,a,b,M[2],15,0x2ad7d2bb);
    II(b,c,d,a,M[9],21,0xeb86d391);

    *pa += a;
    *pb += b;
    *pc += c;
    *pd += d;
}

// end of file
