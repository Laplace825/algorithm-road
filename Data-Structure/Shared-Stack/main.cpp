#include "SharedStack.h"
#include <iostream>

int main()
{
    // write a test case here
    SharedStack<int> s(10);
    for(int i = 0;i < 5;i++){
        s.push(i,1);
    } // 0 1 2 3 4 - - - - -
    for(int i = 5;i < 10;i++){
        s.push(i,2);
    } // - - - - 9 8 7 6 5
    std::cout << "top1: " << s.getTop(1) << '\n'; // 4
    std::cout << "top2: " << s.getTop(2) << '\n'; // 9
    std::cout << "size1: " << s.getSize(1) << '\n'; // 5
    std::cout << "size2: " << s.getSize(2) << '\n'; // 5
    std::cout << "pop1: " << s.pop(1) << '\n'; // 4
    std::cout << "pop2: " << s.pop(2) << '\n'; // 9
    std::cout << "top1: " << s.getTop(1) << '\n'; // 3
    std::cout << "top2: " << s.getTop(2) << '\n'; // 8
    std::cout << "size1: " << s.getSize(1) << '\n'; // 4
    std::cout << "size2: " << s.getSize(2) << '\n'; // 4
}
