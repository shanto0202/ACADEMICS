#include <iostream>
#include <vector>
using namespace std;


// Functions in Vector Template Class
// Constructors

// vector (const allocator_type & alloc = allocator_type());
// Default Constructor: construct a vector object

// vector (size_type n, const value_type & val = value_type(),
// const allocator_type & alloc = allocator_type());
// Fill Constructor: construct a vector object with n-element filled with val

// vector (const vector & v); // Copy Constructor

// template <class InputIterator>
// vector (InputIterator first, InputIterator last,
// const allocator_type & alloc = allocator_type());
// Range Copy Constructor

// Size and Capacity

// size_type size () const;        // Return the size (number of elements)
// size_type capacity () const;    // Return the storage allocated
// bool empty () const;            // Return true if size is 0
// void reserve (size_type n);     // Request storage to hold n elements
// void resize (size_type n, value_type val = value_type());
// size_type max_size () const;    // Maximum possible elements
// void shrink_to_fit ();          // Shrink storage

int main()
{
    vector<int> v1;                       // default constructor
    vector<int> v2(5, 10);                // fill constructor
    vector<int> v3(v2);                   // copy constructor
    vector<int> v4(v2.begin(), v2.end()); // range constructor
    cout << "Size: " << v2.size() << endl;
    cout << "Capacity: " << v2.capacity() << endl;
    cout << "Empty? " << v1.empty() << endl;
    v1.reserve(10);  // reserve memory
    v1.resize(5, 2); // resize vector
    cout << "Max size: " << v1.max_size() << endl;
    v1.shrink_to_fit(); // shrink capacity
    return 0;
}

/*
Key Notes
---------
vector()              -> creates empty vector
vector(n,val)         -> creates n elements filled with val
vector(v)             -> copy constructor
vector(begin,end)     -> copy a range
size()                -> number of elements
capacity()            -> allocated memory
empty()               -> check if vector empty
reserve(n)            -> allocate memory
resize(n,val)         -> change size
max_size()            -> maximum possible size
shrink_to_fit()       -> reduce unused capacity
*/