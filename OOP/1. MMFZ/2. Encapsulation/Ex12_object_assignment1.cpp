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
    ObAssign(const char *s)
    {
        len = strlen(s);
        str = (char *)malloc(len + 1); // dynamic memory allocation
        strcpy(str, s);
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
    ObAssign ob1("Hello World"), ob2("I like C++");
    //  ob1.show();
    //  ob2.show();
    //  ob2 = ob1; // Problem occurs here (shallow copy)
    //  ob2.show();

    // Use of Pointer
    ObAssign *ob3 = new ObAssign("Hello World");
    ObAssign *ob4 = new ObAssign("Like C++");
    ob3->show();
    ob4->show();
    //ObAssign *temp = ob4;
    ob4 = ob3;
    ob4->show();
    //No Execution of Destructor
    delete ob3;
    delete ob4;
    return 0;
}