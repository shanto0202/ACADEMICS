#include <stdio.h>

int main()
{
    int a, b, max;
    printf("Enter two numbers:");
    scanf("%d %d", &a, &b);
    if (a < b)
    {
        max = b;
    }
    else
    {
        max = a;
    }
    int i = max, lcm;
    while (1)
    {

        if (i % a == 0 && i % b == 0)
        {
            lcm = i;
            break;
        }
        i++;
    }
    printf("lcm=%d", lcm);
    return 0;
}