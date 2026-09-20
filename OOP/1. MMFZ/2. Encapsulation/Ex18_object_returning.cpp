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
        s = "\0";
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
    s.set("Hello world"); // dangling pointer
    return s;
}

int main()
{
    Samp ob;
    ob = input();
    ob.show();
    return 0;
}