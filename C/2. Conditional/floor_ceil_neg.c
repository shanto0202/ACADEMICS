#include <stdio.h>
int main()
{
    float a, b;
    scanf("%f", &a);
    b = (int)a;
    printf("ceil: %.0f\n", b);
    if (a != b)
    {
        float c = --b;
        printf("floor: %.0f\n", c);
    }
    else
    {
        printf("floor: %.0f\n", b);
    }
    b = a - .5;
    b = (int)b;
    printf("round %.0f", b);
    return 0;
}