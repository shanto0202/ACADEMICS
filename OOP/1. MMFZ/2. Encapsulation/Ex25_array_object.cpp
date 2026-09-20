#include <iostream>
#include <string>
using namespace std;

/* ---------- Class Sa ---------- */
class Sa
{
    int a;

public:
    Sa(int n)
    {
        a = n;
    }

    int getA()
    {
        return a;
    }
};

/* ---------- Class Da ---------- */
class Da
{
    string name;
    int b;

public:
    Da(string nam, int n)
    {
        name = nam;
        b = n;
    }

    void show()
    {
        cout << "(" << name << ", " << b << ")" << endl;
    }
};

/* ---------- Main ---------- */
int main()
{
    Sa s1[4] = {10, 20, 30, 40};
    Sa s2[4] = {Sa(50), Sa(60), Sa(70), Sa(80)};
    Sa s3[3][2] = {{11, 12}, {21, 22}, {31, 32}};
    Sa s4[3][2] = {{Sa(41), Sa(42)}, {Sa(51), Sa(52)}, {Sa(61), Sa(62)}};

    Da ob[4] = {Da("A", 10), Da("B", 20), Da("C", 30), Da("D", 40)};

    for (int i = 0; i < 4; i++)
    {
        cout << "s1[" << i << "] = " << s1[i].getA() << "   ";
        cout << "s2[" << i << "] = " << s2[i].getA() << endl;
        ob[i].show();
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cout << "s3[" << i << "][" << j << "] = " << s3[i][j].getA() << "   ";
            cout << "s4[" << i << "][" << j << "] = " << s4[i][j].getA() << endl;
        }
    }
    return 0;
}

/*
Key Notes:
1. Array of objects → multiple objects of a class stored in an array.
2. Objects can be initialized directly or using constructors.
3. Syntax: ClassName obj[size];
4. Multi-dimensional arrays of objects are also possible.
5. Object methods are accessed using dot operator (obj[i].method()).
*/