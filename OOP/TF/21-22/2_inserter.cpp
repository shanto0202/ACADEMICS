#include <iostream>
using namespace std;

class myclass
{
    int x, y;

public:
    myclass(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    friend ostream &operator<<(ostream &out, const myclass &ob);
};

ostream &operator<<(ostream &out, const myclass &ob)
{
    out << "x: " << ob.x << ", y: " << ob.y;
    return out;
}

int main()
{
    myclass ob(120, 130);
    cout << ob;
    return 0;
}