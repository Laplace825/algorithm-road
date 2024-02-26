#include "EraseElemArray.h"
#include <iostream>

int main(int argc, char **argv)
{
    int arr[10] = {1, 2, 3, 4, 5, 5, 7, 8, 9, 10};
    constexpr int size = 10;
    erase(5, arr, size);
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << ' ';
    } // 1 2 3 4 7 8 9 10
    std::cout << '\n';
}