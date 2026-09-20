#include <stdio.h>
int main()
{
    int n = 5;
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < n - i-1; k++)
        {
            printf(" ");
        }
        for (int j = 0; j <= i; j++)
        {
            printf("* ");
        }
        printf("\n");
    }
    int m=n-1;
    for (int i =0; i <m; i++)
    {
        for (int k = 0; k <= i; k++)
        {
            printf(" ");
        }
        for (int j = 0; j < m-i; j++)
        {
            printf("* ");
        }
        printf("\n");
    }
    return 0;
}