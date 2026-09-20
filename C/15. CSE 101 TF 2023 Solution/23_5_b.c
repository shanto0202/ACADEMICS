#include <stdio.h>
int is_prime(int n)
{
    int fact = 0;
    int i;
    for (i = 1; i * i < n; i++)
    {
        if (n % i == 0)
        {
            fact += 2;
        }
    }
    if (i * i == n)
    {
        fact++;
    }
    if (fact == 2)
    {
        return 1;
    }
    return 0;
}
int main()
{
    int k;
    scanf("%d", &k);
    int i = 2;
    while (1)
    {
        if (is_prime(i) && is_prime(2 * i + 1))
        {
            printf("%d ", i);
        }
        if (k <= i)
        {
            break;
        }
        i++;
    }
    return 0;
}