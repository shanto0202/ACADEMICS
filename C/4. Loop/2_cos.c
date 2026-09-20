#include <stdio.h>
#include <math.h>
int main()
{
    float y, x, s = 1, t = 1;
    int n;
    scanf("%f %d", &x, &n);
    x = (x * 22) / (180 * 7);
    for (int i = 1; i < n; i++)
    {
        y = (-x * x) / (2 * i * (2 * i - 1));
        t = t * y;
        s = s + t;
    }
    printf("%f", s);
    return 0;
}