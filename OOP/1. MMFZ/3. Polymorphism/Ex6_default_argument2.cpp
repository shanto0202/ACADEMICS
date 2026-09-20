#include <iostream>
using namespace std;

// function with default argument
double rect_area(double length, double width = 0)
{
    if (width == 0)
        width = length; // if width not given → square
    return length * width;
}

int main()
{
    cout << rect_area(10.0, 5.8) << endl; // both values
    cout << rect_area(10.0) << endl;      // default width used
    return 0;
}

/*
Key Notes:
1. Default arguments can replace some function overloading.
2. Default values must be on the rightmost parameters.
3. Provided argument overrides default value.
*/