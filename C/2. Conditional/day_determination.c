#include <stdio.h>
#include <math.h>
int main()
{
    int k, m, C, Y, W;
    scanf("%d %d %d", &k, &m, &Y);
    if (m == 1 || m == 2)
    {
        Y = Y - 1;
        C = Y / 100;
        Y = Y % 100;
    }
    else
    {
        C = Y / 100;
        Y = Y % 100;
    }
    if (m == 1)
        m = 11;
    else if (m == 2)
        m = 12;
    else
        m = m - 2;
    int i = k + floor(2.6 * m - .2) - 2 * C + Y + floor(Y / 4) + floor(C / 4);
    W = ((i % 7) + 7) % 7;
    if (W == 0)
        printf("Sunday");
    if (W == 1)
        printf("Monday");
    if (W == 2)
        printf("Tuesday");
    if (W == 3)
        printf("Wednesday");
    if (W == 4)
        printf("Thursday");
    if (W == 5)
        printf("Friday");
    if (W == 6)
        printf("Saturday");
    return 0;
}