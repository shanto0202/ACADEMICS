#include <iostream>
#include <vector>

using namespace std;

template <typename T>
struct Node
{
    T data;
    Node *next;
    Node *random; // For Problem 10
    Node *child;  // For Problem 8

    Node(T val) : data(val), next(nullptr), random(nullptr), child(nullptr) {}
};

template <typename T>
class LinkedList
{
public:
    Node<T> *head;

    LinkedList() : head(nullptr) {}

    // Helper: Add to end
    void push_back(T val)
    {
        if (!head)
        {
            head = new Node<T>(val);
            return;
        }
        Node<T> *temp = head;
        while (temp->next)
            temp = temp->next;
        temp->next = new Node<T>(val);
    }

    // 1. Reverse
    void reverse()
    {
        Node<T> *prev = nullptr, *curr = head, *next = nullptr;
        while (curr)
        {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }

    // 2. Detect Cycle
    bool hasCycle()
    {
        Node<T> *slow = head, *fast = head;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast)
                return true;
        }
        return false;
    }

    // 3. Merge Two Sorted Lists (Static helper)
    static Node<T> *mergeSorted(Node<T> *l1, Node<T> *l2)
    {
        if (!l1)
            return l2;
        if (!l2)
            return l1;
        if (l1->data < l2->data)
        {
            l1->next = mergeSorted(l1->next, l2);
            return l1;
        }
        else
        {
            l2->next = mergeSorted(l1, l2->next);
            return l2;
        }
    }

    // 4. Remove Nth from End
    void removeNthFromEnd(int n)
    {
        Node<T> dummy(0);
        dummy.next = head;
        Node<T> *fast = &dummy, *slow = &dummy;
        for (int i = 0; i < n; i++)
            fast = fast->next;
        while (fast->next)
        {
            fast = fast->next;
            slow = slow->next;
        }
        Node<T> *toDelete = slow->next;
        slow->next = slow->next->next;
        delete toDelete;
        head = dummy.next;
    }

    // 5. Find Middle
    Node<T> *findMiddle()
    {
        Node<T> *slow = head, *fast = head;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    // 6. Check Palindrome
    bool isPalindrome()
    {
        if (!head || !head->next)
            return true;
        Node<T> *mid = findMiddle();
        // Reverse second half
        Node<T> *prev = nullptr, *curr = mid, *next = nullptr;
        while (curr)
        {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        Node<T> *first = head, *second = prev;
        while (second)
        {
            if (first->data != second->data)
                return false;
            first = first->next;
            second = second->next;
        }
        return true;
    }

    // 7. Rotate Right by K
    void rotateRight(int k)
    {
        if (!head || k == 0)
            return;
        int len = 1;
        Node<T> *tail = head;
        while (tail->next)
        {
            tail = tail->next;
            len++;
        }
        k %= len;
        if (k == 0)
            return;
        tail->next = head; // Make circular
        for (int i = 0; i < len - k; i++)
            tail = tail->next;
        head = tail->next;
        tail->next = nullptr;
    }

    // 8. Flatten Multilevel (Doubly/Child logic)
    void flatten()
    {
        Node<T> *curr = head;
        while (curr)
        {
            if (curr->child)
            {
                Node<T> *next = curr->next;
                Node<T> *childTail = curr->child;
                while (childTail->next)
                    childTail = childTail->next;
                curr->next = curr->child;
                childTail->next = next;
                curr->child = nullptr;
            }
            curr = curr->next;
        }
    }

    // 9. Intersection Point
    static Node<T> *getIntersection(Node<T> *h1, Node<T> *h2)
    {
        Node<T> *a = h1, *b = h2;
        while (a != b)
        {
            a = a ? a->next : h2;
            b = b ? b->next : h1;
        }
        return a;
    }

    // 10. Clone with Random Pointers
    Node<T> *cloneWithRandom()
    {
        if (!head)
            return nullptr;
        // Step 1: Insert copy nodes
        Node<T> *curr = head;
        while (curr)
        {
            Node<T> *copy = new Node<T>(curr->data);
            copy->next = curr->next;
            curr->next = copy;
            curr = copy->next;
        }
        // Step 2: Copy random pointers
        curr = head;
        while (curr)
        {
            if (curr->random)
                curr->next->random = curr->random->next;
            curr = curr->next->next;
        }
        // Step 3: Separate lists
        Node<T> *newHead = head->next;
        curr = head;
        while (curr)
        {
            Node<T> *temp = curr->next;
            curr->next = temp->next;
            if (temp->next)
                temp->next = temp->next->next;
            curr = curr->next;
        }
        return newHead;
    }

    void print()
    {
        Node<T> *temp = head;
        while (temp)
        {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
};

int main()
{
    LinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);

    cout << "Original: ";
    list.print();
    list.reverse();
    cout << "Reversed: ";
    list.print();

    return 0;
}