#include <iostream>
#include <cstring>
using namespace std;

class Rectangle
{
    char name[20];
    int length;
    int wide;

public:
    Rectangle(char *name, int length, int wide)
    {
        strcpy(this->name, name);
        this->length = length;
        this->wide = wide;
    }

    // conversion function: object → double
    operator double()
    {
        return length * wide; // returns area
    }

    // conversion function: object → char*
    operator char *()
    {
        return name; // returns rectangle name
    }
};

int main()
{

    Rectangle r("Rectangle", 5, 10);

    double area = r; // object converted to double
    cout << "Area: " << area << endl;

    char *name = r; // object converted to char*
    cout << "Name: " << name << endl;

    return 0;
}

/*
Key Notes:

1. Conversion function converts an object to another type.
2. Syntax:
       operator type(){ return value; }

3. operator double() converts Rectangle → double.
4. operator char*() converts Rectangle → char*.

5. Conversion happens automatically when needed.
   Example:
       double area = r;

6. Conversion functions have:
   - no return type
   - no parameters
*/