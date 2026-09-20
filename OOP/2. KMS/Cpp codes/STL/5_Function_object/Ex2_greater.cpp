#include <iostream>
#include <algorithm>
#include <vector>
#include <functional> // required header
using namespace std;

int main()
{

    vector<int> num = {5, 2, 8, 1, 9, 4};

    // sort in descending order using functor
    sort(num.begin(), num.end(), greater<int>());

    // print vector
    cout << "Sorted in descending order: ";

    for (int x : num)
    {
        cout << x << " ";
    }

    cout << endl;

    // use function object directly
    greater<int> g;

    if (g(10, 5))
    {
        cout << "10 is greater than 5" << endl;
    }

    return 0;
}

/*
Key Notes
---------
greater<int>() sorts container in descending order.
Default sort uses less<int>().
Functors can be used like functions.
*/