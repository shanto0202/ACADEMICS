#include <stdio.h>
int main()
{
    int n;
    float p = 0;
    scanf("%d", &n);
    switch (n / 5000)
    {
    case 0:
        p = n - n * .05;
        break;
    case 1:
        p = n - 4999 * .05 - (n - 4999) * .1;
        break;
    case 2:
        p = n - 4999 * .05 - (n - 4999) * .1 - (n - 9999) * .2;
        break;
    }
    printf("%f", p);
    return 0;
}