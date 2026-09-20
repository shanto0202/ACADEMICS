#include <stdio.h>
int calculate(int c[], int n)
{
    int h = 0;
    for (int i = c[0]; i >= 0; i--)
    {
        int temp_h = 0;
        for (int j = 0; j < n; j++)
        {
            if (c[j] >= i)
            {
                temp_h++;
            }
        }
        if (temp_h > h && temp_h == i)
        {
            h = temp_h;
        }
    }
    return h;
}
int main()
{
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    printf("%d", calculate(a, n));
    return 0;
}