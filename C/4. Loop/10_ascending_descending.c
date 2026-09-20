#include <stdio.h>
int main()
{
    int n, min = 10000000, max = -1, a = 0, d = 0;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
        if (max < arr[i])
        {
            max = arr[i];
        }
        if (min > arr[i])
        {
            min = arr[i];
        }
    }
    for (int i = 2; i < n; i++)
    {
        if (arr[i - 2] <= arr[i - 1] && arr[i - 1] <= arr[i])
        {
            a++;
        }
        else if (arr[i - 2] >= arr[i - 1] && arr[i - 1] >= arr[i])
        {
            d++;
        }
        else
        {
            printf("U\n");
            break;
        }
    }
    int s = 0;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] == arr[j])
            {
                arr[j] = 0;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        s = s + arr[i];
    }
    if (a == n - 2)
    {
        printf("A\n");
    }
    else if (d == n - 2)
    {
        printf("D\n");
    }
    printf("k:%d & f:%d", max - min, s);
    return 0;
}