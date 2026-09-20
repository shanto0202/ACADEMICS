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

struct Node
{
    ll key, h;
    Node *l, *r;
    Node(ll x)
    {
        key = x;
        h = 1;
        l = r = nullptr;
    }
};

Node *root = nullptr;

ll Height_dekhao(Node *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return node->h;
}

void updateHeight(Node *node)
{
    if (node == nullptr)
    {
        return;
    }
    node->h = 1 + max(Height_dekhao(node->l), Height_dekhao(node->r));
}

ll Balance_dekhao(Node *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return Height_dekhao(node->l) - Height_dekhao(node->r);
}

Node *rotateLeft(Node *node)
{
    Node *r_child = node->r;
    Node *majherSubtree = r_child->l;
    r_child->l = node;
    node->r = majherSubtree;
    updateHeight(node);
    updateHeight(r_child);
    return r_child;
}

Node *rotateRight(Node *node)
{
    Node *l_child = node->l;
    Node *majher_Subtree = l_child->r;
    l_child->r = node;
    node->l = majher_Subtree;
    updateHeight(node);
    updateHeight(l_child);
    return l_child;
}

Node *re_balance(Node *node)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    updateHeight(node);
    ll balance = Balance_dekhao(node);
    if (balance > 1)
    {
        if (Balance_dekhao(node->l) < 0)
        {
            node->l = rotateLeft(node->l);
        }
        return rotateRight(node);
    }
    if (balance < -1)
    {
        if (Balance_dekhao(node->r) > 0)
        {
            node->r = rotateRight(node->r);
        }
        return rotateLeft(node);
    }
    return node;
}

Node *node_insert(Node *node, ll k, bool &x)
{
    if (node == nullptr)
    {
        x = true;
        return new Node(k);
    }
    if (k < node->key)
    {
        node->l = node_insert(node->l, k, x);
    }
    else if (k > node->key)
    {
        node->r = node_insert(node->r, k, x);
    }
    else
    {
        x = false;
        return node;
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

Node *Node_sorao(Node *node, ll k, bool &y)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    if (k < node->key)
    {
        node->l = Node_sorao(node->l, k, y);
    }
    else if (k > node->key)
    {
        node->r = Node_sorao(node->r, k, y);
    }
    else
    {
        y = true;
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
        node->key = succ->key;
        bool d = false;
        node->r = Node_sorao(node->r, succ->key, d);
    }
    return re_balance(node);
}

bool find(int key)
{
    Node *current = root;
    while (current != nullptr)
    {
        if (key == current->key)
        {
            return true;
        }
        if (key < current->key)
        {
            current = current->l;
        }
        else
        {
            current = current->r;
        }
    }
    return false;
}

void in_order(Node *node, vector<ll> &a)
{
    if (node == nullptr)
    {
        return;
    }
    in_order(node->l, a);
    a.pb(node->key);
    in_order(node->r, a);
}

bool insert(int key)
{
    bool inserted = false;
    root = node_insert(root, key, inserted);
    return inserted;
}

bool erase(int key)
{
    bool erased = false;
    root = Node_sorao(root, key, erased);
    return erased;
}

vector<int> traverse()
{
    vector<ll> values;
    in_order(root, values);
    return vector<int>(values.begin(), values.end());
}

string serialize(Node *node)
{
    if (node == nullptr)
    {
        return "";
    }
    string s = to_string(node->key);
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
    T_data ins, del, findTime, trav;
    char c;
    while (fin >> c)
    {
        if (c == 'I')
        {
            ll x;
            fin >> x;
            bool x1 = false;
            auto a = chrono::steady_clock::now();
            x1 = insert(x);
            auto b = chrono::steady_clock::now();
            time_jog(ins, chrono::duration_cast<chrono::nanoseconds>(b - a).count());
            if (!x1)
            {
                fout << "duplicate" << tata;
            }
            else
            {
                fout << serialize(root) << tata;
            }
        }
        else if (c == 'D')
        {
            ll x;
            fin >> x;
            bool e = false;
            auto a = chrono::steady_clock::now();
            e = erase(x);
            auto b = chrono::steady_clock::now();
            time_jog(del, chrono::duration_cast<chrono::nanoseconds>(b - a).count());
            if (!e)
            {
                fout << "not found" << tata;
            }
            else
            {
                fout << serialize(root) << tata;
            }
        }
        else if (c == 'F')
        {
            ll x;
            fin >> x;
            auto a = chrono::steady_clock::now();
            bool x1 = find(x);
            auto b = chrono::steady_clock::now();
            time_jog(findTime, chrono::duration_cast<chrono::nanoseconds>(b - a).count());
            if (x1)
            {
                fout << "found" << tata;
            }
            else
            {
                fout << "not found" << tata;
            }
        }
        else if (c == 'T')
        {
            vector<int> v;
            auto a = chrono::steady_clock::now();
            v = traverse();
            auto b = chrono::steady_clock::now();
            time_jog(trav, chrono::duration_cast<chrono::nanoseconds>(b - a).count());
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
    cout << "operation,count,total_ns,average_ns" << tata;
    time_print("insert", ins);
    time_print("delete", del);
    time_print("find", findTime);
    time_print("traverse", trav);
    Tree_mucho(root);
    return 0;
}