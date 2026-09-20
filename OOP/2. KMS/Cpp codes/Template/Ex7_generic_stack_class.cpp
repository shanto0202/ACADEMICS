#include <iostream>
using namespace std;

const int SIZE = 10;

// generic stack class
template <class StackType>
class stack
{
    StackType stck[SIZE]; // array to hold stack items
    int tos;              // top of stack

public:
    stack() { tos = 0; } // initialize empty stack

    void push(StackType ob)
    {
        if (tos == SIZE)
        {
            cout << "Stack is full.\n";
            return;
        }

        stck[tos] = ob;
        tos++;
    }

    StackType pop();
};

template <class StackType>
StackType stack<StackType>::pop()
{
    if (tos == 0)
    {
        cout << "Stack is empty.\n";
        return 0;
    }

    tos--;
    return stck[tos];
}

/*
Key Notes:

1. Generic Class → one class can work with different data types.
2. Here stack elements can be int, char, double, etc.
3. push() inserts an item into stack.
4. pop() removes and returns the top item.
5. Compiler creates specific versions when needed.
*/