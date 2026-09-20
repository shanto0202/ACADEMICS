#include <iostream>
#include <cstdio>
using namespace std;

class date
{
    int month, day, year;

public:
    date(char *str);
    date(int d, int m, int y)
    {
        day = d;
        month = m;
        year = y;
    }

    void show()
    {
        cout << day << '/' << month << '/';
        cout << year << '\n';
    }
};

date::date(char *str)
{
    sscanf(str, "%d%*c%d%*c%d", &day, &month, &year);
}

int main()
{
    date sdate("31/12/99");
    date idate(31, 12, 99);
    sdate.show();
    idate.show();
    return 0;
}