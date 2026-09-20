#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    int dc = 0, ac = 0;
    for (int i = 0; i < n - 1; i++)
    {
        if (a[i + 1] >= a[i])
        {
            ac++;
        }
        if (a[i + 1] <= a[i])
        {
            dc++;
        }
    }
    if (ac == n - 1 && dc == n - 1)
    {
        printf("A D\n");
    }
    else if (ac == n - 1)
    {
        printf("A\n");
    }
    else if (dc == n - 1)
    {
        printf("D\n");
    }
    else
    {
        printf("U\n");
    }
}