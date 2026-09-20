#include <iostream>
#include <fstream>
#include <string>
#include "listBST.hpp"
#define ll long long
using namespace std;

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
        return 1;
    }
    // TODO: Declare data structures to track bid statistics for each item
    // Start your code here
    ListBST<string, int> *TPrice = new ListBST<string, int>();
    ListBST<string, int> *TTotal = new ListBST<string, int>();
    ListBST<string, int> *TSucc = new ListBST<string, int>();
    ListBST<string, int>::T_Total = TTotal;
    ListBST<string, int>::T_Success = TSucc;
    ll Bids = 0, Succ = 0, Rej = 0;
    // End your code here

    int n;
    in_file >> n;
    for (int i = 0; i < n; ++i)
    {
        // TODO: Implement the logic to read initial items and their starting bids
        // Start your code here
        string id;
        int b;
        in_file >> id >> b;
        TPrice->insert(id, b);
        TTotal->insert(id, 0);
        TSucc->insert(id, 0);
        // End your code here
    }

    // TODO: Implement the logic to print the initial auction state
    // Start your code here
    cout << "Initial auction items:" << endl;
    TPrice->print('I');
    // End your code here
    cout << "\nAuction starts!\n\n";
    cout << "==============================\n";

    string op;
    while (in_file >> op)
    {
        // TODO: Implement the logic to process operations
        // Start your code here
        string id;
        ll x;
        if (op == "ADD")
        {
            in_file >> id >> x;
            if (TPrice->find(id))
            {
                if (x > TPrice->get(id))
                    TPrice->update(id, x);
            }
            else
            {
                TPrice->insert(id, x);
                TTotal->insert(id, 0);
                TSucc->insert(id, 0);
            }
            cout << "Item " << id << " added with starting bid " << x << endl;
            TPrice->print('I');
        }
        else if (op == "BID")
        {
            in_file >> id >> x;
            Bids++;
            if (!TPrice->find(id))
            {
                Rej++;
                cout << "Bid rejected. Item " << id << " not found." << endl;
            }
            else
            {
                // Increment Total Bids
                TTotal->update(id, TTotal->get(id) + 1);

                if (x > TPrice->get(id))
                {
                    // Success Case
                    Succ++;
                    TPrice->update(id, x);
                    TSucc->update(id, TSucc->get(id) + 1);
                    cout << "Bid of " << x << " on " << id << " accepted. Current bid: " << x << endl;
                }
                else
                {
                    // Reject Case
                    Rej++;
                    cout << "Bid of " << x << " on " << id << " rejected. Current bid: " << TPrice->get(id) << endl;
                }
            }
            TPrice->print('I');
        }
        else if (op == "CHECK")
        {
            in_file >> id;
            if (TPrice->find(id))
                cout << "Current bid for " << id << ": " << TPrice->get(id) << endl;
            else
                cout << "Item " << id << " not found." << endl;
            TPrice->print('I');
        }
        else if (op == "STATS")
        {
            in_file >> id;
            if (TPrice->find(id))
            {
                int t = TTotal->get(id);
                int s = TSucc->get(id);
                cout << "Statistics for " << id << ":" << endl;
                cout << "  Current highest bid: " << TPrice->get(id) << endl;
                cout << "  Total bids placed: " << t << endl;
                cout << "  Successful bids: " << s << endl;
                cout << "  Rejected bids: " << (t - s) << endl;
            }
            else
            {
                cout << "Item " << id << " not found." << endl;
            }
        }
        else if (op == "REPORT")
        {
            cout << "Auction Report:\nTotal items: " << TPrice->size() << "\nTotal bids placed: " << Bids << "\nTotal successful bids: " << Succ << "\nTotal rejected bids: " << Rej << "\n\nItem Statistics:" << endl;
            TPrice->print('R');
        }
        // End your code here
        cout << "==============================\n";
    }
    in_file.close();
    delete TPrice;
    delete TTotal;
    delete TSucc;
    return 0;
}