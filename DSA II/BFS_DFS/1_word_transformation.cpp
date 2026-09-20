#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define tata "\n"
#define loop(i, j, n) for (ll i = j; i < n; i++)

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;

    vector<string> words(n);
    unordered_set<string> st;

    for (ll i = 0; i < n; i++)
    {
        cin >> words[i];
        st.insert(words[i]);
    }

    string start, target;
    cin >> start >> target;

    if (start == target)
    {
        cout << 0 << tata;
        return 0;
    }

    queue<pair<string, ll>> q;
    q.push({start, 0});

    st.erase(start);

    while (!q.empty())
    {
        string word = q.front().first;
        ll steps = q.front().second;
        q.pop();

        for (ll i = 0; i < word.size(); i++)
        {
            char original = word[i];

            for (char ch = 'a'; ch <= 'z'; ch++)
            {
                if (ch == original)
                    continue;

                word[i] = ch;

                if (st.count(word))
                {
                    if (word == target)
                    {
                        cout << steps + 1 << tata;
                        return 0;
                    }

                    q.push({word, steps + 1});
                    st.erase(word);
                }
            }

            word[i] = original;
        }
    }

    cout << -1 << tata;

    return 0;
}