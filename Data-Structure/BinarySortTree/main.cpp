/*
 * @Author: laplace825
 * @Date: 2024-04-22 20:08:54
 * @LastEditors: laplace825
 * @LastEditTime: 2024-04-22 21:42:59
 * @FilePath: /algorithm-road/Data-Structure/BinarySortTree/main.cpp
 * @Description:
 *
 * Copyright (c) 2024 by laplace825, All Rights Reserved.
 */
#include "BST.hpp"

signed main() {
  using std::cout;
  // constexpr int in[] = {1, 2, 3, 4};
  // constexpr int pre[] = {1, 2, 3, 4};
  BT::BST<int> binSortTree;
  binSortTree.insert(1);
  binSortTree.insert(10);
  binSortTree.insert(5);
  binSortTree.insert(3);
  binSortTree.inOrder();
  binSortTree.allKey(4);
  // binSortTree.preOrder();
  // BT::BinTreeNode<int> *res;
  // cout << binSortTree.find(2, res);
}
