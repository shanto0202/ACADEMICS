#include <iostream>
#include <list>
using namespace std;

class myclass
{
    int a, b, sum;

public:
    myclass()
    {
        a = b = 0;
    }

    myclass(int i, int j)
    {
        a = i;
        b = j;
        sum = a + b;
    }

    int getsum()
    {
        return sum;
    }

    friend bool operator<(const myclass &o1, const myclass &o2)
    {
        return o1.sum < o2.sum;
    }

    friend bool operator>(const myclass &o1, const myclass &o2)
    {
        return o1.sum > o2.sum;
    }

    friend bool operator==(const myclass &o1, const myclass &o2)
    {
        return o1.sum == o2.sum;
    }

    friend bool operator!=(const myclass &o1, const myclass &o2)
    {
        return o1.sum != o2.sum;
    }
};

int main()
{
    int i;

    list<myclass> lst1; // create first list

    for (i = 0; i < 10; i++)
        lst1.push_back(myclass(i, i));

    cout << "First list: ";

    list<myclass>::iterator p = lst1.begin();

    while (p != lst1.end())
    {
        cout << p->getsum() << " ";
        p++;
    }

    cout << endl;

    list<myclass> lst2; // create second list

    for (i = 0; i < 10; i++)
        lst2.push_back(myclass(i * 2, i * 3));

    cout << "Second list: ";

    p = lst2.begin();

    while (p != lst2.end())
    {
        cout << p->getsum() << " ";
        p++;
    }

    cout << endl;

    lst1.merge(lst2); // merge lists

    cout << "Merged list: ";

    p = lst1.begin();

    while (p != lst1.end())
    {
        cout << p->getsum() << " ";
        p++;
    }

    return 0;
}

/*
Key Notes
---------
list can store objects.
Operator overloading required for comparisons.
merge() uses comparison operators.
Access object members using iterator -> operator.
*/