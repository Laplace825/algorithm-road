#include <algorithm>
#include <iostream>
#include <vector>

#include "DoubleDirBubble.hpp"

int main() {
    using std::vector;
    vector<int> vec{2, 1, 0, -1, 2, 19, 3, 7, 1, 5};
    ds::DoubleBubbleSort(vec.data(), 0, vec.size());

    std::for_each(vec.begin(), vec.end(),
                  [](const int elem) { std::cout << elem << ' '; });
}
