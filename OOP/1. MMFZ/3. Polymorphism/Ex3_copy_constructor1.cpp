#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

class strtype
{
    char *p;

public:
    // Constructor: dynamically allocates memory and copies string
    strtype(const char *s)
    {
        int l;
        l = strlen(s) + 1;
        p = new char[l];
        if (!p)
        {
            cout << "Allocation error\n";
            exit(1);
        }
        strcpy(p, s);
    }

    // Destructor: frees dynamically allocated memory
    ~strtype()
    {
        delete[] p;
    }

    // Returns the pointer to stored string
    char *get()
    {
        return p;
    }
};

// Function receives object by value → invokes copy constructor
void show(strtype x)
{
    char *s;
    s = x.get(); // get string from object
    cout << s << endl;
}

int main()
{
    strtype a("Hello"), b("There");

    show(a); // object copy created
    show(b); // object copy created
    return 0;
}

/*
Key Notes:
1. Passing object by value calls the copy constructor.
2. Default copy constructor performs shallow copy.
3. Shallow copy copies the pointer address, not the actual data.
4. When destructors run, the same memory may be freed twice → runtime error.
5. Copy constructor is needed to perform deep copy for classes using dynamic memory.
*/