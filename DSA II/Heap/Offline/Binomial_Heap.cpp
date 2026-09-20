#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define tata "\n"
#define loop(i, j, n) for (ll i = j; i < n; i++)
struct Node
{
    ll k, d;
    Node *parent, *child, *sibling;
    Node(ll x)
    {
        k = x;
        d = 0;
        parent = child = sibling = NULL;
    }
};
class BinomialHeap
{
public:
    Node *head;
    ll heapSize;
    unordered_map<ll, Node *> pos;
    BinomialHeap()
    {
        head = NULL;
        heapSize = 0;
    }
    void linkTree(Node *child, Node *parent)
    {
        child->parent = parent;
        child->sibling = parent->child;
        parent->child = child;
        parent->d++;
    }
    Node *mergeRootLists(Node *a, Node *b)
    {
        Node d(0), *t = &d;
        while (a && b)
        {
            if (a->d <= b->d)
            {
                t->sibling = a;
                a = a->sibling;
            }
            else
            {
                t->sibling = b;
                b = b->sibling;
            }
            t = t->sibling;
        }
        t->sibling = a ? a : b;
        return d.sibling;
    }
    void Heap_comb(bool show = false)
    {
        if (!head)
        {
            return;
        }
        Node *prev = NULL;
        Node *cur = head;
        Node *nxt = cur->sibling;
        while (nxt)
        {
            if (cur->d != nxt->d || (nxt->sibling && nxt->sibling->d == cur->d))
            {
                prev = cur;
                cur = nxt;
            }
            else if (cur->k <= nxt->k)
            {
                if (show)
                {
                    cout << "Link: B" << cur->d << " + B" << nxt->d << " -> B" << cur->d + 1 << tata;
                }
                cur->sibling = nxt->sibling;
                linkTree(nxt, cur);
            }
            else
            {
                if (show)
                {
                    cout << "Link: B" << cur->d << " + B" << nxt->d << " -> B" << cur->d + 1 << tata;
                }
                if (!prev)
                {
                    head = nxt;
                }
                else
                {
                    prev->sibling = nxt;
                }
                linkTree(cur, nxt);
                cur = nxt;
            }
            nxt = cur->sibling;
        }
    }
    void unite(BinomialHeap &other, bool show = false)
    {
        head = mergeRootLists(head, other.head);
        heapSize += other.heapSize;
        for (auto p : other.pos)
        {
            pos[p.first] = p.second;
        }
        other.head = NULL;
        other.heapSize = 0;
        other.pos.clear();
        Heap_comb(show);
    }
    void key_boshao(ll k)
    {
        BinomialHeap one;
        one.head = new Node(k);
        one.heapSize = 1;
        one.pos[k] = one.head;
        unite(one);
    }
    ll findMin()
    {
        ll answer = LLONG_MAX;
        for (Node *root = head; root; root = root->sibling)
        {
            answer = min(answer, root->k);
        }
        return answer;
    }
    ll extractMin()
    {
        Node *Min = head, *min_prev = NULL;
        Node *prev = NULL;
        for (Node *r = head; r; r = r->sibling)
        {
            if (r->k < Min->k)
            {
                Min = r;
                min_prev = prev;
            }
            prev = r;
        }
        if (!min_prev)
        {
            head = Min->sibling;
        }
        else
        {
            min_prev->sibling = Min->sibling;
        }
        Node *children = NULL;
        Node *child = Min->child;
        while (child)
        {
            Node *next = child->sibling;
            child->parent = NULL;
            child->sibling = children;
            children = child;
            child = next;
        }
        BinomialHeap childHeap;
        childHeap.head = children;
        head = mergeRootLists(head, childHeap.head);
        Heap_comb();
        ll answer = Min->k;
        pos.erase(answer);
        heapSize--;
        delete Min;
        return answer;
    }
    void decreaseKey(ll oldKey, ll newKey)
    {
        Node *cur = pos[oldKey];
        pos.erase(oldKey);
        cur->k = newKey;
        pos[newKey] = cur;
        while (cur->parent && cur->k < cur->parent->k)
        {
            Node *parent = cur->parent;
            swap(cur->k, parent->k);
            pos[cur->k] = cur;
            pos[parent->k] = parent;
            cur = parent;
        }
    }
    void removeKey(ll k)
    {
        decreaseKey(k, LLONG_MIN);
        extractMin();
    }
    void Heap_dekhao(ll heapNumber, ostream &out)
    {
        out << "Printing Binomial Heap H" << heapNumber << tata;
        out << "Heap size: " << heapSize << tata;
        if (!head)
        {
            out << "Heap H" << heapNumber << " is empty." << tata;
            return;
        }
        for (Node *root = head; root; root = root->sibling)
        {
            out << "Binomial Tree, B" << root->d << tata;
            queue<Node *> q;
            q.push(root);
            ll level = 0;
            while (!q.empty())
            {
                ll n = q.size();
                vector<ll> ks;
                while (n--)
                {
                    Node *cur = q.front();
                    q.pop();
                    ks.pb(cur->k);
                    for (Node *child = cur->child; child; child = child->sibling)
                    {
                        q.push(child);
                    }
                }
                sort(ks.begin(), ks.end());
                out << "Lev " << level++ << ":";
                for (ll k : ks)
                {
                    out << " " << k;
                }
                out << tata;
            }
        }
    }
    void Tree_dekhao(Node *node, string space, bool last, ll minimum)
    {
        cout << space << (last ? "`-- " : "|-- ") << node->k;
        if (node->k == minimum)
        {
            cout << " [MIN]";
        }
        cout << " (degree " << node->d << ")" << tata;
        vector<Node *> children;
        for (Node *child = node->child; child; child = child->sibling)
        {
            children.pb(child);
        }
        loop(i, 0, (ll)children.size())
        {
            Tree_dekhao(children[i], space + (last ? "    " : "|   "), i + 1 == (ll)children.size(), minimum);
        }
    }
    void visualize(ll heapNumber)
    {
        cout << "Visualizing Heap H" << heapNumber << tata;
        cout << "Heap size: " << heapSize << tata;
        if (!head)
        {
            cout << "Heap H" << heapNumber << " is empty." << tata;
            return;
        }
        ll minimum = findMin();
        for (Node *root = head; root; root = root->sibling)
        {
            cout << "B" << root->d << ", root = " << root->k << tata;
            Tree_dekhao(root, "", true, minimum);
        }
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    string File = "test_00";
    ifstream in(File + "/input.txt");
    ofstream out(File + "/output_mine.txt");
    BinomialHeap heap[3];
    string com;
    while (in >> com)
    {
        if (com == "I")
        {
            ll h, x;
            in >> h >> x;
            heap[h].key_boshao(x);
        }
        else if (com == "F")
        {
            ll h;
            in >> h;
            ll answer = heap[h].findMin();
            cout << "Find Min returned: " << answer << tata;
            out << "Find Min returned: " << answer << tata;
        }
        else if (com == "E")
        {
            ll h;
            in >> h;
            ll answer = heap[h].extractMin();
            cout << "Extract Min returned: " << answer << tata;
            out << "Extract Min returned: " << answer << tata;
        }
        else if (com == "D")
        {
            ll h, x, y;
            in >> h >> x >> y;
            heap[h].decreaseKey(x, y);
        }
        else if (com == "R")
        {
            ll h, x;
            in >> h >> x;
            heap[h].removeKey(x);
        }
        else if (com == "U")
        {
            ll h1, h2;
            in >> h1 >> h2;
            heap[h1].unite(heap[h2]);
        }
        else if (com == "P")
        {
            ll h;
            in >> h;
            heap[h].Heap_dekhao(h, cout);
            heap[h].Heap_dekhao(h, out);
        }
        else if (com == "V")
        {
            ll h;
            in >> h;
            heap[h].visualize(h);
        }
        else if (com == "W")
        {
            ll h1, h2;
            in >> h1 >> h2;
            cout << "Before Union" << tata;
            heap[h1].visualize(h1);
            heap[h2].visualize(h2);
            cout << "Union Steps" << tata;
            heap[h1].unite(heap[h2], true);
            cout << "After Union" << tata;
            heap[h1].visualize(h1);
        }
    }
    return 0;
}