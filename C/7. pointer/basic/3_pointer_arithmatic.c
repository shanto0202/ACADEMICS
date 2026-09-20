#include <stdio.h>
int main()
{
    int a[5];
    for (int i = 0; i < 5; i++)
    {
        scanf("%d", &a[i]);
    }
    int *p = a + 3;
    int *q = a;
    printf("%d %p", p - q, p);
    return 0;
}