#include <stdio.h>
int main()
{
    int n, a, b, c, d, m, sm;
    scanf("%d", &n);
    a = n / 1000;
    b = (n / 100) % 10;
    c = (n / 10) % 10;
    d = n % 10;
    if (a == b && b == c && c == d)
    {
        printf("-1 (No second largest)");
    }
    m = a;
    if (b > m)
        m = b;
    if (c > m)
        m = c;
    if (d > m)
        m = d;
    sm = -1;
    if (a < m)
        sm = a;
    if (b < m && b > sm)
        sm = b;
    if (c < m && c > sm)
        sm = c;
    if (d < m && d > sm)
        sm = d;
    printf("%d", sm);
    return 0;
}