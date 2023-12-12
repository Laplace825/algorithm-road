#include "SimulateQueue.h"
#include <iostream>

int main()
{
    SimulateQueue<int> sq;
    // write a test case
    for(int i = 0; i < 10; i++)
        sq.EnQueue(i);
    for(int i = 0; i < 8; i++) // 0 1 2 3 4 5 6 7
        std::cout << sq.DeQueue() << " ";
    sq.EnQueue(10); // EnQueue 10
    std::cout << '\n';
    while(!sq.isEmpty())
        std::cout << sq.DeQueue() << " ";
    return 0;
    // output: 0 1 2 3 4 5 6 7
    // 8 9 10
}