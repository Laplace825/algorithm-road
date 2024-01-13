#include "MoveSubstrTail.h"
#include <string>
#include <iostream>

int main()
{
    using std::cout;
    using std::string;

    string str = "Hello World!";
    MoveSubstrTail(str, 5, 5);
    cout << "str:" << str << '\n';

    char *arr = new char[]{" Hello World!"};
    memcpy(arr, " Hello World!", strlen(" Hello World!"));
    MoveSubstrTailArr(arr, 6, 5);
    cout << "arr:" << arr << '\n';
}