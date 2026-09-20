#include <stdio.h>
#include <stdlib.h>
int func(int n, int y);
int main()
{
    int a = 6, b = 3;
    printf("%i", func(a, b));
    return 0;
}
int func(int n, int y)
{
    if (y == 0)
    {
        printf("Division by zero\n"); // Add newline
        exit(1);                      // or abort() - terminates entire program
    }
    return n / y;
}