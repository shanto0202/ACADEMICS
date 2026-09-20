#include <stdio.h>
int main()
{
    int x;
    float e = 1, e_1 = 2.718;
    scanf("%d", &x);
    for (int i = 1; i <= x; i++)
    {
        e = e * e_1;
    }
    e = 1 / e;
    printf("e^-x= %.4f", e);
    return 0;
}