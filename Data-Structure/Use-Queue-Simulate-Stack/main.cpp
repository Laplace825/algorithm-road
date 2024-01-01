#include "QueueSimuStack.h"
#include <iostream>
// write a test case

int main(int argc, char **argv)
{
    QueueSimuStack<int> qss;
    qss.push(1);
    qss.push(2);
    qss.push(3);
    qss.push(4);
    qss.push(5);
    while (!qss.empty())
    {
        std::cout << qss.pop() << ' ';
    }
    std::cout << '\n';
    return 0;
}