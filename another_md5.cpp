
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <stdio.h>

using namespace std;
#define SingleOneBit 0x80
#define BlockSize 512
#define ModSize 448 //余数值
#define LengthSize 64
#define Bits 8
// MD5 Chaining Variable 四个链接变量
#define A 0x67452301UL
#define B 0xEFCDAB89UL
#define C 0x98BADCFEUL
#define D 0x10325476UL
// Creating own types
#ifdef Uint64
# undef Uint64 //删除原有定义
#endif
#ifdef Uint32
# undef Uint32
#endif
typedef unsigned long long Uint64;
typedef unsigned int Uint32;
typedef unsigned char Uint8;

typedef struct
{
 char *message;
 Uint64 length;
}String;
const Uint32 X[4][2] = {{0, 1}, {1, 5}, {5, 3}, {0, 7}};
const Uint32 S[4][4] = {{ 7, 12, 17, 22 },{ 5, 9, 14, 20 },{ 4, 11, 16, 23 },{ 6, 10, 15, 21 }};
//四个非线性函数 
Uint32 F(Uint32 x,Uint32 y,Uint32 z)
{
 return (x&y)|(~x&z);
}

Uint32 G(Uint32 x,Uint32 y,Uint32 z)
{
 return (x&z)|(y & ~z);
}
Uint32 H(Uint32 x,Uint32 y,Uint32 z)
{
 return x^y^z;
}
Uint32 I(Uint32 x,Uint32 y,Uint32 z)
{
 return y^( x| ~z);
}

Uint32 rotateLeft(Uint32 x,Uint32 s)
{
 return (x<<s) | (x>>(32 -s));
}
Uint32 countPaddingBits(Uint32 length)
{
 Uint32 div = length * Bits/BlockSize;
 Uint32 mod = length * Bits % BlockSize;
 Uint32 cBits;
 if(mod ==0)
 {
  cBits = ModSize;
 }
 else 
 {
  cBits = (ModSize + BlockSize - mod) % BlockSize;
 }
 return cBits/Bits;
}
String appendPaddingBits(char *str)
{
 Uint32 len= strlen(str);
 Uint32 bitLength = countPaddingBits(len);
 Uint64 appLength = len * Bits;
 String strs;
 strs.message =(char *)malloc(len + bitLength + LengthSize/Bits);
 strncpy(strs.message,str,len);
 memset(strs.message + len,0,bitLength);
 strs.message[len] = SingleOneBit;
 memmove(strs.message +len + bitLength,(char *) &appLength,sizeof(Uint64));  // cause wrong calcu if bitLength==0
 strs.length = len + bitLength + sizeof(Uint64);
 Uint32 *p = (Uint32*)strs.message;
printf("len=%d, bitLength=%d, appLength=%d, strs.length=%d\n", len, bitLength, appLength,strs.length);
 int i=0;
 for (i=0;i<strs.length/4;i++) {
    printf("%08x ", p[i]);
 }
 printf("\n");
 return strs;
}
int main(int argc,char *argv[])
{
 String str;
 Uint32 w[16];
 Uint32 chain[4];
 Uint32 state[4];
 Uint8 r[16];
 Uint32 (*auxi[4])(Uint32,Uint32,Uint32) = {F,G,H,I};//这种用法跟QSORT中的CMP一样
 int roundIndex, argIndex,sIndex,wIndex,i,j;
 if (argc <2)
 {
  cout<<"Sorry:You input error"<<endl;
  return 0;
 }
 for(argIndex = 1;argIndex <argc;argIndex++)
 {
  str = appendPaddingBits(argv[argIndex]);
  chain[0] = A;
  chain[1] = B;
  chain[2] = C;
  chain[3] = D;
  for(j = 0;j<str.length;j+=BlockSize/Bits)
  {
   memmove((char *)w,str.message +j,BlockSize/Bits);
   memmove(state,chain,sizeof(chain));
   for(roundIndex = 0;roundIndex <4;roundIndex++)
   {
    wIndex = X[roundIndex][0];
    sIndex = 0;
    for(i=0;i<16;i++)
    {
     Uint32 ti = (Uint32)floor((1ULL<<32)*fabs(sin((double)(roundIndex*16 + i +1))));
     Uint32 s = S[roundIndex][i%4];
     Uint32 fx = (*auxi[roundIndex])( state[(sIndex+1)%4], state[(sIndex+2)%4], state[(sIndex+3)%4]);
     //printf("F(%08x, %08x, %08x) =%08x\n", state[(sIndex+1)%4], state[(sIndex+2)%4], state[(sIndex+3)%4], fx);
     Uint32 rl = state[sIndex] + fx + w[wIndex] + ti;
     //printf("%08x + %08x + %08x + %08x =%08x\n", state[sIndex], fx, w[wIndex], ti, rl);
     Uint32 rlr = rotateLeft(state[sIndex] + fx + w[wIndex] + ti, s);
     //printf("%2d, %2d:  %x, %x, %x, %x ti=%08x s=%d fx=%08x rl=%08x rlr=%08x\n", roundIndex, i, state[0], state[1], state[2], state[3], ti, s, fx, rl, rlr);
     state[sIndex] = state[(sIndex +1)%4]+rotateLeft(state[sIndex] + fx + w[wIndex] + ti, s);
     //printf("%08x:  %x, %x, %x, %x\n", w[wIndex], state[0], state[1], state[2], state[3]);
     sIndex = (sIndex +3) %4;
     wIndex = (wIndex + X[roundIndex][1])& 0xF;
    }
    //printf("%02d:  %08x, %08x, %08x, %08x\n", roundIndex, state[0], state[1], state[2], state[3]);
   }
   chain[0] += state[0];
   chain[1] += state[1];
   chain[2] += state[2];
   chain[3] += state[3];
   printf("%x, %x, %x, %x\n", chain[0], chain[1], chain[2], chain[3]);
  }
  memmove(r+0,(char *)&chain[0],sizeof(Uint32));
  memmove(r+4,(char *)&chain[1],sizeof(Uint32));
  memmove(r+8,(char *)&chain[2],sizeof(Uint32));
  memmove(r+12,(char *)&chain[3],sizeof(Uint32));
  for(i = 0;i<16;i++)
  {
   printf("%02x", r[i]);
  }
  putchar('\n');
  free(str.message);
 }
 return 0;
}
