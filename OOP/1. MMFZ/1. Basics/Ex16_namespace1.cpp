// Example 1: Using std:: with every identifier

#include <iostream>
#include <string>

int main()
{
    std::string str;
    std::cout << "Enter a string: ";
    getline(std::cin, str);
    std::cout << str << std::endl;

    return 0;
}