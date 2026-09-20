#include <iostream>
using namespace std;

int divide()
{
    int d = 0;

    if (d == 0)
        throw runtime_error("Division by zero error");

    return 10 / d;
}

int main()
{
    try
    {
        cout << divide() << endl;
    }
    catch (runtime_error &e)
    {
        cout << e.what() << endl;
    }

    return 0;
}

/*
Key Notes:

1. throw → used to signal error
2. try → wrap risky code
3. catch → handles exception
4. prevents program crash
*/