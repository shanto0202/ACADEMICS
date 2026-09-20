// Demonstrate count_if()

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/* Unary predicate that checks divisibility by 3 */
bool dividesBy3(int i)
{
    if ((i % 3) == 0)
        return true;
    return false;
}

int main()
{

    vector<int> v;
    int i;

    for (i = 1; i < 20; i++)
        v.push_back(i);

    cout << "Sequence:\n";

    for (i = 0; i < v.size(); i++)
        cout << v[i] << " ";

    cout << endl;

    i = count_if(v.begin(), v.end(), dividesBy3);

    cout << i << " numbers are divisible by 3.\n";

    return 0;
}

/*
Key Notes
---------
count_if counts elements satisfying condition.
Predicate function returns true/false.
Common in filtering operations.
*/