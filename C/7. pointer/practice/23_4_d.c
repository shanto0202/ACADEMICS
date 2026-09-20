#include <stdio.h>
int main()
{
    int a[10];
    int i;
    for (i = 0; i < 10; i++)
    {
        a[i] = i;
    }
    int *p;
    p = a + 5;
    for (i = 3; i < 8; i++)
        printf("\n%d", *(p + i));
    p = p - 3;
    for (i = 0; i < 10; i++)
    {
        printf("\n%d", *p);
        p++;
    }
    return 0;
}