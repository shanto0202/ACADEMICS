#include <stdio.h>
int main()
{
    int t, n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    scanf("%d", &t);
    int st = 0, f = n - 1, idx = -1;
    while (st <= f)
    {
        int m = (st + f) / 2;
        if (t == arr[m])
        {
            idx = m;
            break;
        }
        else if (t > arr[m])
        {
            st = m + 1;
        }
        else
        {
            f = m - 1;
        }
    }
    if (idx != -1)
    {
        printf("%d", idx + 1);
    }
    else
    {
        printf("Not Found");
    }
    return 0;
}