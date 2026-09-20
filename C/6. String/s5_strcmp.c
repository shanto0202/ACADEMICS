#include <stdio.h>
#include <string.h>
int main()
{
    char s[20] = "ab", k[20] = "abc", l[20] = "ab", p[20] = "aa";
    int a, b, c, d;
    a = strcmp(k, s); // if k>s output: 1
    b = strcmp(l, s); // if l=s output: 0
    c = strcmp(p, s); // if p<s output: -1
    printf("%d %d %d\n", a, b, c);
    a = strncmp("b", s + 1, 2);
    printf("%d", a);
    return 0;
}