#include <stdio.h>
void print(int n)
{
    unsigned m = 1; // unsigned!!!
    m = m << 31;
    for (int i = 1; i <= 32; i++)
    {
        if (n & m)
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
int main()
{
    int n;
    scanf("%d", &n);
    print(n);
    printf("\n");
    unsigned y = n;
    print(y << 1 | (unsigned)n >> 31);
    return 0;
}