#include <stdio.h>
int allRepeated(int x)
{
    while (x)
    {
        if (((x % 10) ^ ((x / 10) % 10)))
        {
            return 0;
        }
        x /= 100;
    }
    return 1;
}
int main()
{
    int x;
    scanf("%d", &x);
    printf("%d\n", allRepeated(x));
    return 0;
}