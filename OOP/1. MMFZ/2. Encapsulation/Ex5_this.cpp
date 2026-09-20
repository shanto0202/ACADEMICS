#include <iostream>
#include <string>
using namespace std;
class Message
{
    string msg;

public:
    Message(string msg)
    {
        this->msg = msg; //this is a object pointer that's why arrow
    }
    Message updateMessage(string msg)
    {
        this->msg = msg;
        return *this;
    }
    void displayMessage()
    {
        cout << "Message: " << this->msg << endl;
    }
};

int main()
{
    Message msg("Hello, World!");
    msg.displayMessage();
    msg = msg.updateMessage("New Message.");
    msg.displayMessage();
    return 0;
}