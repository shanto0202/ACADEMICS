#include <cstring>
#include <iostream>
using namespace std;
class Father
{
    char name[20];

public:
    Father(char *fname)
    {
        strcpy(name, fname);
    }
    virtual void show()
    { // virtual enables overriding
        cout << "Father: " << name << endl;
    }
};

class Son : public Father
{
    char name[20];

public:
    Son(char *sname, char *fname) : Father(fname)
    {
        strcpy(name, sname);
    }
    void show()
    {
        cout << "Son: " << name << endl;
    }
};

int main()
{
    Father *fp, father("Rashid");
    Son son("Robin", "Rashid");
    fp = &father;
    fp->show();
    fp = &son;
    fp->show(); // with virtual
}

/*
Key Notes:

1. virtual enables runtime binding.

2. When fp points to Son, Son::show() is called.

3. This is runtime polymorphism.
*/