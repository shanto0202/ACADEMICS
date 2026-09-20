#include <iostream>
#include <string.h>
using namespace std;
// struct p
// {

// } sifat;
typedef struct xx
{
private:
    char name[20];
    int rollno;
    double cgpa;

public:
    // setter - getter
    void setName(char *N)
    {
        strcpy(name, N);
    }
    char *getName()
    {
        return name;
    }
    void setRollno(int R)
    {
        rollno = R;
    }
    int getRollno()
    {
        return rollno;
    };
    void setCGPA(double CGPA)
    {
        cgpa = CGPA;
    }
    double getCGPA()
    {
        return cgpa;
    }
} Student;
int main()
{
    Student karim;
    char iname[20];
    int irollno;
    double icgpa;
    cout << "Enter the name: ";
    // cin >> karim.name; //Error
    cin >> iname;
    karim.setName(iname);
    cout << "Enter Rollno: ";
    // cin >> karim.rollno; //Error
    cin >> irollno;
    karim.setRollno(irollno);
    cout << "Enter CGPA: ";
    cin >> icgpa;
    karim.setCGPA(icgpa);
    cout << karim.getName() << " ";
    cout << karim.getRollno();
    cout << " " << karim.getCGPA();
}