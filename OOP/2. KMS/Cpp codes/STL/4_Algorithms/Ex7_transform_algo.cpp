// An example of transform algorithm.

#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

// transformation function
double reciprocal(double i)
{
    return 1.0 / i;
}

int main()
{

    list<double> vals;

    int i;

    for (i = 1; i < 10; i++)
        vals.push_back((double)i);

    list<double>::iterator p;

    // transform list values
    p = transform(vals.begin(), vals.end(), vals.begin(), reciprocal);
    /*
      vals.begin()	start
      vals.end()	end
      vals.begin()	overwrite same list
      reciprocal	function
    */
    // You didn’t really need to store it here.
    cout << "Transformed contents of vals:\n";

    p = vals.begin();

    while (p != vals.end())
    {

        cout << *p << " ";

        p++;
    }

    return 0;
}

/*
Key Notes
---------
transform applies function to each element.
Result can overwrite same container.
Function must match element type.
*/