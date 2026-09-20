#include <stdio.h>
int main()
{
    char c;
    int x, n;
    scanf("%c %d", &c, &x);
    n = ((c - 65 + x) % 26) + 65;
    printf("%c",n);
    return 0;
}