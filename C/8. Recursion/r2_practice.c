#include <stdio.h>
int fun(int n)
{
    if (n == 20)
    {
        return 0;
    }
    printf("%d ", n);
    fun(n + 1);
    return 0;
}
int main()
{
    int n;
    scanf("%d", &n);
    fun(n);
    return 0;
}