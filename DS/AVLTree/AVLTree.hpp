#ifndef __AVL_TREE_HPP__
#define __AVL_TREE_HPP__

#include <format>
#include <iomanip>
#include <iostream>
#include <queue>

namespace BT {

template <typename Elem>
class AVLTree
{
protected:
    struct AVLNode
    {
        Elem data;           // 数据域
        AVLNode *leftChild;  // 左孩子
        AVLNode *rightChild; // 右孩子
        size_t height;       // 该节点的高度
        short BF;            // 平衡因子
        size_t lsize;        // 该结点左子树中结点数加1

        AVLNode() = default;
        AVLNode(const Elem &_data, size_t _height = 1,
                AVLNode *_leftC = nullptr, AVLNode *_rightC = nullptr,
                size_t _lsize = 1)
            : data(_data),
              height(_height),
              leftChild(_leftC),
              rightChild(_rightC),
              lsize(_lsize),
              BF(0)
        {
        }

        ~AVLNode()
        {
            if (leftChild) delete leftChild;
            if (rightChild) delete rightChild;
        }
        // 重载输出运算符
        friend std::ostream &operator<<(std::ostream &os, const AVLNode &node)
        {
            return os << std::format("data[{}] height[{}] BF[{}] lsize[{}]",
                                     node.data, node.height, node.BF,
                                     node.lsize);
        }
    };
    AVLNode *root;

    size_t getHeight(AVLNode *node) const noexcept
    {
        return node ? node->height : 0;
    }
    short getBF(AVLNode *node) const noexcept { return node ? node->BF : 0; }

    void updateBF(AVLNode *node) noexcept
    {
        node->BF = getHeight(node->rightChild) - getHeight(node->leftChild);
    }

    void updateHeight(AVLNode *node) noexcept
    {
        node->height =
            std::max(getHeight(node->leftChild), getHeight(node->rightChild)) +
            1;
    }

    void updateStatus(AVLNode *node) noexcept
    {
        updateHeight(node);
        updateBF(node);
    }

    void updateLsizeWhenRotate(AVLNode *node) noexcept
    {
        if (node)
        {
            if (node->leftChild)
                node->lsize = node->leftChild->lsize + 1;
            else
                node->lsize = 1;
        }
    }

    void LL_rotate(AVLNode *&subRoot)
    {
        /**
         * @description: subRoot 表示需要旋转的子树根节点
         * @param {AVLNode} *subRoot
         * @return {*}
         */
        AVLNode *tmp = subRoot->leftChild;
        subRoot->leftChild = tmp->rightChild;
        tmp->rightChild = subRoot;
        updateStatus(subRoot);
        updateLsizeWhenRotate(subRoot);
        updateStatus(tmp);
        updateLsizeWhenRotate(tmp);
        subRoot = tmp;
    }

    void RR_rotate(AVLNode *&subRoot)
    {
        AVLNode *tmp = subRoot->rightChild;
        subRoot->rightChild = tmp->leftChild;
        tmp->leftChild = subRoot;
        updateStatus(subRoot);
        updateLsizeWhenRotate(subRoot);
        updateStatus(tmp);
        updateLsizeWhenRotate(tmp);
        subRoot = tmp;
    }

    void RL_rotate(AVLNode *&subRoot)
    {
        /**
         * @description: 先将subRoot的右孩子LL旋转,再将自己RR旋转
         * @param {AVLNode} *subRoot
         * @return {*}
         */
        LL_rotate(subRoot->rightChild);
        RR_rotate(subRoot);
    }

    void LR_rotate(AVLNode *&subRoot)
    {
        RR_rotate(subRoot->leftChild);
        LL_rotate(subRoot);
    }

public:
    AVLTree() : root{nullptr} {}

    ~AVLTree()
    {
        std::queue<AVLNode *> que;
        if (!root)
            ;
        else
        {
            auto tmp = root;
            delete tmp;
            tmp->leftChild = nullptr;
            tmp->rightChild = nullptr;
        }
    }

    void print() const noexcept
    {
        /**
         * @note: 按照树形结构进行打印
         */
        auto printHelp = [](auto &&func, AVLNode *node, int indent) -> void {
            if (node != nullptr)
            {
                if (node->rightChild)
                {
                    func(func, node->rightChild, indent + 4);
                }
                if (indent)
                {
                    std::cout << std::setw(indent) << ' ';
                }
                if (node->rightChild)
                {
                    std::cout << " /\n" << std::setw(indent) << ' ';
                }
                std::cout << node->data << "\n ";
                if (node->leftChild)
                {
                    std::cout << std::setw(indent) << ' ' << " \\\n";
                    func(func, node->leftChild, indent + 4);
                }
            }
        };
        printHelp(printHelp, root, 0);
        std::cout << std::endl;
    }

    auto find(const Elem &key)
    {
        AVLNode *nearBFneq0Node{nullptr};
        AVLNode *PnearBFneq0Node{nullptr};
        AVLNode *PKeyNode{nullptr};
        auto curNode = root;
        if (!root)
            return std::make_tuple(curNode, PKeyNode, nearBFneq0Node,
                                   PnearBFneq0Node);
        else
        {
            while (curNode && curNode->data != key)
            {
                if (curNode->BF != 0)
                {
                    PnearBFneq0Node = PKeyNode;
                    nearBFneq0Node = curNode;
                }
                if (key < curNode->data)
                {
                    PKeyNode = curNode;
                    curNode = curNode->leftChild;
                }
                else
                {
                    PKeyNode = curNode;
                    curNode = curNode->rightChild;
                }
            }
            return std::make_tuple(curNode, PKeyNode, nearBFneq0Node,
                                   PnearBFneq0Node);
        }
    }

    void insert(const Elem &e) noexcept
    {
        // @note:keyNode为e对应的节点,PKeyNode为keyNode双亲
        // nearBFneq0Node 为最近一个BF不等于0的,PnearBFneq0Node为前面的双亲
        auto abs = [](const auto &x) { return x > 0 ? x : -x; };

        auto updateLsize = [](AVLNode *node) {
            if (node) node->lsize += 1;
        };

        auto insertHelp = [this, &e, &abs, &updateLsize](
                              auto &&func, AVLNode *&subRoot) -> void {
            if (subRoot == nullptr)
            {
                subRoot = new AVLNode(e);
                return;
            }
            else if (subRoot->data > e)
            {
                // @note : 左子树插入

                func(func, subRoot->leftChild);
                updateStatus(subRoot);
                updateLsize(subRoot);
                if (abs(getBF(subRoot)) > 1)
                {
                    if (getBF(subRoot->leftChild) == 1)
                    {
                        LR_rotate(subRoot);
                    }
                    else if (getBF(subRoot->leftChild) == -1)
                    {
                        LL_rotate(subRoot);
                    }
                }
            }

            else if (subRoot->data < e)
            {
                // @note: 右子树插入

                func(func, subRoot->rightChild);
                updateStatus(subRoot);
                if (abs(getBF(subRoot)) > 1)
                {
                    if (getBF(subRoot->rightChild) == 1)
                    {
                        RR_rotate(subRoot);
                    }
                    else if (getBF(subRoot->rightChild) == -1)
                    {
                        RL_rotate(subRoot);
                    }
                }
            }
            else
                return; // @note: 已经存在相同元素,不插入
        };

        insertHelp(insertHelp, root);
    }

    auto findTheKMinElem(size_t k) const noexcept
    {
        /**
         * @description: 找到第k小的元素
         * @param {size_t} k
         * @return {*}
         */
        auto findtheKMinElemHelp = [](auto &&func, AVLNode *subRoot,
                                      int64_t iter) -> AVLNode * {
            // subRoot非空时
            if (subRoot)
            {
                // 左边的节点数多一些
                if (subRoot->lsize > iter)
                {
                    /**
                     * @note: 每次将iter-subRoot->lsize检查当前被跳过的元素个数
                     */
                    iter = iter - static_cast<int64_t>(subRoot->lsize) > 0
                               ? iter - subRoot->lsize
                               : iter;
                    return func(func, subRoot->leftChild, iter);
                }
                else if (subRoot->lsize < iter)
                {
                    iter = iter - static_cast<int64_t>(subRoot->lsize) > 0
                               ? iter - subRoot->lsize
                               : iter;
                    return func(func, subRoot->rightChild, iter);
                }
            }

            return subRoot;
        };
        return findtheKMinElemHelp(findtheKMinElemHelp, root, k);
    }

    size_t height() const noexcept
    {
        size_t heightAvlTree{0};
        // while (curNode) {
        //     if (curNode->BF > 0) {
        //         curNode = curNode->rightChild;
        //         heightAvlTree++;
        //     } else if (curNode->BF <= 0) {
        //         curNode = curNode->leftChild;
        //         heightAvlTree++;
        //     }
        // }

        // 尾递归
        auto heightHelp = [&heightAvlTree](auto &&func, AVLNode *node) {
            if (!node)
                return heightAvlTree;
            else
            {
                heightAvlTree++;
                // @note: 树左边高则BF<0
                return node->BF >= 0 ? func(func, node->rightChild)
                                     : func(func, node->leftChild);
            }
        };

        return heightHelp(heightHelp, root);
    }
};

} // namespace BT
#endif // __AVL_TREE_HPP__
