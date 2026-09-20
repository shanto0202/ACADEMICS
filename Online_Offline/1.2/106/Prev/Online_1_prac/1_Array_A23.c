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
    ll n, m = LONG_LONG_MIN;
    scanf("%lld", &n);
    ll arr[n + 1];
    ll p[n + 1];
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &arr[i]);
    }
    p[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        p[i] = p[i - 1] + arr[i];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            m = (m > (p[j] - p[i])) ? m : (p[j] - p[i]);
        }
    }
    printf("%lld\n", m);
    return 0;
}