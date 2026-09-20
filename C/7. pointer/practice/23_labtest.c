#include <stdio.h>
int main()
{
    int x, *y, *z, **w;
    x = 30;
    y = &x;
    z = &x;
    printf("%p %p\n", y, z);
    int a[5];
    for (int i = 0; i < 5; i++)
    {
        a[i] = 10 * i;
    }
    *(a + 1) += *y;
    *(a + 4) = *y;
    *y++ = *z--;
    printf("%d %p %p %p", x, y, z, w);
    printf("\n");
    for (int i = 0; i < 5; i++)
        printf("%d ", a[i]);
    printf("\n");
    return 0;
}