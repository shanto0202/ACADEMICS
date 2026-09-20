#include <bits/stdc++.h>
using namespace std;
#include "arrayList.h"
// #include "linkedList.h"

int main()
{
    FILE *file = fopen("in.txt", "r");
    if (file == NULL)
    {
        return 1;
    }
    ArrayList list;
    // DoublyLinkedList list;
    int x, yo, yoyo;

    while (fscanf(file, "%d", &x) == 1 && x != 0)
    {
        if (x == 1 && fscanf(file, "%d", &yo) == 1)
        {
            cout << "Insert " << yo << endl;
            list.insert(yo);
            list.print();
        }
        else if (x == 2)
        {
            cout << "Delete current item" << endl;
            int ret = list.delete_cur();
            if (ret >= 0)
            {
                list.print();
                cout << ret << " is deleted" << endl;
            }
            else
            {
                cout << "List is empty" << endl;
            }
        }
        else if (x == 3 && fscanf(file, "%d", &yo) == 1)
        {
            cout << "Append " << yo << endl;
            list.append(yo);
            list.print();
        }
        else if (x == 4)
        {
            cout << "Size of the list is " << list.size() << endl;
        }
        else if (x == 5 && fscanf(file, "%d", &yo) == 1)
        {
            cout << "Prev " << yo << endl;
            list.prev(yo);
            list.print();
        }
        else if (x == 6 && fscanf(file, "%d", &yo) == 1)
        {
            cout << "Next " << yo << endl;
            list.next(yo);
            list.print();
        }
        else if (x == 7 && fscanf(file, "%d", &yo) == 1)
        {
            if (list.is_present(yo))
                cout << yo << " is present" << endl;
            else
                cout << yo << " is not present" << endl;
        }
        else if (x == 8)
        {
            cout << "Clear list" << endl;
            list.clear();
            list.print();
        }
        else if (x == 9 && fscanf(file, "%d", &yo) == 1)
        {
            cout << "Delete " << yo << endl;
            int ret = list.delete_item(yo);
            if (ret == -1)
                cout << yo << " not found" << endl;
            else
            {
                list.print();
            }
        }
        else if (x == 10 && fscanf(file, "%d %d", &yo, &yoyo) == 2)
        {
            cout << "Swap index " << yo << " and " << yoyo << endl;
            list.swap_ind(yo, yoyo);
            list.print();
        }
        else if (x == 11 && fscanf(file, "%d", &yo) == 1)
        {
            cout << "Search " << yo << endl;
            int idx = list.search(yo);
            if (idx == -1)
                cout << yo << " is not found" << endl;
            else
            {
                list.print();
                cout << yo << " is found at " << idx << endl;
            }
        }
        else if (x == 12 && fscanf(file, "%d", &yo) == 1)
        {
            cout << "Find " << yo << endl;
            int val = list.find(yo);
            if (val == -1)
                cout << yo << " is not a valid index" << endl;
            else
            {
                list.print();
                cout << val << " is found at " << yo << endl;
            }
        }
        else if (x == 13 && fscanf(file, "%d %d", &yo, &yoyo) == 2)
        {
            cout << "Update element at " << yo << endl;
            int ret = list.update(yo, yoyo);
            if (ret == -1)
                cout << yo << " is not a valid index" << endl;
            else
            {
                list.print();
                cout << ret << " is updated by " << yoyo << endl;
            }
        }
        else if (x == 14)
        {
            cout << "Trim" << endl;
            int ret = list.trim();
            list.print();
            cout << ret << " removed" << endl;
        }
        else if (x == 15)
        {
            cout << "Reverse" << endl;
            list.reverse();
            list.print();
        }
    }

    cout << "End" << endl;
    fclose(file);
    return 0;
}