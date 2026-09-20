#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ll long long
#define loop(i, j, n) for (ll i = j; i < n; i++)
#define in(arr) loop(i, 0, n) scanf("%lld", &arr[i])
#define out(arr) loop(i, 0, n) printf("%lld ", arr[i])
#define no printf("NO\n")
#define yes printf("YES\n")
#define N 1000000
ll p[N];

int main()
{
    ll n, l = 1;
    scanf("%lld", &n);
    ll arr[n];
    in(arr);
    for (int i = 0; i < n; i++)
    {
        p[arr[i]]++;
    }
    for (int i = 1; i < N; i++)
    {

        if (p[i] > n / 2)
        {
            l = 0;
            printf("%lld ", i);
        }
    }
    if (l)
    {
        printf("No Majority Candidate\n");
    }
    return 0;
}