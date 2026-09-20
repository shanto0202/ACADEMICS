#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{

    char str[] = "Atik is gay.";

    vector<char> v, v2(30);
    // v2[0]=5;

    unsigned int i;

    for (i = 0; str[i]; i++)
        v.push_back(str[i]);

    // demonstrate remove_copy

    cout << "Input sequence:\n";

    for (i = 0; i < v.size(); i++)
        cout << v[i];

    cout << endl;

    // remove spaces
    remove_copy(v.begin(), v.end(), v2.begin(), ' ');

    cout << "Result after removing spaces:\n";

    for (i = 0; i < v2.size(); i++)
        cout << v2[i];

    cout << endl;

    // demonstrate replace_copy

    cout << "Input sequence:\n";

    for (i = 0; i < v.size(); i++)
        cout << v[i];

    cout << endl;

    // replace spaces with colons
    replace_copy(v.begin(), v.end(), v2.begin(), ' ', ':');

    cout << "Result after replacing spaces with colons:\n";

    for (i = 0; i < v2.size(); i++)
        cout << v2[i];
    //reverse(v.begin(), v.end());
    cout << endl;

    return 0;
}

/*
Key Notes
---------
remove_copy copies elements except specified value.
replace_copy copies while replacing values.
Destination container must have enough space.
*/