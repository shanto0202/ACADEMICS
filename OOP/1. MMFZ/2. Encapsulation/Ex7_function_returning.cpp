#include <iostream>
using namespace std;
int x;
int &f()
{
    return x;
}

int main()
{
    int x = 10;
    f() = 100;
    cout << "Local: " << x << "\nGlobal: " << ::x << endl; // local
    return 0;
}