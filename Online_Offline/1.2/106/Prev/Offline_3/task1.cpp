#include <iostream>
#include <fstream>
#include <string>
#include "listBST.hpp"
using namespace std;
//g++ task2.cpp -o task2.exe
//./task1 in_task1.txt > myout.task1.txt

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cerr << "Usage: filename" << "\n";
        return 1;
    }
    ifstream in_file(argv[1]);
    if (!in_file)
    {
        cerr << "Unable to open file\n";
        return 2;
    }

    char c, str[5];
    int value;
    BST<int, int> *bst = new ListBST<int, int>();

    if (!bst)
    {
        cerr << "Memory allocation failed\n";
        return 3;
    }

    while (in_file >> c)
    {
        if (c == 'F')
        {
            int koi;
            in_file >> koi;
            if (bst->find(koi))
                cout << "Key " << koi << " found in BST." << endl;
            else
                cout << "Key " << koi << " not found in BST." << endl;
        }
        else if (c == 'E')
        {
            if (bst->empty())
                cout << "Empty" << endl;
            else
                cout << "Not Empty" << endl;
        }
        else if (c == 'I')
        {
            int koi;
            in_file >> koi;
            if (bst->insert(koi, koi))
                cout << "Key " << koi << " inserted into BST, ";
            else
                cout << "Insertion failed! Key " << koi << " already exists in BST, ";
            bst->print();
        }
        else if (c == 'D')
        {
            int koi;
            in_file >> koi;
            if (bst->remove(koi))
                cout << "Key " << koi << " removed from BST, ";
            else
                cout << "Removal failed! Key " << koi << " not found in BST, ";
            bst->print();
        }
        else if (c == 'M')
        {
            string which;
            in_file >> which;
            if (which == "Min")
            {
                if (!bst->empty())
                    cout << "Minimum value: " << bst->find_min() << endl;
            }
            else if (which == "Max")
            {
                if (!bst->empty())
                    cout << "Maximum value: " << bst->find_max() << endl;
            }
        }
        else if (c == 'T')
        {
            string t;
            in_file >> t;
            if (t == "In")
                bst->print('I');
            else if (t == "Pre")
                bst->print('P');
            else if (t == "Post")
                bst->print('O');
        }
        else if (c == 'S')
        {
            cout << "Size: " << bst->size() << endl;
        }
    }
    in_file.close();
    delete bst;
    return 0;
}