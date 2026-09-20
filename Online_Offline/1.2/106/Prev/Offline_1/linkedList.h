#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int element;
    Node *next;
    Node *prev;
    Node(int it)
    {
        element = it;
        prev = nullptr;
        next = nullptr;
    }
};

class DoublyLinkedList
{
    Node *head;
    Node *tail;
    Node *curr;
    int length;

    Node *getNodeAt(int idx)
    {
        if (idx < 0 || idx >= length)
            return nullptr;
        Node *t = head;
        for (int i = 0; i < idx; i++)
            t = t->next;
        return t;
    }

    int currentidx()
    {
        Node *t = head;
        int idx = 0;
        while (t != nullptr)
        {
            if (t == curr)
                return idx;
            t = t->next;
            idx++;
        }
        return -1;
    }

public:
    DoublyLinkedList()
    {
        head = tail = curr = nullptr;
        length = 0;
    }

    ~DoublyLinkedList()
    {
        clear();
    }
    void insert(int item)
    {
        Node *n1 = new Node(item);
        if (length == 0)
        {
            head = tail = curr = n1;
        }
        else
        {
            n1->next = curr->next;
            n1->prev = curr;
            if (curr->next != nullptr)
            {
                curr->next->prev = n1;
            }
            else
            {
                tail = n1;
            }
            curr->next = n1;
            curr = n1;
        }
        length++;
    }
    int delete_cur()
    {
        if (curr == nullptr)
            return -1;
        int delx = curr->element;
        Node *tdel = curr;
        Node *nextNode = curr->next;
        Node *prevNode = curr->prev;
        if (length == 1)
        {
            head = tail = curr = nullptr;
        }
        else if (curr == head)
        {
            head = nextNode;
            head->prev = nullptr;
            curr = head;
        }
        else if (curr == tail)
        {
            tail = prevNode;
            tail->next = nullptr;
            curr = tail;
        }
        else
        {
            prevNode->next = nextNode;
            nextNode->prev = prevNode;
            curr = nextNode;
        }
        delete tdel;
        length--;
        return delx;
    }
    void append(int it)
    {
        Node *n1 = new Node(it);
        if (length == 0)
        {
            head = tail = curr = n1;
        }
        else
        {
            tail->next = n1;
            n1->prev = tail;
            tail = n1;
            if (curr == nullptr)
                curr = tail;
        }
        length++;
    }
    int size()
    {
        return length;
    }
    void prev(int n)
    {
        if (curr == nullptr)
            return;
        while (n > 0 && curr->prev != nullptr)
        {
            curr = curr->prev;
            n--;
        }
    }
    void next(int n)
    {
        if (curr == nullptr)
            return;
        while (n > 0 && curr->next != nullptr)
        {
            curr = curr->next;
            n--;
        }
    }
    int is_present(int it)
    {
        return (search(it) != -1);
    }
    void clear()
    {
        Node *t = head;
        while (t != nullptr)
        {
            Node *del = t;
            t = t->next;
            delete del;
        }
        head = tail = curr = nullptr;
        length = 0;
    }
    int delete_item(int item)
    {
        int idx = search(item);
        if (idx == -1)
        {
            return -1;
        }
        return delete_cur();
    }
    void swap_ind(int ind1, int ind2)
    {
        if (ind1 < 0 || ind1 >= length || ind2 < 0 || ind2 >= length)
            return;
        if (ind1 == ind2)
            return;
        Node *node1 = getNodeAt(ind1);
        Node *node2 = getNodeAt(ind2);
        int temp = node1->element;
        node1->element = node2->element;
        node2->element = temp;
    }
    int search(int item)
    {
        Node *t = head;
        int idx = 0;
        while (t != nullptr)
        {
            if (t->element == item)
            {
                curr = t;
                return idx;
            }
            t = t->next;
            idx++;
        }
        return -1;
    }
    int find(int ind)
    {
        Node *n = getNodeAt(ind);
        if (!n)
        {
            return -1;
        }
        curr = n;
        return curr->element;
    }
    int update(int ind, int value)
    {
        Node *n = getNodeAt(ind);
        if (!n)
        {
            return -1;
        }
        int xval = n->element;
        n->element = value;
        curr = n;
        return xval;
    }
    int trim()
    {
        if (length == 0)
        {
            return -1;
        }
        int rval = tail->element;
        Node *tdel = tail;
        if (curr == tail)
        {
            curr = tail->prev;
        }

        if (length == 1)
        {
            head = tail = nullptr;
        }
        else
        {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete tdel;
        length--;
        return rval;
    }
    void reverse()
    {
        if (length <= 1)
            return;
        int odel = currentidx();
        Node *t = nullptr;
        Node *current = head;

        while (current != nullptr)
        {
            t = current->prev;
            current->prev = current->next;
            current->next = t;
            current = current->prev;
        }
        t = head;
        head = tail;
        tail = t;
        if (odel != -1)
        {
            curr = getNodeAt(odel);
        }
    }

    void print()
    {
        if (length == 0)
        {
            cout << "[ . ]" << endl;
            return;
        }
        cout << "[ ";
        Node *t = head;
        while (t != nullptr)
        {
            cout << t->element << " ";
            if (t == curr)
                cout << "| ";
            t = t->next;
        }
        cout << "]" << endl;
    }
};