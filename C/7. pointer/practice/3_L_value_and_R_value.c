#include <stdio.h>
int main()
{
    int v = 3, *p;
    scanf("%i", &v); //&v L-value
    p = &v;          // &v R-value
    printf("%i %p\n", *p, p);
    *p = 100;
    printf("%i %i\n", v, *p);
    return 0;
}