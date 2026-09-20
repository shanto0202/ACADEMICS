#include <iostream>
#include <stack>
using namespace std;

int main()
{

    stack<int> st; // create stack container

    st.push(21); // push element
    st.push(22);
    st.push(24);
    st.push(25);

    int num = 0;
    st.push(num);

    st.pop(); // remove top element
    st.pop();
    st.pop();

    while (!st.empty())
    {                               // print stack contents
        cout << st.top() << " "; // access top element
        st.pop();                // remove after printing
    }
}

/*
Key Notes
---------
stack is a container adaptor implementing LIFO.
push() inserts element.
pop() removes top element.
top() accesses top element.
empty() checks if stack is empty.
Default underlying container is deque.
*/