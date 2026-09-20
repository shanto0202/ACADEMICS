#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define tata "\n"
#define vr(v, x) vector<ll> v(x)
#define sajai(x) sort(x.begin(), x.end())
#define choto(a) *min_element(a.begin(), a.end())
#define boro(a) *max_element(a.begin(), a.end())
#define jog(a) accumulate(a.begin(), a.end(), 0LL)
#define bit(n) __builtin_popcountll(n)
#define loop(i, j, n) for (ll i = j; i < n; i++)
#define in(v) loop(i, 0, v.size()) cin >> v[i]
#define out(v) loop(i, 0, v.size()) cout << v[i] << tata

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll I, D, R, m, n;
    string S, T;
    cin >> I >> D >> R;
    cin.ignore();
    getline(cin, S);
    getline(cin, T);
    m = S.size();
    n = T.size();
    ll dp[m + 1][n + 1];
    // O(n)
    loop(j, 0, n + 1)
    {
        dp[0][j] = I * j;
    }
    // O(m)
    loop(i, 0, m + 1)
    {
        dp[i][0] = D * i;
    }
    // O(mn)
    loop(i, 1, m + 1)
    {
        loop(j, 1, n + 1)
        {
            if (S[i - 1] == T[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = min({dp[i][j - 1] + I, dp[i - 1][j] + D, R + dp[i - 1][j - 1]});
            }
        }
    }
    ll i = m, j = n;
    vector<string> v;
    // O(m+n) ->worst case need to delete all and matches nothing
    while (i != 0 || j != 0)
    {
        if (j > 0 && dp[i][j] == dp[i][j - 1] + I)
        {
            v.pb("Insert " + string(1, T[j - 1]));
            j--;
        }
        else if (i > 0 && dp[i][j] == dp[i - 1][j] + D)
        {
            v.pb("Delete " + string(1, S[i - 1]));
            i--;
        }
        else if (i > 0 && j > 0 && S[i - 1] == T[j - 1])
        {
            v.pb("Match " + string(1, S[i - 1]));
            i--;
            j--;
        }
        else if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + R)
        {
            v.pb("Replace " + string(1, S[i - 1]) + " with " + string(1, T[j - 1]));
            i--;
            j--;
        }
    }
    // O(m+n)
    reverse(v.begin(), v.end());
    cout << "Minimum Cost: " << dp[m][n] << tata;
    cout << "Operations: " << tata;
    // O(m+n)
    out(v);
    // overall time complexity O(mn)
    return 0;
}

/*
Example:
I = 2 , D = 2 , R = 3
S = "CAT", T = "CUT"

--------DP Table------
         C   U   T
   [ 0   2   4   6 ]
C  [ 2   0   2   4 ]
A  [ 4   2   3   5 ]
T  [ 6   4   5   3 ]

Traceback
1. dp[3][3] 'T'=='T' -> Match (cost 0), move to dp[2][2]
2. dp[2][2] 'A'!='U' -> Replace (cost 3), move to dp[1][1]
3. dp[1][1] 'C'=='C' -> Match (cost 0), move to dp[0][0]
*/