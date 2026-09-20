#include <iostream>
using namespace std;

template <class T>
class Gen
{
    T val;

public:
    Gen(T v)
    {
        val = v;
    } // constructor storing generic value

    T getval()
    {
        return val;
    } // return stored value
};

int main()
{

    Gen<int> iob(88);       // template with int
    Gen<double> dob(22.22); // template with double
    Gen<char> cob('X');     // template with char

    cout << "Value: " << iob.getval() << endl;
    cout << "Value: " << dob.getval() << endl;
    cout << "Value: " << cob.getval() << endl;

    return 0;
}

/*
Key Notes:

1. Template class allows one class to work with multiple data types.

2. template<class T> → T represents a generic data type.

3. Objects specify the type when created:
      Gen<int>, Gen<double>, Gen<char>

4. Improves code reusability.
*/