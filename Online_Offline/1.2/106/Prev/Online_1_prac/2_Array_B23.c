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
    ll n, k;
    scanf("%lld", &n);
    ll a[n];
    in(a);
    for (int i = 0; i < n; i++)
    {
        k = 1;
        for (int j = i + 1; j < n; j++)
        {
            if (a[j] > a[i])
            {
                k = 0;
                break;
            }
        }
        if (k)
        {
            printf("%d ", a[i]);
        }
    }
    return 0;
}