#include <stdio.h>
void print(int k)
{
    unsigned m = 1; // unsigned!!!
    m = m << 31;
    for (int i = 1; i <= 32; i++)
    {
        if (k & m)
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
        m = m >> 1;
        if (i % 4 == 0)
        {
            printf(" ");
        }
    }
}
int setBits(int x, int p, int n)
{
    int h;
    h = ~(~0 << n) << (p - n);
    return x|h;
}
int main()
{
    int x, p, n;
    scanf("%d %d %d", &x, &p, &n);
    print(x);
    printf("\n");
    print(setBits(x, p, n));
    return 0;
}