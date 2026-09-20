#include <stdio.h>

int main()
{
    int a[10];
    for (int i = 0; i < 10; i++)
        a[i] = i;
    int *p;
    p = a + 5;
    for (int i = 3; i < 8; i++)
    {
        printf("\n%d", *(p + i)); // last 3 values ar garbage value
    }
    p = p - 3;
    for (int i = 0; i < 10; i++)
    {
        printf("\n%d", *p); // last 2 values ar garbage value
        p++;
    }
    return 0;
}