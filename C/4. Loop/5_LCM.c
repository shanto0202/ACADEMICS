#include <stdio.h>
int main()
{
    int a, b, max, s = 1;
    scanf("%d %d", &a, &b);
    max = (a > b) ? a : b;
    int i = max;
    while (1)
    {
        if (i % a == 0 && i % b == 0)
        {
            s = i;
            break;
        }
        i++;
    }
    printf("%d", s);
    return 0;
}