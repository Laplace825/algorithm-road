#include "SimulateQueue.h"
#include <iostream>

int main()
{
    using std::cout ;
    using std::cin;
    SimulateQueue<int> sq;
    // write a test case
    cout << "Enqueue sequence :\n";
    for(int i = 0; i < 10; i++)
    {
        cout << i << ' ';
        sq.EnQueue(i);
    }
    cout << "\nDequeue :\n";
    for(int i = 0; i < 8; i++) // 0 1 2 3 4 5 6 7
        cout << sq.DeQueue() << " ";
    cout << "\nEnqueue 10\n";
    sq.EnQueue(10); // EnQueue 10
    cout << "Dequeue all:\n";
    while(!sq.isEmpty())
        cout << sq.DeQueue() << " ";
    // output: 0 1 2 3 4 5 6 7
    // 8 9 10
}