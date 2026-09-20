#include <stdio.h>
int gcd(int a, int b)
{
    int min, Gcd;
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
            Gcd = i;
            break;
        }
    }
    return Gcd;
}

int main()
{
    int a, b;
    printf("Enter two numbers:");
    scanf("%d %d", &a, &b);
    int lcm = (a * b) / gcd(a, b);
    printf("%d", lcm);
    return 0;
}