/*
 * @Author: laplace825
 * @Date: 2024-04-28 15:47:51
 * @LastEditors: laplace825
 * @LastEditTime: 2024-04-28 20:39:25
 * @FilePath: /algorithm-road/DS/HashSequence/HashSequence.hpp
 * @Description:
 *
 * Copyright (c) 2024 by laplace825, All Rights Reserved.
 */
#ifndef __HASH__SEQUENCE_HPP__
#define __HASH__SEQUENCE_HPP__

#include <format>
#include <iostream>
#include <type_traits>
#include <vector>

namespace ds {

template <typename Elem>
class HashSeparateChain {
   protected:
    struct DataNode {
        // @note: 链表节点元素类型
        Elem data;
        DataNode* next;
        DataNode(const Elem& key, DataNode* ptr) : data(key), next(ptr){};
        ~DataNode() { delete next; }
    };

    struct Node {
        // @note: 散列表节点指针
        DataNode* keyData{nullptr};
        ~Node() { delete keyData; }
    };

    std::vector<Node> map;
    size_t CHAIN_SIZE;

    size_t Hash(const Elem& key) const {
        using originalType = std::remove_cvref_t<Elem>;
        if constexpr (std::is_same_v<originalType, std::string>) {
            // 字符串类型
            if (!key.empty()) {
                for (const auto& ch : key) {
                    if (std::isalpha(ch)) {
                        return ((std::isupper(ch) ? ch - 'A' : ch - 'a') +
                                CHAIN_SIZE) %
                               CHAIN_SIZE;
                    }
                }
            }
        } else if constexpr (std::is_same_v<originalType, char>) {
            // 字母字符
            if (std::isalpha(key))
                return ((std::isupper(key) ? key - 'A' : key - 'a') +
                        CHAIN_SIZE) %
                       CHAIN_SIZE;
            else
                static_assert("char should be A-Z or a-z");
        } else if constexpr (std::is_arithmetic_v<originalType>) {
            // 数字类型
            return static_cast<size_t>(key) % CHAIN_SIZE;
        }
        // 不是上面支持的类型
        static_assert("type not support!");
    }

   public:
    HashSeparateChain(){};
    HashSeparateChain(size_t size) : CHAIN_SIZE(size), map(size) {}
    ~HashSeparateChain() {
        for (auto& iter : map) {
            if (iter.keyData) {
                DataNode* cur = iter.keyData;
                DataNode* del = iter.keyData->next;

                while (del) {
                    cur->next = del->next;
                    delete del;
                    del = cur->next;
                }
                delete iter.keyData;
                iter.keyData = nullptr;
            }
        }
    };

    size_t size() const noexcept { return map.size(); }

    bool insert(const Elem& key) {
        size_t hashVal = Hash(key);
        if (hashVal > CHAIN_SIZE) {
            return false;
        }
        if (!map[hashVal].keyData) {
            map[hashVal].keyData = new DataNode(key, nullptr);
        } else {
            DataNode* trans = map[hashVal].keyData;
            while (trans->next) {
                trans = trans->next;
            }
            trans->next = new DataNode(key, nullptr);
        }
        return true;
    }

    void print() const {
        DataNode* cur = nullptr;
        size_t i = 0;
        for (auto& iter : map) {
            std::cout << std::format("|{}| ->", i++);
            if (iter.keyData) {
                cur = iter.keyData;
                while (cur) {
                    std::cout << std::format(" {} ->", cur->data);
                    cur = cur->next;
                }
            }
            std::cout << " null";
            std::cout << '\n';
        }
        std::cout << std::endl;
    }
};
}  // namespace ds

#endif  // __HASH__SEQUENCE_HPP__
