#include <cstring>
#include <iostream>
using namespace std;
class Father
{
    char *name;

public:
    Father(char *fname)
    {
        name = new char[strlen(fname) + 1];
        strcpy(name, fname);
    }
    virtual ~Father()
    { // virtual destructor
        delete name;
        cout << "Father destroyed" << endl;
    }
    virtual void show()
    {
        cout << "Father: " << name << endl;
    }
};

class Son : public Father
{
    char *name;

public:
    Son(char *sname, char *fname) : Father(fname)
    {
        name = new char[strlen(sname) + 1];
        strcpy(name, sname);
    }
    virtual ~Son()
    {
        delete name;
        cout << "Son destroyed" << endl;
    }
    virtual void show()
    {
        cout << "Son: " << name << endl;
    }
};

int main()
{
    Father *fp = new Father("Rashid");
    fp->show();
    delete fp;

    fp = new Son("Robin", "Rashid");
    fp->show();
    delete fp;
    return 0;
}

/*
Key Notes:

1. Virtual destructor ensures proper destructor chain.

2. Deleting derived object through base pointer is safe here.

3. Prevents memory/resource leak in polymorphic deletion.
*/