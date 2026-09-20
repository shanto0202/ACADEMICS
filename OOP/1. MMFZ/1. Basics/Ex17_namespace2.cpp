// Example 2: Using specific names from std namespace

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    string str;

    cout << "Enter a string: ";
    getline(cin, str);
    cout << str << endl;

    return 0;
}