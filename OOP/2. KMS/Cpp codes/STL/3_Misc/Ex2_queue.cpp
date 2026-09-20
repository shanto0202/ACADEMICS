#include <iostream>
#include <queue>
using namespace std;

// Print the queue
void print_queue(queue<int> &q)
{
    while (!q.empty())
    {
        cout << q.front() << " " << q.back() << '\n'; // show front and back
        q.pop();
    }

    cout << '\n';
}

int main()
{

    queue<int> q1;

    q1.push(1);
    q1.push(2);
    q1.push(3);

    cout << "The first queue is : \n";

    print_queue(q1);

    return 0;
}

/*
Key Notes
---------
queue implements FIFO structure.
push() inserts element at back.
pop() removes element from front.
front() returns first element.
back() returns last element.
*/