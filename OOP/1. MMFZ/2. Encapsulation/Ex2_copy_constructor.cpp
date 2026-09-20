#include <iostream>
using namespace std;

class Box
{
private:
    double length;
    double width;
    double height;

public:
    // Constructor
    Box(double l, double w, double h)
    {
        length = l;
        width = w;
        height = h;
    }

    // Copy constructor
    Box(Box &ob)
    {
        length = ob.length;
        width = ob.width;
        height = ob.height;
    }

    // Setter functions
    void setLength(double l)
    {
        length = l;
    }

    void setWidth(double w)
    {
        width = w;
    }

    void setHeight(double h)
    {
        height = h;
    }

    // Getter functions
    double getLength()
    {
        return length;
    }

    double getWidth()
    {
        return width;
    }

    double getHeight()
    {
        return height;
    }

    double volume()
    {
        return length * width * height;
    }
};

int main()
{
    Box myBox(5, 3, 2);
    Box myClone(myBox);
    //myBox.setHeight(0);
    cout << "Box Volume: " << myBox.volume() << endl;
    cout << "Clone Volume: " << myClone.volume() << endl;
    return 0;
}