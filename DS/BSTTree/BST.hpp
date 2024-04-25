/*
 * @Author: laplace825
 * @Date: 2024-04-22 20:09:21
 * @LastEditors: laplace825
 * @LastEditTime: 2024-04-24 20:51:35
 * @FilePath: /algorithm-road/Data-Structure/BinarySortTree/BST.hpp
 * @Description:
 *
 * Copyright (c) 2024 by laplace825, All Rights Reserved.
 */
#ifndef __BST_HPP__
#define __BST_HPP__

#include "LinkBinaryTree.h"
#include <queue>
namespace BT
{
  template <typename Elem>
  class BST : public LinkBinaryTree<Elem>
  {
    friend class BinTreeNode<Elem>;

  public:
    BinTreeNode<Elem> *find(const Elem &e, BinTreeNode<Elem> *&res) const;
    bool insert(const Elem &v) noexcept;
    void allKey(const Elem &x) const;
  };

  template <typename Elem>
  BinTreeNode<Elem> *BST<Elem>::find(const Elem &e,
                                     BinTreeNode<Elem> *&res) const
  {
    using std::queue;

    BinTreeNode<Elem> *tmp = this->root;
    res = nullptr;
    while (tmp && tmp->data != e)
    {
      res = tmp;
      if (tmp->data < e)
      {
        tmp = tmp->rightChild;
      }
      else
      {
        tmp = tmp->leftChild;
      }
    }
    return tmp;
  }

  template <typename Elem>
  bool BST<Elem>::insert(const Elem &v) noexcept
  {
    BinTreeNode<Elem> *parent{};
    if (find(v, parent))
    {
      return false;
    }
    else
    {
      auto *p = new BinTreeNode<Elem>(v, nullptr, nullptr);
      if (!this->root)
        this->root = p;
      else if (parent->data > v)
      {
        parent->leftChild = p;
      }
      else
      {
        parent->rightChild = p;
      }
      return true;
    }
  }

  template <typename Elem>
  void BST<Elem>::allKey(const Elem &x) const
  {
    /**
     * NOTE: 当前节点值小往右递归,大则左右都递归
     * Param: x 是待比较的值
     */
    std::stack<Elem> stk;
    auto help = [this, &x, &stk](auto &&func, BinTreeNode<Elem> *rt) -> void
    {
      if (!rt)
        return;
      if (rt->data < x)
      {
        func(func, rt->rightChild);
      }
      else
      {
        stk.push(rt->data);
        func(func, rt->leftChild);
        func(func, rt->rightChild);
      }
    };

    help(help, this->root);
    while (!stk.empty())
    {
      std::cout << stk.top() << ' ';
      stk.pop();
    }
  }
} // namespace BT

#endif // __BST_HPP__
