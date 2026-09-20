#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ll long long
#define loop(i, j, n) for (ll i = j; i < n; i++)
#define in(arr) loop(i, 0, n) scanf("%lld", &arr[i])
#define out(arr) loop(i, 0, n) printf("%lld ", arr[i])
#define no printf("NO\n")
#define yes printf("YES\n")

void countInversion(int arr[], int n)
{
    if (n < 2)
    {
        printf("Invaid input\n");
        return;
    }
    int x = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (arr[i] > arr[j])
            {
                x = 0;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    if (x)
    {
        printf("Second largest element not found\n");
    }
    {
        printf("%d\n", arr[1]);
    }
}
int main()
{
    int T, t, n, i, inv;
    int *arr;
    scanf("%d", &T);
    for (t = 0; t < T; t++)
    {
        scanf("%d", &n);
        arr = (int *)malloc(n * sizeof(int));
        for (i = 0; i < n; i++)
        {
            scanf("%d", &arr[i]);
        }
        countInversion(arr, n);
        free(arr);
    }
    return 0;
}