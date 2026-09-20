#include <iostream>
using namespace std;

class myclass
{
    int x;

public:
    // Default constructor
    myclass()
    {
        x = 0;
    }

    // Parameterized constructor
    myclass(int n)
    {
        x = n;
    }

    int getx()
    {
        return x;
    }
};

int main()
{
    myclass o1[5];                   // uses default constructor
    myclass o2[5] = {1, 2, 3, 4, 5}; // uses parameterized constructor

    for (int i = 0; i < 5; i++)
    {
        cout << o1[i].getx() << " ";
        cout << o2[i].getx() << endl;
    }
    
    return 0;
}

/*
Key Notes:
1. Constructor Overloading → multiple constructors with different parameters.
2. Default constructor → no parameter.
3. Parameterized constructor → accepts arguments.
4. Used for flexibility in object initialization.
5. Destructor cannot be overloaded in C++.
*/