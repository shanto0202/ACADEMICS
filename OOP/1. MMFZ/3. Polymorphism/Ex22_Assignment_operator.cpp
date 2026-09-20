#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

class strtype
{
    char *p;
    int len;

public:
    // strtype(char *s); // constructor
    strtype(char *s)
    {
        p = new char[strlen(s) + 1]; // dynamic memory allocation
        strcpy(p, s);
        len = strlen(s);
    }
    ~strtype()
    {
        delete[] p; // destructor (free memory)
    }
    char *get()
    {
        return p; // return stored string
    }
    strtype &operator=(strtype &ob) // overloaded assignment operator
    {
        p = new char[ob.len + 1]; // allocate new memory
        strcpy(p, ob.p);          // copy string
        return *this;             // return current object reference
    }
};

// constructor
// strtype::strtype(char *s)
// {
//     p = new char[strlen(s) + 1]; // dynamic memory allocation
//     strcpy(p, s);
//     len = strlen(s);
// }

// assignment operator overloading
// strtype &strtype::operator=(strtype &ob)
// {
//     p = new char[ob.len]; // allocate new memory
//     len = ob.len;
//     strcpy(p, ob.p); // copy string
//     return *this;    // return current object reference
// }

int main()
{

    strtype a("Hello"), b("There");

    cout << a.get() << " " << b.get() << endl;

    a = b; // assignment operator called

    cout << a.get() << " " << b.get() << endl;

    return 0;
}

/*
Key Notes:

1. Default assignment operator performs bitwise copy.
2. Bitwise copy is problematic when dynamic memory is used.
3. Both objects would point to the same memory (shallow copy).
4. Overloading operator= creates a deep copy of the object.
5. operator= should return reference (*this) to allow chaining:
      a = b = c;
*/