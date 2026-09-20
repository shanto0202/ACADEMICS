// Include header files as required
#include <bits/stdc++.h>
using namespace std;
#define ll long long
//===============================================================
class PartyMember
{
    int member_id;        // a unique ID assigned to each member by the political party
    string name;          // name of the member
    ll asset_value;       // net asset of the member
    string nominated_for; // name of the constituency if this member is nominated by his party for running election
    // You are not allowed to add any other member variable in this class
    
public:
    // Write a default constructor for this class. Initialize data members as deem appropriate.
    PartyMember(string Name, ll asset)
    {
        name = Name;
        asset_value = asset;
        nominated_for = "";
    }

    // Write other parameterize constructors as required.

    // Write the setter functions for this class
    void setMemberId(int id)
    {
        member_id = id;
    }
    void setNominatedFor(string constituency)
    {
        nominated_for = constituency;
    }
    // Write the getter functions for this class
    string getName()
    {
        return name;
    }
    ll getAssetValue()
    {
        return asset_value;
    }
    int getMemberId()
    {
        return member_id;
    }
    string getNominatedFor()
    {
        return nominated_for;
    }

    void show_member_details()
    {
        cout << "ID: " << member_id << ", Name: " << name << ", Asset: " << asset_value << ", Constituency: " << nominated_for << endl
             << endl;
        // Print member details in the format shown in the given sample output
    }
    // Add any other helper functions as required
};
//===============================================================
class PoliticalParty
{
    string name;                // name of the political party
    PartyMember *members[1000]; // Array of pointers to PartyMember objects; Allocate an object to a pointer when a member is added. Assume that there will be at most 1000 members in a party
    int member_count;           // count of members in the party
    int next_id;                // next ID to assign
    // Add other member variables as required and justified

public:
    // Write a copy constructor for this class
    PoliticalParty(string party)
    {
        name = party;
        member_count = 0;
        next_id = 1;
    }
    // Write other parameterize constructors as required

    // Write a destructor for this class
    ~PoliticalParty()
    {
        for (int i = 0; i < member_count; i++)
        {
            delete members[i];
        }
    }
    // Write setter functions for this class
    void setName(string n)
    {
        name = n;
    }

    // Write getter functions for this class
    string getName()
    {
        return name;
    }
    int getMemberCount()
    {
        return member_count;
    }

    PartyMember search_member(string constituency)
    {
        for (int i = 0; i < member_count; i++)
        {
            if (members[i]->getNominatedFor() == constituency)
            {
                return *members[i];
            }
        }
        // Returns the member nominated for the given constituency. If not found, return an empty object.
        return PartyMember("", 0);
    }

    void join_party(PartyMember m)
    {
        members[member_count] = new PartyMember(m);
        members[member_count]->setMemberId(next_id);
        next_id++;
        member_count++;
        // Add the member m to this party. Assign id sequentially to the new member.
    }

    void join_party(PoliticalParty &pp)
    {
        for (int i = 0; i < pp.member_count; i++)
        {
            pp.members[i]->setNominatedFor(""); // Cancel nomination from old party
            members[member_count] = new PartyMember(*pp.members[i]);
            members[member_count]->setMemberId(next_id);
            next_id++;
            member_count++;
            delete pp.members[i];
            pp.members[i] = nullptr;
        }
        pp.member_count = 0; // Remove all members from pp
        // Add all the members of pp to this party and remove them from pp. Assign ids sequentially to the new members in this party. When a member joins from one party to another, his nomination, if given, from the old party is automatically cancelled.
    }

    void leave_party(int id)
    {
        for (int i = 0; i < member_count; i++)
        {
            if (members[i]->getMemberId() == id)
            {
                delete members[i];
                for (int j = i; j < member_count - 1; j++)
                {
                    members[j] = members[j + 1];
                }
                members[member_count - 1] = nullptr;
                member_count--;
                break;
            }
        }
        // Remove the member with the given id from this party. Rearrange the list such that all the members are consecutive, i.e., there is no hole in the list. When a member leaves a party, his id is never reused.
    }

    void nominate_member(int id, string constituency)
    {
        for (int i = 0; i < member_count; i++)
        {
            if (members[i]->getMemberId() == id)
            {
                members[i]->setNominatedFor(constituency);
                break;
            }
        }
        // Nominate the member with given id for the constituency
    }
    void show_nominated_members()
    {
        cout << "Nominated members for " << name << endl;
        for (int i = 0; i < member_count; i++)
        {
            if (members[i]->getNominatedFor() != "")
            {
                cout << "ID: " << members[i]->getMemberId() << ", Name: " << members[i]->getName() << ", Asset: " << members[i]->getAssetValue() << ", Constituency: " << members[i]->getNominatedFor() << endl;
            }
        }
        // Show details of the members nominated for the election. Match the format as given in the expected output.
    }

    void cancel_nomination(int id)
    {
        for (int i = 0; i < member_count; i++)
        {
            if (members[i]->getMemberId() == id)
            {
                members[i]->setNominatedFor("");
                break;
            }
        }
        // Cancel nomination of the member with the given id
    }

    PoliticalParty form_new_party(string partyName)
    {
        PoliticalParty newParty(partyName);
        for (int i = 0; i < member_count;)
        {
            if (members[i]->getNominatedFor() == "")
            {
                newParty.join_party(*members[i]);
                leave_party(members[i]->getMemberId());
            }
            else
            {
                i++;
            }
        }
        return newParty;
        // Form a new party with the members who have been denied nomination	from this party
    }

    void show_all_members()
    {
        cout << "Members of " << name << ":" << endl;
        if (member_count == 0)
        {
            cout << "No members found." << endl;
            return;
        }
        for (int i = 0; i < member_count; i++)
        {
            cout << "ID: " << members[i]->getMemberId() << ", Name: " << members[i]->getName() << ", Asset: " << members[i]->getAssetValue();
            if (members[i]->getNominatedFor() != "")
            {
                cout << ", Constituency: " << members[i]->getNominatedFor() << endl;
            }
            else
            {
                cout << endl;
            }
        }
        // Print details info of all the members of this party in the format shown in the given expected output
    }

    // Add any other helper function as required and justified
};
//=======================================
int main()
{
    PartyMember abc1("Mr. A", 100000000);
    PartyMember abc2("Mr. B", 4000000);
    PartyMember abc3("Mr. C", 20000000);
    PoliticalParty p1("ABC");
    p1.join_party(abc1);
    p1.join_party(abc2);
    p1.join_party(abc3);
    p1.show_all_members();

    p1.nominate_member(1, "DHK-10");
    PartyMember pm = p1.search_member("DHK-10");
    cout << endl
         << "Details of the member nominated for DHK-10 constituency:" << endl;
    pm.show_member_details();

    p1.nominate_member(2, "CUM-3");
    p1.nominate_member(3, "SYL-1");
    p1.show_nominated_members();

    PartyMember xyz1("Mr. X", 1000000);
    PartyMember xyz2("Mr. Y", 3000000);

    PoliticalParty p2("XYZ");
    p2.join_party(xyz1);
    p2.join_party(xyz2);
    p2.show_all_members();

    p1.join_party(p2);
    p1.show_all_members();
    p2.show_all_members();

    PartyMember xyz3("Mr. Z", 5000000);
    p2.join_party(xyz3);
    p2.show_all_members();

    p1.cancel_nomination(1);
    p1.cancel_nomination(3);
    p1.nominate_member(4, "CUM-3");
    p1.nominate_member(5, "SYL-1");
    p1.show_nominated_members();

    PoliticalParty p3 = p1.form_new_party("Renegades");
    p1.show_all_members();
    p3.show_all_members();
}

/* Expected Output
Members of ABC:
ID: 1, Name: Mr. A, Asset: 100000000
ID: 2, Name: Mr. B, Asset: 4000000
ID: 3, Name: Mr. C, Asset: 20000000

Details of the member nominated for DHK-10 constituency:
ID: 1, Name: Mr. A, Asset: 100000000, Constituency: DHK-10

Nominated Members of ABC:
ID: 1, Name: Mr. A, Asset: 100000000, Constituency: DHK-10
ID: 2, Name: Mr. B, Asset: 4000000, Constituency: CUM-3
ID: 3, Name: Mr. C, Asset: 20000000, Constituency: SYL-1

Members of XYZ:
ID: 1, Name: Mr. X, Asset: 1000000
ID: 2, Name: Mr. Y, Asset: 3000000

Members of ABC:
ID: 1, Name: Mr. A, Asset: 100000000, Constituency: DHK-10
ID: 2, Name: Mr. B, Asset: 4000000, Constituency: CUM-3
ID: 3, Name: Mr. C, Asset: 20000000, Constituency: SYL-1
ID: 4, Name: Mr. X, Asset: 1000000
ID: 5, Name: Mr. Y, Asset: 3000000

Members of XYZ:
No members found.

Members of XYZ:
ID: 3, Name: Mr. Z, Asset: 5000000

Nominated Members of ABC:
ID: 2, Name: Mr. B, Asset: 4000000, Constituency: CUM-3
ID: 4, Name: Mr. X, Asset: 1000000, Constituency: CUM-3
ID: 5, Name: Mr. Y, Asset: 3000000, Constituency: SYL-1

Members of ABC:
ID: 2, Name: Mr. B, Asset: 4000000, Constituency: CUM-3
ID: 4, Name: Mr. X, Asset: 1000000, Constituency: CUM-3
ID: 5, Name: Mr. Y, Asset: 3000000, Constituency: SYL-1

Members of Renegades:
ID: 1, Name: Mr. A, Asset: 100000000
ID: 2, Name: Mr. C, Asset: 20000000
*/