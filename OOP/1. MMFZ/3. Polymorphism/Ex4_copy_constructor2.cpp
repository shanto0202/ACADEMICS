#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

class strtype
{
    char *p;

public:
    // Normal constructor: allocates memory and copies string
    strtype(const char *s)
    {
        int l;
        l = strlen(s) + 1;
        p = new char[l];
        strcpy(p, s);
        cout << "Constructing normally\n";
    }

    // Copy Constructor: creates deep copy of object
    strtype(const strtype &s)
    {
        p = new char[strlen(s.p) + 1];
        strcpy(p, s.p);
        cout << "Constructing copy\n";
    }

    // Destructor: frees allocated memory
    ~strtype()
    {
        delete[] p;
    }

    // Returns stored string
    char *get()
    {
        return p;
    }
};

// Passing object by value → invokes copy constructor
void show(strtype x)
{
    char *s;
    s = x.get();
    cout << s << endl;
}

int main()
{
    strtype a("Hello"), b("There");

    show(a); // temporary object created → copy constructor called
    show(b);

    return 0;
}

/*
Key Notes:
1. Copy constructor creates a new object as a copy of another object.
2. It is called when:
   - An object is passed by value to a function.
   - An object is returned from a function.
   - An object is initialized with another object.
3. Default copy constructor performs shallow copy.
4. Custom copy constructor performs deep copy (allocates new memory).
5. Java does NOT have copy constructors; it uses object references instead.
*/