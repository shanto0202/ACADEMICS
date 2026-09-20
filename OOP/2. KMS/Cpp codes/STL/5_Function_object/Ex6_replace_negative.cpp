#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

template <typename X>
class ReplaceNegative
{

public:
    X operator()(X value1, X value2) const
    {

        return (value1 < 0) ? value2 : value1;
    }
};

int main()
{

    list<int> list1 = {5, -3, 7, -8, -2, 10};

    list<int> list2 = {100, 200, 300, 400, 500, 600};

    transform(list1.begin(), list1.end(), list2.begin(), list1.begin(), ReplaceNegative<int>());

    cout << "Modified list1: ";

    for (int value : list1)
        cout << value << ", ";

    cout << endl;

    return 0;
}

/*
Expected Output
---------------
Modified list1: 5, 200, 7, 400, 500, 10

Key Notes
---------
Binary functor receives two inputs.
value1 from list1, value2 from list2.
Negative values replaced by list2 element.
Used with transform().
*/