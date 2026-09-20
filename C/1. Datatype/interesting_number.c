#include <stdio.h>
int main()
{
    int a, b, c, d, w, x, y, z;
    for (int i = 1000; i <= 9999; i++)
    {
        a = i/ 1000;
        b = (i / 100) % 10;
        c = (i % 100) / 10;
        d = i % 10;
        w = (a == 0) + (b == 0) + (c == 0) + (d == 0);
        x = (a == 1) + (b == 1) + (c == 1) + (d == 1);
        y = (a == 2) + (b == 2) + (c == 2) + (d == 2);
        z = (a == 3) + (b == 3) + (c == 3) + (d == 3);
        if (a == w && b == x && c == y && d == z)
        {
            printf("%d is such a number\n", i);
        }
    }
    return 0;
}