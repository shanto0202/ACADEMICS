#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

class Samp
{
    char *s;

public:
    Samp()
    {
        s = nullptr;
    }
    // Copy Assignment Operator
    Samp &operator=(const Samp &ob)
    {
        if (this == &ob)
        {
            return *this;
        }
        s = (char *)malloc(strlen(ob.s) + 1);
        strcpy(s, ob.s);
        return *this;
    }
    ~Samp()
    {
        free(s);
        cout << "Freeing S" << endl;
    }
    void show()
    {
        cout << s << endl;
    }
    void set(char *str)
    {
        s = (char *)malloc(strlen(str) + 1);
        strcpy(s, str);
    }
};

Samp input()
{
    Samp s;
    s.set((char *)"Hello, world!");
    return s;
}

int main()
{
    Samp ob;
    ob = input();
    ob.show();
    return 0;
}