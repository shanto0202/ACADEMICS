#include <iostream>
using namespace std;

// class template with two type parameters
template <class Type1, class Type2>
class myclass
{
    Type1 i;
    Type2 j;

public:
    // constructor initializes both values
    myclass(Type1 a, Type2 b)
    {
        i = a;
        j = b;
    }

    void show()
    {
        cout << i << ' ' << j << '\n';
    }
};

int main()
{
    myclass<int, float> ob1(10, 0.23);                     // int and double
    myclass<char, char *> ob2('X', "Templates add power."); // char and string

    int c = 3;
    float p = 1.2;
    myclass Myclass(c, p);
    myclass Myclass1(3, "ifat"); //automatically detects

    ob1.show();
    ob2.show();
    
    Myclass.show();
    Myclass1.show();

    return 0;
}

/*
Key Notes:

1. Class templates can have multiple type parameters.
2. Syntax:
   template<class T1, class T2>
3. Objects specify the actual types during creation.
4. Example:
   myclass<int,double>
*/