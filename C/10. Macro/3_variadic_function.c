#include <stdio.h>
#include <stdarg.h>
int sum(int n, ...)
{
    va_list p;
    va_start(p, n);
    int s = 0;
    for (int i = 0; i < n; i++)
    {
        int x = va_arg(p, int);
        s = s + x;
    }
    va_end(p);
    return s;
}
int main(int argc, char *argv[])
{
    printf("Sum is: %d\n", sum(3, 2, 3, 5));
    return 0;
}