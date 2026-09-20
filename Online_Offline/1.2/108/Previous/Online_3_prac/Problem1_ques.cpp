#include <iostream>
#include <string>
#include <iomanip>
#include <fstream> // for file handling

using namespace std;

//**************** ****************************************************************** **********************/
//**************** 'Cricketer' class represents a general cricketer. Do not change!!! **********************/
//****************   You can not add any other properties or methods in any classes   **********************/
//**************** ****************************************************************** **********************/
class Cricketer
{
protected:
    int matchPlayed;
    string name;
    int age;

public:
    // constructor to initialize name, age, and matches played
    Cricketer(string s = "Unknown", int a = 0, int m = 0) : name(s), age(a), matchPlayed(m)
    {
    }

    string getName()
    {
        return name;
    }
    int getMatchPlayed()
    {
        return matchPlayed;
    }
    int getAge()
    {
        return age;
    }
    void setName(string n)
    {
        name = n;
    }
    void setAge(int a)
    {
        age = a;
    }
    void setMatchPlayed(int m)
    {
        matchPlayed = m;
    }

    // Prints basic cricketer info
    virtual void printInfo(ofstream &out)
    {
        out << "Name: " << name << ", Age: " << age << ", Matches Played: " << matchPlayed << endl;
    }

    virtual ~Cricketer()
    {
    }
};

//**************** ****************************************************************** **********************/
//**************** ****************************************************************** **********************/

// 'Batsman' class represents a batsman
// Inherit 'Cricketer' class to implement 'Batsman'
class Batsman
{
protected:
    int runScored;
    int ballsFaced;

public:
    // Implement Constructor to initialize batting details along with cricketer data
    // Take Name, Age, Matches played, Runs, Balls
    Batsman();

    // Compute batting average: runs/matches
    double computeBattingAverage();

    // Compute strike rate: (runs/balls faced) * 100
    double computeStrikeRate();

    // Getter & Setter for total runs
    // Getter & Setter for balls faced

    // Print batsman-specific stats; you have to use the base class's method here.
    void printInfo();
};

// 'Bowler' class represents a bowler
// Inherit 'Cricketer' class to implement 'Bowler'
class Bowler
{
protected:
    int wicketsTaken;
    int runsConceded;
    double oversBowled;

public:
    // Implement Constructor to initialize bowling details along with cricketer data
    // Take Name, Age, Matches played, Wickets, RunsConceded, Overs
    Bowler();

    // Compute average wickets per match
    double computeWicketAverage();

    // Compute economy rate: runs conceded per over
    double computeEconomy();

    // Getter & Setter for wickets
    // Getter & Setter for runs conceded
    // Getter & Setter for overs bowled

    // Print bowler-specific stats; you have to use the base class's method here.
    void printInfo();
};

// The following class represents an allrounder (inherits from both Batsman and Bowler)
class Allrounder
{
public:
    // Implement Constructor to initialize all data for an allrounder (batsman and bowler)
    Allrounder();

    // Print both batting and bowling statistics; you have to use the base class's method here.
    void printInfo();
};

// input file style
// TYPE Name Age Matches Runs Balls Wickets RunsConceded Overs

int main()
{
    // You have to take input from "input1.txt" and you have to generate an "output.txt" file like "Demo_output.txt"
    // First take the players information from "input.txt" and create necessary player objects
    // Then save them in an array of players
    // Finally, show the players' information
    // NOTE: Players can be of any type

    return 0;
}
