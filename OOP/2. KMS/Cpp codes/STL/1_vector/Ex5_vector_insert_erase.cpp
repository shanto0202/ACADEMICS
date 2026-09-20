#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<char> v(10);
    vector<char> v2;

    char str[] = "Vector";

    unsigned int i;

    // initialize vector
    for (i = 0; i < 10; i++)
        v[i] = i + 'a';

    // fill second vector
    for (i = 0; str[i]; i++)
        v2.push_back(str[i]);

    cout << "Original contents of v:\n";
    for (i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << "\n\n";

    vector<char>::iterator p = v.begin();
    p += 2; // point to third element

    // insert elements
    v.insert(p, 'X'); // (starting, times, element)
    // v.insert(p,10, 'X');

    cout << v.size() << endl;

    cout << "Contents after insert:\n";
    for (i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << "\n\n";

    // erase inserted elements
    p = v.begin();
    p += 2;
    // 2-7 a b c d e f g h i j
    v.erase(p, p + 5); // O(n)

    cout << v.size() << endl;

    cout << "Contents after erase:\n";
    for (i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << "\n\n";

    // insert another vector
    // v2 = Vector
    v.insert(p, v2.begin(), v2.end());

    cout << "Size after v2 insertion = ";
    cout << v.size() << endl;

    cout << "Contents after insert:\n";
    for (i = 0; i < v.size(); i++)
        cout << v[i] << " ";

    cout << endl;

    return 0;
}

/*
Key Notes:

1. insert() adds elements at a specified position.
2. erase() removes elements from vector.
3. Iterator determines where operations occur.
4. Vector automatically shifts elements after insert or erase.
5. Other container ranges can also be inserted.
*/