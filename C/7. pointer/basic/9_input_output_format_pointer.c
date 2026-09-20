#include <stdio.h>
#define N 5
int main()
{
    int a[N];
    for (int i = 0; i < N; i++)
    {
        scanf("%d", a + i);
    }
    for (int i = 0; i < N; i++)
    {
        printf("%d ", *(a + i));
    }
    printf("\n");
    for (int *p = a; p < a + N; p++)
    {
        scanf("%d", p);
    }
    for (int *p = a; p < a + N; p++)
    {
        printf("%d ", *p);
    }
    return 0;
}