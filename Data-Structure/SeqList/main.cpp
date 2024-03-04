#include "SeqList.h"
#include <iostream>

int main()
{
    // write a test case
    SeqList<int> sq;
    for (int i = 0; i < 10; i++)
        sq.insert(i, i);
    std::cout << "the seqlist is :";
    for (int i = 0; i < 10; i++) // 0 1 2 3 4 5 6 7
        std::cout << sq.get(i) << " ";

    sq.insert(8, 10); // insert 10
    std::cout << '\n';
    std::cout << "After insert(8,10) :";
    for (int i = 0; i < 11; i++) // 0 1 2 3 4 5 6 7 10
        std::cout << sq.get(i) << " ";
    std::cout << '\n';

    sq.remove(8); // remove 10
    std::cout << "After remove(8) :";
    for (int i = 0; i < 10; i++) // 0 1 2 3 4 5 6 7
        std::cout << sq.get(i) << " ";
    std::cout << '\n';
    std::cout << "seqlist.size(): " << sq.getSize() << '\n';   // 8
    std::cout << "is seqlist empty? " << sq.isEmpty() << '\n'; // 0
    return 0;
}