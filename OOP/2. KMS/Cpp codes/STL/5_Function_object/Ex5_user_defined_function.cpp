// Create a reciprocal function object.

#include <iostream>
#include <list>
#include <functional>
#include <algorithm>
using namespace std;

// custom functor
template <class result_type, class argument_type>
class reciprocal
{

public:
    result_type operator()(argument_type i)
    {
        return (result_type)1.0 / i; // reciprocal
    }
};

int main()
{

    list<double> vals;

    int i;

    for (i = 1; i < 10; i++)
        vals.push_back((double)i);

    cout << "Original contents of vals:\n";

    list<double>::iterator p = vals.begin();

    while (p != vals.end())
    {
        cout << *p << " ";
        p++;
    }

    cout << endl;

    // apply custom functor
    p = transform(vals.begin(), vals.end(), vals.begin(), reciprocal<double, double>());

    cout << "Transformed contents of vals:\n";

    p = vals.begin();

    while (p != vals.end())
    {
        cout << *p << " ";
        p++;
    }

    return 0;
}

/*
Key Notes
---------
User functor must overload operator().
Works with STL algorithms.
Allows custom behavior inside algorithms.
*/