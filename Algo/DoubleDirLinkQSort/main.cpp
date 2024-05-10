/*
 * @Author: laplace825
 * @Date: 2024-05-06 13:46:18
 * @LastEditors: laplace825
 * @LastEditTime: 2024-05-06 16:18:17
 * @FilePath: /algorithm-road/Algo/LinkQSort/main.cpp
 * @Description:
 *
 * Copyright (c) 2024 by laplace825, All Rights Reserved.
 */
#include <iostream>
#include <vector>

#include "LinkQSort.hpp"

signed main() {
    using std::vector;
    vector<int> vec{10, 2, 7, 8, -1, 2, 3, 6, 20, 1, 2, 3, -2, -9, 0, 100};
    ds::LinkListDoubleDir<int> dlist(vec.data(), vec.size());
    dlist.println();
    dlist.Qsort();
    dlist.println();
}
