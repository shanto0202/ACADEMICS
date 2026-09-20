#include <stdio.h>
int main()
{
    char c;
    int x, n, y, p;
    scanf("%c %d", &c, &x);
    n = ((c - 65 + 26 - (x % 26)) % 26) + 65;
    printf("%c", n);
    return 0;
}