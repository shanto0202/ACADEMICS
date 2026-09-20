#include <stdio.h>
int main()
{
    int n;
    scanf("%d", &n);
    int s = n % 10 + (n / 10) % 10 + (n / 100) % 10 + (n / 1000);
    printf("%d", s);
    return 0;
}