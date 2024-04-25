#include "QueueSimuStack.h"
#include <iostream>
// write a test case

int main(int argc, char **argv)
{
    QueueSimuStack<int> qss;
    std::cout << "push sequence : 1 2 3 4 5\n";
    qss.push(1);
    qss.push(2);
    qss.push(3);
    qss.push(4);
    qss.push(5);
    std::cout << "pop result :";
    while (!qss.empty())
    {
        std::cout << qss.pop() << ' ';
    }
    std::cout << '\n';
    return 0;
}