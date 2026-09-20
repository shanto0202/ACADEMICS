#include <stdio.h>
int main()
{
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    int temp[n];
    for (int i = 0; i < n; i++)
    {
        temp[i] = arr[n - i - 1];
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d ", temp[i]);
    }

    return 0;
}