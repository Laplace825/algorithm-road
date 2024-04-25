/*
 * @Author: laplace825
 * @Date: 2024-04-23 15:34:04
 * @LastEditors: laplace825
 * @LastEditTime: 2024-04-25 21:11:27
 * @FilePath: /algorithm-road/Data-Structure/AVLTree/main.cpp
 * @Description:
 *
 * Copyright (c) 2024 by laplace825, All Rights Reserved.
 */
#include <format>
#include <iostream>

#include "AVLTree.hpp"

signed main() {
    BT::AVLTree<int> AvlTr;
    constexpr int arr[] = {50, 30, 53, 52, 55, 26, 33, 10, 27, 28};
    for (size_t i = 0; i < sizeof(arr) / 4; i++) {
        AvlTr.insert(arr[i]);
    }
    std::cout << "*-----------\033[1;33mAvlTree\033[0m------------*\n";
    AvlTr.print();
    std::cout << "--------------------------------\n";
    std::cout << "find the \033[1;33m2nd\033[0m smallest :"
              << *AvlTr.findTheKMinElem(2) << '\n';
    std::cout << "find the \033[1;33m7th\033[0m smallest :"
              << *AvlTr.findTheKMinElem(7) << '\n';
    std::cout << "--------------------------------\n";
}
