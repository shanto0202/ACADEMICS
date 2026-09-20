#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

string removeText(string &str)
{
    size_t pos = 0;
    if ((pos = str.find("Sheikh Hasina")) != string::npos)
        str.erase(pos, 14);
    return str;
}

int main()
{

    vector<string> strings = {

        "Sheikh Hasina National Institute of Burn and Plastic Surgery",
        "Sheikh Hasina National Youth Center",
        "Gangachara Sheikh Hasina Bridge"};

    transform(strings.begin(), strings.end(), strings.begin(), removeText);
    // for_each(strings.begin(), strings.end(), removeText);

    sort(strings.begin(), strings.end());

    for (auto &str : strings)
        cout << str << endl;

    return 0;
}

/*
Expected Output
---------------
Gangachara Bridge
National Institute of Burn and Plastic Surgery
National Youth Center

Key Notes
---------
find() locates substring.
erase(pos,len) removes substring.
for_each applies function to all strings.
sort sorts lexicographically.
*/