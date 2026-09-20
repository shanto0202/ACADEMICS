#include <iostream>
using namespace std;

// using typename
template <typename X>
void swapargs(X &a, X &b)
{
    X temp;
    temp = a;
    a = b;
    b = temp;
}

// using class keyword (same meaning)
template <class X>
void swapargs(X &a, X &b)
{
    X temp;
    temp = a;
    a = b;
    b = temp;
}

/*
Key Notes:

1. typename and class mean the same in template parameters.
2. Both specify a type parameter.
3. Example:
   template<typename T>
   template<class T>
*/