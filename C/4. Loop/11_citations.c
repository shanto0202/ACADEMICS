#include <stdio.h>
int calculateHindex(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (a[i] < i)
        {
            return i;
        }
    }
    return 0;
}
int main()
{
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    printf("%d", calculateHindex(arr, n));
    return 0;
}