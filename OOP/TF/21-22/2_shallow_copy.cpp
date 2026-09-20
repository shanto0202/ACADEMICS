#include <iostream>
#include <cstring>
using namespace std;

class strtype
{
    char *p;
    int len;

public:
    strtype(char *s)
    {
        len = strlen(s) + 1;
        p = new char[len];
        strcpy(p, s);
    }

    ~strtype()
    {
        delete[] p;
    }

    void show()
    {
        cout << p << endl;
    }

    strtype &operator=(const strtype &ob)
    {
        if (this == &ob) // self-assignment check
            return *this;

        delete[] p; // free old memory

        len = ob.len;
        p = new char[len]; // allocate new memory
        strcpy(p, ob.p);   // copy contents

        return *this;
    }
};

int main()
{
    strtype s1((char *)"LEVEL"), s2((char *)"TERM");

    s1 = s2;

    s1.show();
    s2.show();

    return 0;
}