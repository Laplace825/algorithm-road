#include "MoveSubstrTail.h"
#include <string>
#include <iostream>

int main()
{
    using std::cout;
    using std::string;

    string str = "Hello World!";
    cout << "Before :" << str << '\n';
    MoveSubstrTail(str, 5, 5);
    cout << "After :" << str << '\n';

    char *arr = new char[]{" Hello World!"};
    MoveSubstrTailArr(arr, 6, 5);
    cout << "arr(type char*) :" << arr << '\n';
}