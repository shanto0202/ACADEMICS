// Testing for_each algorithms

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void square(int &n)
{
    n *= n;
} // square element

void print(int &n)
{
    cout << n << " ";
} // print element

int main()
{

    vector<int> v;

    v.push_back(11);
    v.push_back(3);
    v.push_back(4);
    v.push_back(22);

    // invoke function for each element
    for_each(v.begin(), v.end(), print);

    cout << endl;

    // square selected elements
    for_each(v.begin() + 1, v.begin() + 3, square);

    for_each(v.begin(), v.end(), print);

    return 0;
}

/*
Key Notes
---------
for_each applies a function to elements in range.
Function receives reference to element.
Can modify container elements.
*/