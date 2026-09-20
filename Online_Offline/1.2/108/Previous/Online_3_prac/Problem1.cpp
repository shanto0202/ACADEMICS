#include <iostream>
#include <string>
#include <iomanip>
#include <fstream> // for file handling
#include <vector>

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
class Batsman : public virtual Cricketer
{
protected:
    int runScored;
    int ballsFaced;

public:
    // Constructor to initialize all data
    Batsman(string s = "Unknown", int a = 0, int m = 0, int runs = 0, int balls = 0)
        : Cricketer(s, a, m), runScored(runs), ballsFaced(balls)
    {
    }

    // Compute batting average: runs/matches
    double computeBattingAverage()
    {
        if (matchPlayed == 0)
            return 0.0;
        return (double)runScored / matchPlayed;
    }

    // Compute strike rate: (runs/balls faced) * 100
    double computeStrikeRate()
    {
        if (ballsFaced == 0)
            return 0.0;
        return ((double)runScored / ballsFaced) * 100.0;
    }

    // Getter & Setter for total runs
    int getRunScored()
    {
        return runScored;
    }
    void setRunScored(int runs)
    {
        runScored = runs;
    }

    // Getter & Setter for balls faced
    int getBallsFaced()
    {
        return ballsFaced;
    }
    void setBallsFaced(int balls)
    {
        ballsFaced = balls;
    }

    // Print batsman-specific stats; use base class's method
    void printInfo(ofstream &out)
    {
        out << "---- Batsman Info ----" << endl;
        Cricketer::printInfo(out);
        out << "---- Batting Stats ----" << endl;
        out << "Runs Scored: " << runScored << ", Balls Faced: " << ballsFaced << endl;
        out << fixed << setprecision(2);
        out << "Batting Average: " << computeBattingAverage() << ", Strike Rate: " << computeStrikeRate() << endl;
    }
};

// 'Bowler' class represents a bowler
// Inherit 'Cricketer' class to implement 'Bowler'
class Bowler : public virtual Cricketer
{
protected:
    int wicketsTaken;
    int runsConceded;
    double oversBowled;

public:
    // Constructor to initialize all data
    Bowler(string s = "Unknown", int a = 0, int m = 0, int wickets = 0, int runs = 0, double overs = 0.0)
        : Cricketer(s, a, m), wicketsTaken(wickets), runsConceded(runs), oversBowled(overs)
    {
    }

    // Compute average wickets per match
    double computeWicketAverage()
    {
        if (matchPlayed == 0)
            return 0.0;
        return (double)wicketsTaken / matchPlayed;
    }

    // Compute economy rate: runs conceded per over
    double computeEconomy()
    {
        if (oversBowled == 0.0)
            return 0.0;
        return (double)runsConceded / oversBowled;
    }

    // Getter & Setter for wickets
    int getWicketsTaken() { return wicketsTaken; }
    void setWicketsTaken(int wickets) { wicketsTaken = wickets; }

    // Getter & Setter for runs conceded
    int getRunsConceded() { return runsConceded; }
    void setRunsConceded(int runs) { runsConceded = runs; }

    // Getter & Setter for overs bowled
    double getOversBowled() { return oversBowled; }
    void setOversBowled(double overs) { oversBowled = overs; }

    // Print bowler-specific stats; use base class's method
    void printInfo(ofstream &out)
    {
        out << "---- Bowler Info ----" << endl;
        Cricketer::printInfo(out);
        out << "---- Bowling Stats ----" << endl;
        out << "Wickets Taken: " << wicketsTaken << ", Runs Conceded: " << runsConceded << ", Overs Bowled: " << fixed << setprecision(2) << oversBowled << endl;
        out << "Wicket Average: " << computeWicketAverage() << ", Economy: " << computeEconomy() << endl;
    }
};

// The following class represents an allrounder (inherits from both Batsman and Bowler)
class Allrounder : public Batsman, public Bowler
{
public:
    // Implement Constructor to initialize all data for an allrounder (batsman and bowler)
    Allrounder(string s = "Unknown", int a = 0, int m = 0, int runs = 0, int balls = 0, int wickets = 0, int rConceded = 0, double overs = 0.0)
        : Cricketer(s, a, m), Batsman(s, a, m, runs, balls), Bowler(s, a, m, wickets, rConceded, overs)
    {
    }

    // Print both batting and bowling statistics; you have to use the base class's method here.
    void printInfo(ofstream &out)
    {
        out << "---- Allrounder Info ----" << endl;
        Cricketer::printInfo(out);
        out << "---- Batting Stats ----" << endl;
        out << "Runs Scored: " << Batsman::runScored << ", Balls Faced: " << Batsman::ballsFaced << endl;
        out << fixed << setprecision(2);
        out << "Batting Average: " << Batsman::computeBattingAverage() << ", Strike Rate: " << Batsman::computeStrikeRate() << endl;
        out << "---- Bowling Stats ----" << endl;
        out << "Wickets Taken: " << Bowler::wicketsTaken << ", Runs Conceded: " << Bowler::runsConceded << ", Overs Bowled: " << fixed << setprecision(2) << Bowler::oversBowled << endl;
        out << "Wicket Average: " << Bowler::computeWicketAverage() << ", Economy: " << Bowler::computeEconomy() << endl;
    }
};

// input file style
// TYPE Name Age Matches Runs Balls Wickets RunsConceded Overs

int main()
{
    ifstream inFile("input1.txt");
    ofstream outFile("output.txt");
    vector<Cricketer *> players;
    string type;
    while (inFile >> type)
    {
        string name;
        int age, matches, runs, balls, wickets, runsConceded;
        double overs;
        inFile >> name >> age >> matches;
        if (type == "Batsman")
        {
            inFile >> runs >> balls;
            players.push_back(new Batsman(name, age, matches, runs, balls));
        }
        else if (type == "Bowler")
        {
            inFile >> wickets >> runsConceded >> overs;
            players.push_back(new Bowler(name, age, matches, wickets, runsConceded, overs));
        }
        else if (type == "Allrounder")
        {
            inFile >> runs >> balls >> wickets >> runsConceded >> overs;
            players.push_back(new Allrounder(name, age, matches, runs, balls, wickets, runsConceded, overs));
        }
    }
    int idx = 1;
    for (auto p : players)
    {
        outFile << "=== Player " << idx++ << " ===" << endl;
        p->printInfo(outFile);
        outFile << endl;
    }
    for (auto p : players)
        delete p;
    inFile.close();
    outFile.close();
    return 0;
}
