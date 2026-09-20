#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

class ObAssign
{
    char *str;
    int len;

public:
    // Constructor
    ObAssign(char *s)
    {
        len = strlen(s);
        str = (char *)malloc(len + 1);
        strcpy(str, s);
    }
    // Copy Assignment Operator (deep copy)
    ObAssign &operator=(const ObAssign &obj)
    {
        // Check self-assignment
        if (this == &obj)
            return *this;
        // Free old memory
        free(str);
        // Allocate new memory
        str = (char *)malloc(obj.len + 1 + 1);
        // Copy string
        strcpy(str, obj.str);
        return *this;
    }

    // Destructor
    ~ObAssign()
    {
        cout << "Freeing memory" << endl;
        free(str);
    }

    // Display function
    void show()
    {
        cout << str << ":" << len << endl;
    }
};

int main()
{
    ObAssign ob1("Hello World"), ob2("like C++");
    ob1.show();
    ob2.show();
    ob2 = ob1; // Copy assignment operator called
    ob2.show();
    return 0;
}