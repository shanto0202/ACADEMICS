#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ll long long
#define loop(i, j, n) for (ll i = j; i < n; i++)
#define in(arr) loop(i, 0, n) scanf("%lld", &arr[i])
#define out(arr) loop(i, 0, n) printf("%lld ", arr[i])
#define no printf("NO\n")
#define yes printf("YES\n")

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        ll n, m = LONG_LONG_MIN;
        scanf("%lld", &n);
        ll arr[n];
        in(arr);
        if (n < 3)
        {
            printf("Invalid input\n");
            continue;
        }
        for (int i = 2; i < n; i++)
        {
            m = (m > (arr[i] + arr[i - 1] + arr[i - 2])) ? m : (arr[i] + arr[i - 1] + arr[i - 2]);
        }
        for (int i = 2; i < n; i++)
        {
            if (m == arr[i] + arr[i - 1] + arr[i - 2])
            {
                printf("%d %d %d", arr[i - 2], arr[i - 1], arr[i]);
                break;
            }
        }
        printf("\n");
    }
    return 0;
}