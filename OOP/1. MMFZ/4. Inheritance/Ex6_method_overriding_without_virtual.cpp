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
    void show()
    {
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
    fp->show(); // without virtual
}

/*
Key Notes:

1. Without virtual, function call is resolved by pointer type.

2. fp->show() calls Father::show() even when fp points to Son.

3. This is early binding.
*/