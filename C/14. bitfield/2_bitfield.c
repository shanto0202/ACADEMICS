#include <stdio.h>
#include <string.h>
struct
{
    unsigned int Member1;
    unsigned int Member2;
} d1;
struct
{
    unsigned int Member1 : 3;
    unsigned int Member2 : 1;
} d2;
struct
{
    unsigned int Member1 : 16;
    unsigned int Member2 : 17;
} d3;
int main()
{
    printf("Size of Regular Structure = %d\n", sizeof(d1));         // 8 bytes
    printf("Size of Structure with Bit Field 1: %d\n", sizeof(d2)); // 4 bytes
    printf("Size of Structure with Bit Field 2: %d\n", sizeof(d3)); // 4 bytes
    d1.Member1 = 8;
    d2.Member1 = 7; // if 8; overflow
    printf("%d %d\n", d1.Member1, d2.Member1);
}