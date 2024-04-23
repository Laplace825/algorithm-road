#ifndef __AVL_TREE_HPP__
#define __AVL_TREE_HPP__

#include "BST.hpp"

namespace BT {

template <typename Elem> class AVLTree {
protected:
  struct AVLNode {
    AVLNode *leftChild;  // 左孩子
    AVLNode *rightChild; // 右孩子
    short BF;            // 平衡因子
    size_t lsize;        // 该结点左子树中结点数加1
  };

public:
};
} // namespace BT
#endif // __AVL_TREE_HPP__
