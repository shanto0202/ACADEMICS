#include <iostream>
#include <vector>
using namespace std;

// Accessing Elements

// value_type & operator[] (size_type n);
// [n] operator (without index-bound check)

// value_type & at (size_type n);
// Return reference with bound check

// value_type & front ();
// Return reference to first element

// value_type & back ();
// Return reference to last element

// Modifying Contents

// void push_back (const value_type & val);
// Append element at end

// void pop_back ();
// Remove last element

// void clear ();
// Remove all elements

int main()
{
    vector<int> v;

    v.push_back(10); // add element
    v.push_back(20);
    v.push_back(30);
    cout << "Element [1]: " << v[1] << endl;   // no bound check
    cout << "Using at(): " << v.at(1) << endl; // safe access
    cout << "Front: " << v.front() << endl;    // first element
    cout << "Back: " << v.back() << endl;      // last element
    v.pop_back();                              // remove last element
    cout << "After pop_back, size: " << v.size() << endl;
    v.clear(); // remove all elements //O(n)
    cout << "After clear, size: " << v.size() << endl;

    return 0;
}

/*
Key Notes
---------
operator[] -> fast access but no bound checking
at()       -> safe access with bound checking
front()    -> first element
back()     -> last element

push_back() -> insert element at end
pop_back()  -> remove last element
clear()     -> remove all elements
*/