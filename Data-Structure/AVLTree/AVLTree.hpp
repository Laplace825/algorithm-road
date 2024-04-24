#ifndef __AVL_TREE_HPP__
#define __AVL_TREE_HPP__

#include "BST.hpp"
#include <iostream>

namespace BT {

template <typename Elem> class AVLTree {
protected:
  struct AVLNode {
    Elem data;           // 数据域
    AVLNode *leftChild;  // 左孩子
    AVLNode *rightChild; // 右孩子
    short BF;            // 平衡因子
    size_t lsize;        // 该结点左子树中结点数加1

    AVLNode(const Elem &_data, short _BF = 0, size_t _lsize = 0)
        : data(_data), BF(_BF), lsize(_lsize) {}

    ~AVLNode() {
      delete leftChild;
      delete rightChild;
    }
  };
  AVLNode *root;

public:
  AVLTree() : root{nullptr} {}
  ~AVLTree() {
    std::queue<AVLNode *> que;
    if (!root)
      ;
    else {
      auto tmp = root;
      que.push(root);
      while (!que.empty()) {
        tmp = que.back();
        que.pop();
        if (tmp->leftChild)
          que.push(tmp->leftChild);
        if (tmp->rightChild)
          que.push(tmp->rightChild);
        delete tmp;
      }
    }
  }
  auto find(const Elem &key) {
    AVLNode *nearBFneq0Node{nullptr};
    AVLNode *PnearBFneq0Node{nullptr};
    AVLNode *PKeyNode{nullptr};
    auto curNode = root;
    if (!root)
      return std::make_tuple(curNode, PKeyNode, nearBFneq0Node,
                             PnearBFneq0Node);
    else {
      while (curNode && curNode->data != key) {
        if (curNode->BF != 0) {
          PnearBFneq0Node = PKeyNode;
          nearBFneq0Node = curNode;
        }
        if (key < curNode->data) {
          PKeyNode = curNode;
          curNode = curNode->leftChild;
        } else {
          PKeyNode = curNode;
          curNode = curNode->rightChild;
        }
      }
      return std::make_tuple(curNode, PKeyNode, nearBFneq0Node,
                             PnearBFneq0Node);
    }
  }
};
} // namespace BT
#endif // __AVL_TREE_HPP__
