#include <stdio.h>
int Trailingzeros(int n)
{
    unsigned m = 1;
    int c = 0;
    for (int i = 0; i <= 31; i++)
    {
        if ((n & m) == 0)
        {
            c++;
        }
        if (n & m)
        {
            return c;
        }
        m = m << 1;
    }
    return 0;
}
int main()
{
    int n;
    scanf("%d", &n);
    int zero = Trailingzeros(n);
    printf("%d", zero);
    return 0;
}