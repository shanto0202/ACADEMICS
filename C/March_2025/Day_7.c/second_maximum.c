#include <stdio.h>
int main()
{
    int n, asc = 0, des = 0, uns = 0;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    int max = arr[0], sec = arr[0];
    for (int i = 0; i < n; i++)
    {
        if (arr[i] >max)
        {
            sec = max;
            max = arr[i];
        }
        if (arr[i] > sec && arr[i] < max)
        {
            sec = arr[i];
        }
    }
    printf("max=%d\nsecond largest=%d",max,sec);
    return 0;
}