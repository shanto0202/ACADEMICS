#include <stdio.h>
int main()
{
    int n, i, c = 0;
    scanf("%d", &n);
    for (i = 1; i * i < n; i++)
    {
        if (n % i == 0)
        {
            c += 2;
        }
    }
    if (i * i == n)
    {
        c++;
    }
    printf("%d", c);
    return 0;
}