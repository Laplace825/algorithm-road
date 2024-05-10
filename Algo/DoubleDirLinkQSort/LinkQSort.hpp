/*
 * @Author: laplace825
 * @Date: 2024-05-06 13:46:18
 * @LastEditors: laplace825
 * @LastEditTime: 2024-05-06 16:29:51
 * @FilePath: /algorithm-road/Algo/DoubleDirLinkQSort/LinkQSort.hpp
 * @Description:
 *
 * Copyright (c) 2024 by laplace825, All Rights Reserved.
 */
#ifndef __LINK_Q_SORT_HPP__
#define __LINK_Q_SORT_HPP__

#include <iomanip>
#include <iostream>

namespace ds {

template <typename Elem>
class LinkListDoubleDir {
   protected:
    struct Node {
        Elem data;
        Node* before;
        Node* next;
        Node(const Elem& _data, Node* const _before = nullptr,
             Node* const _next = nullptr)
            : data(_data), before(_before), next(_next) {}
    };

    Node* _head;

   public:
    LinkListDoubleDir() : _head(nullptr) {}

    LinkListDoubleDir(const Elem* const arr, size_t size) : _head(nullptr) {
        for (size_t i = 0; i < size; i++) insert(arr[i]);
    }
    ~LinkListDoubleDir() {
        while (_head) {
            Node* tmp = _head;
            _head = _head->next;
            tmp->next = nullptr;
            delete tmp;
        }
    }

    void insert(const Elem& element) noexcept {
        if (!_head) {
            _head = new Node(element);
            return;
        }
        Node* cur = _head;
        while (cur->next) {
            cur = cur->next;
        }
        cur->next = new Node(element, cur, nullptr);
    }

    void println() const noexcept {
        if (_head) {
            Node* cur = _head;
            while (cur) {
                std::cout << cur->data << " -> ";
                cur = cur->next;
            }
        }
        std::cout << "null \n";
    }

    void Qsort() {
        if (_head) {
            Node* tail = _head;
            while (tail->next) tail = tail->next;

            auto swapNode = [](Node* first, Node* second) {
                auto tmp = first->data;
                first->data = second->data;
                second->data = tmp;
            };

            auto QSortHelp = [swapNode](auto&& func, Node*& _begin,
                                        Node*& _end) -> void {
                if (!_begin || !_end) {
                    return;
                    // _begin == nullptr || _end == nullptr
                }
                if (_begin == _end || _begin->before == _end) return;

                Elem pivot = _begin->data;
                Node* begin = _begin;
                Node* end = _end;
                while (begin != end) {
                    for (; begin != end && end->data >= pivot;
                         end = end->before)
                        ;  // 从后往前找第一个比 pivot 小的元素
                    if (begin != end) {
                        swapNode(begin, end);
                        begin = begin->next;
                    }
                    for (; begin != end && begin->data <= pivot;
                         begin = begin->next)
                        ;  // 从前往后找第一个比 pivot 大的元素
                    if (begin != end) {
                        swapNode(begin, end);
                        end = end->before;
                    }
                }
                func(func, _begin, begin->before);
                func(func, begin->next, _end);
            };

            QSortHelp(QSortHelp, _head, tail);
        }
    }
};

}  // namespace ds

#endif  // __LINK_Q_SORT_HPP__
