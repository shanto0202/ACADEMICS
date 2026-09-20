#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define tata "\n"
#define vr(v, x) vector<ll> v(x)
#define sajai(x) sort(x.begin(), x.end())
#define loop(i, j, n) for (ll i = j; i < n; i++)
#define in(v) loop(i, 0, v.size()) cin >> v[i]
#define out(v) loop(i, 0, v.size()) cout << v[i] << " "
#define yes fout << "yes" << tata
#define no fout << "no" << tata

struct Node
{
    ll id, start, end;
    ll h, maxEnd;
    Node *l, *r;
    Node(ll x, ll a, ll b)
    {
        id = x;
        start = a;
        end = b;
        h = 1;
        maxEnd = b;
        l = r = nullptr;
    }
};

struct Event
{
    ll start, end;
};

Node *root = nullptr;
ll nextId = 1;
unordered_map<ll, Event> ev;

ll Height_dekhao(Node *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return node->h;
}

ll maxend_dekhao(Node *node)
{
    if (node == nullptr)
    {
        return LLONG_MIN;
    }
    return node->maxEnd;
}

void Node_update(Node *node)
{
    if (node == nullptr)
    {
        return;
    }
    node->h = 1 + max(Height_dekhao(node->l), Height_dekhao(node->r));
    node->maxEnd = max(node->end, max(maxend_dekhao(node->l), maxend_dekhao(node->r)));
}

ll Balance_dekhao(Node *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return Height_dekhao(node->l) - Height_dekhao(node->r);
}

bool choto(ll s1, ll id1, ll s2, ll id2)
{
    if (s1 != s2)
    {
        return s1 < s2;
    }
    return id1 < id2;
}

Node *rotateLeft(Node *node)
{
    Node *r_child = node->r;
    Node *majher_Subtree = r_child->l;
    r_child->l = node;
    node->r = majher_Subtree;
    Node_update(node);
    Node_update(r_child);
    return r_child;
}

Node *rotateRight(Node *node)
{
    Node *l_child = node->l;
    Node *majher_Subtree = l_child->r;
    l_child->r = node;
    node->l = majher_Subtree;
    Node_update(node);
    Node_update(l_child);
    return l_child;
}

Node *re_balance(Node *node)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    Node_update(node);
    ll bal = Balance_dekhao(node);
    if (bal > 1)
    {
        if (Balance_dekhao(node->l) < 0)
        {
            node->l = rotateLeft(node->l);
        }
        return rotateRight(node);
    }
    if (bal < -1)
    {
        if (Balance_dekhao(node->r) > 0)
        {
            node->r = rotateRight(node->r);
        }
        return rotateLeft(node);
    }
    return node;
}

Node *Node_insert(Node *node, ll id, ll start, ll end)
{
    if (node == nullptr)
    {
        return new Node(id, start, end);
    }
    if (choto(start, id, node->start, node->id))
    {
        node->l = Node_insert(node->l, id, start, end);
    }
    else
    {
        node->r = Node_insert(node->r, id, start, end);
    }
    return re_balance(node);
}

Node *min_Node(Node *node)
{
    Node *cur = node;
    while (cur->l != nullptr)
    {
        cur = cur->l;
    }
    return cur;
}

Node *Node_mucho(Node *node, ll st, ll id)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    if (choto(st, id, node->start, node->id))
    {
        node->l = Node_mucho(node->l, st, id);
    }
    else if (choto(node->start, node->id, st, id))
    {
        node->r = Node_mucho(node->r, st, id);
    }
    else
    {
        if (node->l == nullptr)
        {
            Node *t = node->r;
            delete node;
            return t;
        }
        if (node->r == nullptr)
        {
            Node *t = node->l;
            delete node;
            return t;
        }
        Node *succ = min_Node(node->r);
        node->id = succ->id;
        node->start = succ->start;
        node->end = succ->end;
        node->r = Node_mucho(node->r, succ->start, succ->id);
    }
    return re_balance(node);
}

bool over_lap(ll s1, ll e1, ll s2, ll e2)
{
    return s1 < e2 && s2 < e1;
}

bool Node_cnflt(Node *node, ll qs, ll qe)
{
    Node *cur = node;
    while (cur != nullptr)
    {
        if (over_lap(cur->start, cur->end, qs, qe))
        {
            return true;
        }
        if (cur->l != nullptr && cur->l->maxEnd > qs)
        {
            cur = cur->l;
        }
        else
        {
            cur = cur->r;
        }
    }
    return false;
}

void Node_overlap(Node *node, ll qs, ll qe, vector<ll> &a)
{
    if (node == nullptr || node->maxEnd <= qs)
    {
        return;
    }
    Node_overlap(node->l, qs, qe, a);
    if (over_lap(node->start, node->end, qs, qe))
    {
        a.pb(node->id);
    }
    if (node->start < qe)
    {
        Node_overlap(node->r, qs, qe, a);
    }
}

void active_interval(Node *node, ll t, vector<ll> &a)
{
    if (node == nullptr || node->maxEnd <= t)
    {
        return;
    }
    active_interval(node->l, t, a);
    if (node->start <= t && t < node->end)
    {
        a.pb(node->id);
    }
    if (node->start <= t)
    {
        active_interval(node->r, t, a);
    }
}

Node *nextNode(ll t)
{
    Node *cur = root;
    Node *a = nullptr;
    while (cur != nullptr)
    {
        if (cur->start >= t)
        {
            a = cur;
            cur = cur->l;
        }
        else
        {
            cur = cur->r;
        }
    }
    return a;
}

string serialize(Node *node)
{
    if (node == nullptr)
    {
        return "";
    }
    string s = to_string(node->id);
    if (node->l != nullptr || node->r != nullptr)
    {
        s += "(";
        s += serialize(node->l);
        s += ",";
        s += serialize(node->r);
        s += ")";
    }
    return s;
}

void Tree_mucho(Node *node)
{
    if (node == nullptr)
    {
        return;
    }
    Tree_mucho(node->l);
    Tree_mucho(node->r);
    delete node;
}

struct T_data
{
    ll c = 0, t_ns = 0;
};

void time_jog(T_data &x, ll ns)
{
    x.c++;
    x.t_ns += ns;
}

void time_print(string op, T_data x)
{
    cout << op << "," << x.c << "," << x.t_ns << ",";
    if (x.c == 0)
    {
        cout << "N/A";
    }
    else
    {
        cout << x.t_ns / x.c;
    }
    cout << tata;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (argc != 3)
    {
        return 1;
    }
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    if (!fin || !fout)
    {
        cerr << "File open error" << tata;
        return 1;
    }
    T_data add, remv, upd;
    T_data cnflt, ovlp, cur, nxt;
    string c;
    while (fin >> c)
    {
        if (c == "ADD")
        {
            ll s, e;
            fin >> s >> e;
            auto a = chrono::steady_clock::now();
            ll id = nextId++;
            root = Node_insert(root, id, s, e);
            ev[id] = {s, e};
            auto b = chrono::steady_clock::now();
            time_jog(add, chrono::duration_cast<chrono::nanoseconds>(b - a).count());
            fout << serialize(root) << tata;
        }
        else if (c == "REMOVE")
        {
            ll x;
            fin >> x;
            auto a = chrono::steady_clock::now();
            bool y = false;
            auto it = ev.find(x);
            if (it != ev.end())
            {
                root = Node_mucho(root, it->second.start, x);
                ev.erase(it);
                y = true;
            }
            auto b = chrono::steady_clock::now();
            time_jog(remv, chrono::duration_cast<chrono::nanoseconds>(b - a).count());
            if (!y)
            {
                fout << "not found" << tata;
            }
            else
            {
                fout << serialize(root) << tata;
            }
        }
        else if (c == "UPDATE")
        {
            ll x, s, e;
            fin >> x >> s >> e;
            auto a = chrono::steady_clock::now();
            bool y = false;
            auto it = ev.find(x);
            if (it != ev.end())
            {
                root = Node_mucho(root, it->second.start, x);
                root = Node_insert(root, x, s, e);
                it->second = {s, e};
                y = true;
            }
            auto b = chrono::steady_clock::now();
            time_jog(upd, chrono::duration_cast<chrono::nanoseconds>(b - a).count());
            if (!y)
            {
                fout << "not found" << tata;
            }
            else
            {
                fout << serialize(root) << tata;
            }
        }
        else if (c == "CONFLICT")
        {
            ll s, e;
            fin >> s >> e;
            auto a = chrono::steady_clock::now();
            bool x = Node_cnflt(root, s, e);
            auto b = chrono::steady_clock::now();
            time_jog(cnflt, chrono::duration_cast<chrono::nanoseconds>(b - a).count());
            if (x)
            {
                yes;
            }
            else
            {
                no;
            }
        }
        else if (c == "OVERLAPS")
        {
            ll s, e;
            fin >> s >> e;
            vector<ll> v;
            auto a = chrono::steady_clock::now();
            Node_overlap(root, s, e, v);
            auto b = chrono::steady_clock::now();
            time_jog(ovlp, chrono::duration_cast<chrono::nanoseconds>(b - a).count());
            if (v.empty())
            {
                fout << "none" << tata;
            }
            else
            {
                loop(i, 0, v.size())
                {
                    if (i)
                    {
                        fout << " ";
                    }
                    fout << v[i];
                }
                fout << tata;
            }
        }
        else if (c == "AT")
        {
            ll t;
            fin >> t;
            vector<ll> ans;
            auto st = chrono::steady_clock::now();
            active_interval(root, t, ans);
            auto en = chrono::steady_clock::now();
            time_jog(cur, chrono::duration_cast<chrono::nanoseconds>(en - st).count());
            if (ans.empty())
            {
                fout << "none" << tata;
            }
            else
            {
                loop(i, 0, ans.size())
                {
                    if (i)
                    {
                        fout << " ";
                    }
                    fout << ans[i];
                }
                fout << tata;
            }
        }
        else if (c == "NEXT")
        {
            ll t;
            fin >> t;
            auto st = chrono::steady_clock::now();
            Node *ans = nextNode(t);
            auto en = chrono::steady_clock::now();
            time_jog(nxt, chrono::duration_cast<chrono::nanoseconds>(en - st).count());
            if (ans == nullptr)
            {
                fout << "none" << tata;
            }
            else
            {
                fout << ans->id << " " << ans->start << " " << ans->end << tata;
            }
        }
    }
    cout << "operation,count,total_ns,average_ns" << tata;
    time_print("add", add);
    time_print("remove", remv);
    time_print("update", upd);
    time_print("conflict", cnflt);
    time_print("overlaps", ovlp);
    time_print("at", cur);
    time_print("next", nxt);
    Tree_mucho(root);
    return 0;
}