#include <stdio.h>
int main()
{
    int k;
    scanf("%d", &k);
    int arr[2 * k + 1];
    for (int i = 2; i < 2 * k + 1; i++)
    {
        arr[i] = 1;
        for (int j = 2; j * j <= i; j++)
        {
            if (i % j == 0)
            {
                arr[i] = 0;
                break;
            }
        }
    }
    for (int i = 1; i < k; i++)
    {
        if (arr[2 * i + 1] == 1 && arr[i] == 1)
        {
            printf("%d ", i);
        }
    }
    return 0;
}