#include <iostream>
#include <queue>
using namespace std;

int main()
{

    priority_queue<int> q; // max heap by default

    q.push(1);
    q.push(2);
    q.push(3);

    cout << "The priority queue is : ";

    while (!q.empty())
    {
        cout << q.top() << " "; // largest element
        q.pop();
        
    }

    cout << '\n';

    return 0;
}

/*
Key Notes
---------
priority_queue stores elements in heap order.
Default behavior: max element first.
top() returns highest priority element.
push() inserts element.
pop() removes highest priority element.
Underlying container: vector.
*/
