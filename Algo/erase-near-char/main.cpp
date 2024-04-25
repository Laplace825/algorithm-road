#include "EraseNearChar.h"
#include <iostream>
#include <string>

int main()
{
    std::string str = "abbaca";
    std::cout << "Before: " << str << "\nAfter eraseNearChar(str): ";
    std::cout << eraseNearChar(str);
}