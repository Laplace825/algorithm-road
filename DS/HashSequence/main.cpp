/*
 * @Author: laplace825
 * @Date: 2024-04-28 15:47:51
 * @LastEditors: laplace825
 * @LastEditTime: 2024-04-28 18:38:37
 * @FilePath: /algorithm-road/DS/HashSequence/main.cpp
 * @Description: 
 * 
 * Copyright (c) 2024 by laplace825, All Rights Reserved. 
 */
#include <format>
#include <iostream>
#include <string>
#include "HashSequence.hpp"

signed main() {
    ds::HashSeparateChain<int> INTsepChain(10);
    std::cout << std::format("{}\n", INTsepChain.size());

    INTsepChain.insert(1);
    INTsepChain.insert(2);
    INTsepChain.insert(3);
    INTsepChain.insert(11);
    INTsepChain.print();

    ds::HashSeparateChain<std::string> StringsepChain(26);

    StringsepChain.insert("Able");
    StringsepChain.insert("Mick");
    StringsepChain.insert("Jack");
    StringsepChain.insert("Abbie");
    StringsepChain.print();

    ds::HashSeparateChain<char> CharsepChain(26);

    CharsepChain.insert('A');
    CharsepChain.insert('b');
    CharsepChain.insert('a');
    // CharsepChain.insert(',');
    CharsepChain.print();
}
