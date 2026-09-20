#include "queue.h"
#include <bits/stdc++.h>
#define tata "\n"
#define ll long long
#define pb push_back
#define loop(i, j, n) for (ll i = j; i < n; i++)
using namespace std;

// Constructor implementation
ListQueue::ListQueue()
{
    front_node = nullptr;
    rear_node = nullptr;
    current_size = 0;
    // TODO: Initialize front_node and rear_node
    // TODO: Initialize current_size to 0
}

// Destructor implementation
ListQueue::~ListQueue()
{
    clear();
    // TODO: Deallocate all nodes in the linked list
    // TODO: Consider using the clear() method
}

// Enqueue implementation (add an item at the rear of the queue)
void ListQueue::enqueue(int item)
{
    Node *t = new Node(item);
    if (empty())
    {
        front_node = t;
        rear_node = t;
    }
    else
    {
        rear_node->next = t;
        rear_node = t;
    }
    current_size++;
    // TODO: Create a new node with the given item
    // TODO: Link the new node to the rear
    // TODO: Update the rear_node
    // TODO: Increment the current size
}

// Dequeue implementation (remove an item from the front of the queue)
int ListQueue::dequeue()
{
    if (empty())
    {
        cout << "Queue is Empty!" << tata;
        return -1;
    }
    int x = front_node->data;
    Node *t = front_node;
    front_node = front_node->next;
    if (front_node == nullptr)
    {
        rear_node = nullptr;
    }
    delete t;
    current_size--;
    return x;
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Store the data from the front node
    // TODO: Update the front pointer to the next node
    // TODO: Update the rear pointer if the queue becomes empty
    // TODO: Delete the old front node
    // TODO: Decrement current_size
    // TODO: Return the stored data
}

// Clear implementation (delete all elements)
void ListQueue::clear()
{
    while (front_node != nullptr)
    {
        Node *t = front_node;
        front_node = front_node->next;
        delete t;
    }
    rear_node = nullptr;
    current_size = 0;
    // TODO: Traverse the linked list and delete each node
    // TODO: Reset front and rear pointer
    // TODO: Reset current_size to 0
}

// Size implementation (return the current number of elements)
int ListQueue::size() const
{
    return current_size;
    // TODO: Return the current size (current_size)
}

// Front implementation (get the element at the front of the queue)
int ListQueue::front() const
{
    if (empty())
    {
        cout << "Queue is empty!" << tata;
        return -1;
    }
    return front_node->data;
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Return the data from the front node without removing it
}

// Back implementation (get the element at the back of the queue)
int ListQueue::back() const
{
    if (empty())
    {
        cout << "Queue is empty!" << tata;
        return -1;
    }
    return rear_node->data;
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Return the data from the back node without removing it
}

// Empty implementation (check if the queue is empty)
bool ListQueue::empty() const
{
    return front_node == nullptr;
    // TODO: Return whether front is nullptr
}

// Print implementation (print elements from front to rear)
string ListQueue::toString() const
{
    string s = "<";
    Node *cur = front_node;
    while (cur != nullptr)
    {
        s += to_string(cur->data);
        if (cur->next != nullptr)
        {
            s += ", ";
        }
        cur = cur->next;
    }
    s += "|";
    return s;
    // TODO: Convert queue to a string representation in the format: <elem1, elem2, ..., elemN|
    // TODO: Traverse the linked list from front
}