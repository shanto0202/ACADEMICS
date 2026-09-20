#include <stdio.h>

int main()
{
    int n, num, max = -8777799, min = 100000;
    printf("Enter n: ");
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &num);
        if (num > max)
        {
            max = num;
        }
        if (num < min)
        {
            min = num;
        }
    }
    printf("max=%d & min=%d", max, min);
    printf("\ndifference=%d",max-min);

    return 0;
}