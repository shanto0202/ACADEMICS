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
    for (int i = 0; i < n; i++)
    {
        int min = i;
        for (int j = i + 1; j < n - 1; j++)
        {
            if (a[j] < a[min])
            {
                min = j;
            }
        }
        int t = a[i];
        a[i] = a[min];
        a[min] = t;
    }
    int unique_sum = a[0];
    for (int i = 1; i < n; i++)
    {
        if (a[i] != a[i - 1])
        {
            unique_sum += a[i];
        }
    }
    printf("%d\n", unique_sum);
    return 0;
}