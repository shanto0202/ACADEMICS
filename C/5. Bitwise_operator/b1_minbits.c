#include <stdio.h>
int Minbits(int n)
{
    unsigned m = 1;
    m = m << 31;
    for (int i = 0; i <= 31; i++)
    {
        if (n & m)
        {
            return 32 - i;
        }
        m = m >> 1;
    }
    return 0;
}
int main()
{
    int n;
    scanf("%d", &n);
    int min = Minbits(n);
    printf("%d", min);
    return 0;
}