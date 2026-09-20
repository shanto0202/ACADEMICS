#include <bits/stdc++.h>
using namespace std;

#define ll long long

struct Node {
    ll key;
    int deg;
    Node *parent, *child, *sib;

    Node(ll x) {
        key = x;
        deg = 0;
        parent = child = sib = NULL;
    }
};

unordered_map<ll, Node*> pos;
ofstream fout;

void printLine(string s) {
    cout << s << '\n';
    fout << s << '\n';
}

class bHeap {
public:
    Node* head;
    ll nodes;

    bHeap() {
        head = NULL;
        nodes = 0;
    }

    void linkTree(Node* child, Node* parent) {
        child->parent = parent;
        child->sib = parent->child;
        parent->child = child;
        parent->deg++;
    }

    Node* mergeRootLists(Node* a, Node* b) {
        if (a == NULL) return b;
        if (b == NULL) return a;

        Node* newHead;
        Node* temp;

        if (a->deg <= b->deg) {
            newHead = a;
            a = a->sib;
        } else {
            newHead = b;
            b = b->sib;
        }

        temp = newHead;

        while (a != NULL && b != NULL) {
            if (a->deg <= b->deg) {
                temp->sib = a;
                a = a->sib;
            } else {
                temp->sib = b;
                b = b->sib;
            }
            temp = temp->sib;
        }

        if (a != NULL) temp->sib = a;
        else temp->sib = b;

        return newHead;
    }

    void unite(bHeap& other, bool showLinks = false) {
        head = mergeRootLists(head, other.head);
        nodes += other.nodes;

        other.head = NULL;
        other.nodes = 0;

        if (head == NULL) return;

        Node* prev = NULL;
        Node* cur = head;
        Node* next = cur->sib;
        int step = 0;

        while (next != NULL) {
            if (cur->deg != next->deg ||
                (next->sib != NULL && next->sib->deg == cur->deg)) {
                prev = cur;
                cur = next;
            }
            else if (cur->key < next->key) {
                cur->sib = next->sib;

                if (showLinks) {
                    step++;
                    printLine("Link " + to_string(step) + ": B" + to_string(cur->deg) +
                              " + B" + to_string(next->deg) + " -> B" +
                              to_string(cur->deg + 1) + ", parent = " +
                              to_string(cur->key) + ", child = " + to_string(next->key));
                }

                linkTree(next, cur);
            }
            else {
                if (prev == NULL) 
                head = next;
                else 
                prev->sib = next;

                if (showLinks) {
                    step++;
                    printLine("Link " + to_string(step) + ": B" + to_string(cur->deg) +
                              " + B" + to_string(next->deg) + " -> B" +
                              to_string(next->deg + 1) + ", parent = " +
                              to_string(next->key) + ", child = " + to_string(cur->key));
                }

                linkTree(cur, next);
                cur = next;
            }

            next = cur->sib;
        }

        if (showLinks && step == 0) 
        printLine("No links needed.");
    }

    void insertKey(ll x) {
        bHeap ins;
        ins.head = new Node(x);
        ins.nodes = 1;
        pos[x] = ins.head;
        unite(ins);
    }

    ll findMin() {
        Node* cur = head;
        ll mn = cur->key;

        while (cur != NULL) {
            if (cur->key < mn) 
            mn = cur->key;
            cur = cur->sib;
        }

        return mn;
    }

    Node* reverseList(Node* root) {
        Node* prev = NULL;
        Node* cur = root;

        while (cur != NULL) {
            Node* next = cur->sib;
            cur->sib = prev;
            cur->parent = NULL;
            prev = cur;
            cur = next;
        }

        return prev;
    }

    ll extractMin() {
        Node* minNode = head;
        Node* minPrev = NULL;
        Node* prev = NULL;
        Node* cur = head;

        while (cur != NULL) {
            if (cur->key < minNode->key) {
                minNode = cur;
                minPrev = prev;
            }
            prev = cur;
            cur = cur->sib;
        }

        if (minPrev == NULL) 
        head = minNode->sib;
        else 
        minPrev->sib = minNode->sib;

        ll answer = minNode->key;
        pos.erase(answer);

        bHeap childHeap;
        childHeap.head = reverseList(minNode->child);
        childHeap.nodes = 0;

        nodes--;
        unite(childHeap);

        delete minNode;
        return answer;
    }

    void decreaseKey(ll oldKey, ll newKey) {
        Node* cur = pos[oldKey];

        pos.erase(oldKey);
        cur->key = newKey;
        pos[newKey] = cur;

        while (cur->parent != NULL && cur->key < cur->parent->key) {
            Node* par = cur->parent;

            swap(cur->key, par->key);

            pos[cur->key] = cur;
            pos[par->key] = par;

            cur = par;
        }
    }

    void removeKey(ll x) {
        decreaseKey(x, LLONG_MIN);
        extractMin();
    }

    void printHeap(int id) {
        printLine("Printing Binomial Heap H" + to_string(id));
        printLine("Heap size: " + to_string(nodes));

        if (head == NULL) {
            printLine("Heap H" + to_string(id) + " is empty.");
            return;
        }

        Node* root = head;

        while (root != NULL) {
            printLine("Binomial Tree, B" + to_string(root->deg));

            vector<Node*> level;
            level.push_back(root);
            int depth = 0;

            while (!level.empty()) {
                vector<ll> keys;
                vector<Node*> nextLevel;

                for (int i = 0; i < (int)level.size(); i++) {
                    Node* u = level[i];
                    keys.push_back(u->key);

                    Node* child = u->child;
                    while (child != NULL) {
                        nextLevel.push_back(child);
                        child = child->sib;
                    }
                }

                sort(keys.begin(), keys.end());

                string s = "Level " + to_string(depth) + ":";
                for (int i = 0; i < (int)keys.size(); i++) {
                    s += " " + to_string(keys[i]);
                }
                printLine(s);

                level = nextLevel;
                depth++;
            }

            root = root->sib;
        }
    }

    void printSubtree(Node* node, string prefix, bool last) {
        string s = prefix;
        if (last) s += "`-- ";
        else s += "|-- ";

        s += to_string(node->key) + " [deg=" + to_string(node->deg) + "]";
        printLine(s);

        vector<Node*> children;
        Node* child = node->child;
        while (child != NULL) {
            children.push_back(child);
            child = child->sib;
        }

        string nextPrefix = prefix;
        if (last) nextPrefix += "    ";
        else nextPrefix += "|   ";

        for (int i = 0; i < (int)children.size(); i++) {
            printSubtree(children[i], nextPrefix, i == (int)children.size() - 1);
        }
    }

    string binarySize() {
        if (nodes == 0) return "0";

        ll x = nodes;
        string s = "";
        while (x > 0) {
            s += char('0' + x % 2);
            x /= 2;
        }
        reverse(s.begin(), s.end());
        return s;
    }

    void visualize(int id) {
        printLine("========== Visualizing H" + to_string(id) + " ==========");
        printLine("Heap size: " + to_string(nodes));
        printLine("Binary size: " + binarySize());

        if (head == NULL) {
            printLine("Heap H" + to_string(id) + " is empty.");
            return;
        }

        Node* root = head;
        while (root != NULL) {
            printLine("Binomial Tree B" + to_string(root->deg) + ", root = " + to_string(root->key));
            printLine(to_string(root->key) + " [deg=" + to_string(root->deg) + "]");

            vector<Node*> children;
            Node* child = root->child;
            while (child != NULL) {
                children.push_back(child);
                child = child->sib;
            }

            for (int i = 0; i < (int)children.size(); i++) {
                printSubtree(children[i], "", i == (int)children.size() - 1);
            }

            root = root->sib;
        }
    }
};

void visualizeUnion(bHeap& a, bHeap& b, int id1, int id2) {
    printLine("========== Union Visualization ==========");
    printLine("Before Union:");
    a.visualize(id1);
    b.visualize(id2);

    printLine("Link steps:");
    a.unite(b, true);

    printLine("After Union:");
    a.visualize(id1);
}

int main() {

    string fl = "test_02";

    ifstream fin(fl + "/input.txt");
    fout.open(fl + "/outputAmar.txt");

    bHeap H[3];
    string C;

    while (fin >> C) {
        if (C == "I") {
            int h;
            ll x;
            fin >> h >> x;
            H[h].insertKey(x);
        }
        else if (C == "F") {
            int h;
            fin >> h;
            printLine("Find Min returned: " + to_string(H[h].findMin()));
        }
        else if (C == "E") {
            int h;
            fin >> h;
            printLine("Extract Min returned: " + to_string(H[h].extractMin()));
        }
        else if (C == "D") {
            int h;
            ll x, y;
            fin >> h >> x >> y;
            H[h].decreaseKey(x, y);
        }
        else if (C == "R") {
            int h;
            ll x;
            fin >> h >> x;
            H[h].removeKey(x);
        }
        else if (C == "U") {
            int h1, h2;
            fin >> h1 >> h2;
            H[h1].unite(H[h2]);
        }
        else if (C == "P") {
            int h;
            fin >> h;
            H[h].printHeap(h);
        }
        else if (C == "V") {
            int h;
            fin >> h;
            H[h].visualize(h);
        }
        else if (C == "VU") {
            int h1, h2;
            fin >> h1 >> h2;
            visualizeUnion(H[h1], H[h2], h1, h2);
        }
    }

    fin.close();
    fout.close();
    return 0;
}
