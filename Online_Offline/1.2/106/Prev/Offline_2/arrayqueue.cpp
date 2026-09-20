#include "queue.h"
#include <bits/stdc++.h>
#define tata "\n"
#define ll long long
#define pb push_back
#define loop(i, j, n) for (ll i = j; i < n; i++)
using namespace std;

// Constructor implementation
ArrayQueue::ArrayQueue(int initial_capacity)
{
    capacity = initial_capacity;
    data = new int[capacity];
    front_idx = -1;
    rear_idx = -1;
    // TODO: Initialize data members (data, capacity, front_idx, rear_idx)
    // TODO: Allocate memory for the array with the specified initial capacity
}

// Destructor implementation
ArrayQueue::~ArrayQueue()
{
    delete[] data;
    // TODO: Free the dynamically allocated memory for the array
}

// Enqueue implementation (add an item to the rear of the queue)
void ArrayQueue::enqueue(int item)
{
    if (size() == capacity)
    {
        resize(capacity * 2);
    }
    if (empty())
    {
        front_idx = 0;
        rear_idx = 0;
    }
    else
    {
        rear_idx = (rear_idx + 1) % capacity;
    }
    data[rear_idx] = item;
    // TODO: Check if the array is full
    // TODO: If full, resize the array to double its current capacity
    // TODO: Add the new element to the rear of the queue
}

// Dequeue implementation (remove an item from the front of the queue)
int ArrayQueue::dequeue()
{
    if (empty())
    {
        cout << "Queue is empty!" << tata;
        return -1;
    }
    ll x = data[front_idx];
    if (front_idx == rear_idx)
    {
        front_idx = -1;
        rear_idx = -1;
    }
    else
    {
        front_idx = (front_idx + 1) % capacity;
    }
    if (size() <= capacity / 4)
    {
        ll new_cap = capacity / 2;
        if (new_cap >= 2)
        {
            resize(new_cap);
        }
    }
    return x;
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Update front index
    // TODO: If the array is less than 25% full, resize it to half its current capacity (but not less than 2)
    // TODO: Return the dequeued element
}

// Clear implementation
void ArrayQueue::clear()
{
    delete[] data;
    capacity=2;
    data= new int [capacity];
    front_idx = -1;
    rear_idx = -1;

    //  TODO: Reset the queue to be empty (reset capacity, front_idx, rear_idx, data)
}

// Size implementation
int ArrayQueue::size() const
{
    if (front_idx == -1)
    {
        return 0;
    }
    return (rear_idx - front_idx + capacity) % capacity + 1;
    // TODO: Return the number of elements currently in the queue
}

// Front implementation
int ArrayQueue::front() const
{
    if (empty())
    {
        cout << "queue is empty." << tata;
        return -1;
    }
    return data[front_idx];
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Return the element at the front of the queue without removing it
}

// Back implementation (get the element at the back of the queue)
int ArrayQueue::back() const
{
    if (empty())
    {
        cout << "queue is empty." << tata;
        return -1;
    }
    return data[rear_idx];
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Return the element at the back of the queue without removing it
}

// Empty implementation
bool ArrayQueue::empty() const
{
    return front_idx == -1;
    // TODO: Return whether the queue is empty
}

// Print implementation
string ArrayQueue::toString() const
{
    string s = "<";
    if (!empty())
    {
        ll c = size();
        ll cur = front_idx;
        loop(i, 0, c)
        {
            s += to_string(data[cur]);
            if (i < c - 1)
            {
                s += ", ";
            }
            cur = (cur + 1) % capacity;
        }
    }
    s += "|";
    return s;
    // TODO: Convert queue to a string representation in the format: <elem1, elem2, ..., elemN|
}

// Resize implementation
void ArrayQueue::resize(int new_capacity)
{
    int *Data = new int[new_capacity];
    ll l = size(), cur = front_idx;
    loop(i, 0, l)
    {
        Data[i] = data[cur];
        cur = (cur + 1) % capacity;
    }
    delete[] data;
    data = Data;
    capacity = new_capacity;
    if (l == 0)
    {
        front_idx = -1;
        rear_idx = -1;
    }
    else
    {
        front_idx = 0;
        rear_idx = l - 1;
    }
    // TODO: Create a new array with the new capacity
    // TODO: Copy elements from the old array to the new array
    // TODO: Delete the old array
    // TODO: Update the data pointer and capacity
    // TODO: Update front and rear indices
}

int ArrayQueue::getCapacity() const
{
    return capacity;
    // TODO: Return the current capacity of the queue
}