#include "KMP.h"
#include <iostream>

int main(int argc, char** argv) {
    std::string text = "ABABDABACDABABCABAB";
    std::string pattern = "ABABCABAB";
    int index = KMP(text, pattern); // 10
    std::cout << "index: " << index << '\n';
    return 0;
}