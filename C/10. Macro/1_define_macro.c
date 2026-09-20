#include <stdio.h>
#define pi 3.1416
#define MUL(a, b) a *b
#define MAX(x, y) ((x) > (y)) ? (x) : (y)
#define MIN(x, y) \
    int min;      \
    if (x > y)    \
        min = x;  \
    else          \
        min = y;
int main()
{
    int a = 2, b = 3;
    printf("mult is= %d\n", MUL(5 - 2, 7 + 4)); // ans= 5 - 2 * 7 + 4
    printf("Max is= %d\n", MAX(a, b));
    MIN(a, b);
    printf("Min is= %d", min);
    // #undef MAX
    // MAX(a, b);
    return 0;
}