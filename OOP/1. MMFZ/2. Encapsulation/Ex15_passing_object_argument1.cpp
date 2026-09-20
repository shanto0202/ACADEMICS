#include <iostream>
#include <cstdlib>
using namespace std;

class ObArgProb
{
    int *p;

public:
    ObArgProb(int n)
    {
        p = (int *)malloc(sizeof(int));
        *p = n;
        cout << "Constructing..." << endl;
    }
    ~ObArgProb()
    {
        cout << "Destructing..." << endl;
        free(p);
    }
    int getP()
    {
        return *p;
    }
};

int negateP(ObArgProb ob)
{
    return -ob.getP();
}

int main()
{
    ObArgProb ob1(10);
    cout << "Before: " << ob1.getP() << endl;
    cout << "Result: " << negateP(ob1) << endl;
    cout << "After: " << ob1.getP() << endl;
    return 0;
}