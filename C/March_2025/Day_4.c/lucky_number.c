#include <stdio.h>
 
int main()
{
    long long n;
    int  reminder, count = 0;
    scanf("%lld", &n);
    while (n != 0)
    {
        reminder = n % 10;
        if (reminder == 4 || reminder == 7)
        {
            count++;
        }
        n = n / 10;
    }
    if (count == 4 || count == 7)
    {
        printf("YES");
    }
    else
    {
        printf("NO");
    }
}