#include <iostream>
#include <utility>
using namespace std;

int main()
{
    pair<int, char> PAIR1;

    pair<string, double> PAIR2("GeeksForGeeks", 1.23);

    pair<string, double> PAIR3;

    PAIR1.first = 100;
    PAIR1.second = 'G';

    PAIR3 = make_pair("GeeksForGeeks is Best", 4.56);

    cout << PAIR1.first << " ";
    cout << PAIR1.second << endl;

    cout << PAIR2.first << " ";
    cout << PAIR2.second << endl;

    cout << PAIR3.first << " ";
    cout << PAIR3.second << endl;
    return 0;
}

/*
Key Notes
---------
pair stores two values together.
first and second access the values.
make_pair() creates pair easily.
Defined in <utility>.
*/

/*
vector<pair<int, int>> v;

     insert pairs
    v.push_back({1, 2});
    v.push_back({3, 4});
    v.push_back({5, 6});

*/
