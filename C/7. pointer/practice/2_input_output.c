#include <stdio.h>
int main()
{
    int a = 4;
    int *p = &a;
    int **q = &p;
    int ***r = &q;
    **q = 6;
    printf("%i %i %i %i\n", a, *p, **q, ***r); // 6 6 6 6
    int var1 = 0, var2 = 1;
    int cons1 = 3, const2 = 3;
    int *box = &var1;
    printf("%i %p\n", *box, box);
    box = &var1;
    printf("%i %p\n", *box, box);
    *box = 10;
    printf("%i %p\n", *box, box);
    return 0;
}