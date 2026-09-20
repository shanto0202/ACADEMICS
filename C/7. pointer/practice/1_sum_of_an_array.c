#include <stdio.h>
int main()
{
    int a[5] = {1, 2, 3, 4, 5};
    int *p = a;
    float s = 0;
    for (int i = 0; i < 5; i++)
    {
        s = s + *p;
        p++;
    }
    float mean = s / 5;
    printf("%g", mean);
    return 0;
}