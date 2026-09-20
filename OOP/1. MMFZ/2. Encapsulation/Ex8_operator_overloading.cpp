#include <iostream>
using namespace std;

class Coord
{
    int x, y;

public:
    Coord(int a, int b)
    {
        x = a;
        y = b;
    }

    Coord &operator++()
    {
        x++;
        y++;
        return *this;
    }

    void show()
    {
        cout << "(" << x << "," << y << ")" << endl;
    }
};

int main()
{
    Coord P(10, 20);
    P.show();
    ++P;
    P.show();
    //P++;
    //P.show();
    return 0;
}