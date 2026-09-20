#include <stdio.h>

int main()
{
    int a, b, min, gcd;
    printf("Enter two numbers:");
    scanf("%d %d", &a, &b);
    if (a < b)
    {
        min = a;
    }
    else
    {
        min = b;
    }
    for (int i = min; i >= 1; i--)
    {
        if (a % i == 0 && b % i == 0)
        {
            gcd = i;
            break;
        }
    }
    printf("gcd=%d", gcd);
    return 0;
}