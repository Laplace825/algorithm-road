#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include <deque>
#include <iostream>
#include <stack>

namespace BT {

enum class print { PRE, IN, POST, LEVEL, DOUBLE };
// 各种声明
template <class Elem>
class LinkBinaryTree;
template <class Elem>
class BinTreeNode;
template <class Elem>
class BST;
template <class Elem>
LinkBinaryTree<Elem> create(const Elem pre[], const Elem in[], int size);
template <class Elem>
void printTree(const LinkBinaryTree<Elem> &Bt, print printType);
template <class Elem>
unsigned int leafNum(const LinkBinaryTree<Elem> &root);
// 定义
template <class Elem>
class BinTreeNode {
    friend class LinkBinaryTree<Elem>;  // 将LinkBinaryTree类设为友元类
    friend class BST<Elem>;
    friend LinkBinaryTree<Elem> create<Elem>(const Elem pre[], const Elem in[],
                                             int size);
    friend void printTree<Elem>(const LinkBinaryTree<Elem> &Bt,
                                print printType);
    friend unsigned int leafNum<Elem>(const LinkBinaryTree<Elem> &root);

    template <typename T>
    friend bool is_BST(const LinkBinaryTree<T> &bTree, bool ascending) noexcept;

   protected:
    Elem data;                      // 数据域
    BinTreeNode<Elem> *leftChild;   // 左孩子指针域
    BinTreeNode<Elem> *rightChild;  // 右孩子指针域
    BinTreeNode();                  // 默认构造
    BinTreeNode(const Elem &data, BinTreeNode<Elem> *lChild,
                BinTreeNode<Elem> *rChild);  // 带参数的构造函数
    ~BinTreeNode() {
        delete leftChild;
        delete rightChild;
        leftChild = nullptr;
        rightChild = nullptr;
    }
};

template <class Elem>
class LinkBinaryTree {
    friend class BinTreeNode<Elem>;  // 将BinTreeNode类设为友元类
    // 将构建函数设为友元
    friend LinkBinaryTree<Elem> create<Elem>(const Elem pre[], const Elem in[],
                                             int size);
    friend void printTree<Elem>(const LinkBinaryTree<Elem> &Bt,
                                print printType);
    friend unsigned int leafNum<Elem>(const LinkBinaryTree<Elem> &root);

    template <typename T>
    friend bool is_BST(const LinkBinaryTree<T> &bTree, bool ascending) noexcept;

   protected:
    using Uint = unsigned int;
    BinTreeNode<Elem> *root;  // 根结点指针
    BinTreeNode<Elem> *&createHelp(BinTreeNode<Elem> *&root, const Elem pre[],
                                   const Elem in[], int pleft, int pright,
                                   int ileft, int iright);
    Uint depth(const BinTreeNode<Elem> *rt) const;        // 求树的深度
    void preOrder(const BinTreeNode<Elem> *rt) const;     // 先序遍历
    void inOrder(const BinTreeNode<Elem> *rt) const;      // 中序遍历
    void postOrder(const BinTreeNode<Elem> *rt) const;    // 后序遍历
    void doubleOrder(const BinTreeNode<Elem> *rt) const;  // 递归双序遍历
    Uint leafNum(const BinTreeNode<Elem> *rt) const;  // 求树的叶子结点个数
   public:
    LinkBinaryTree();  // 默认构造函数
    LinkBinaryTree(LinkBinaryTree<Elem> &&src);
    LinkBinaryTree(const LinkBinaryTree<Elem> &src) = delete;
    ~LinkBinaryTree();
    void preOrder() const;    // 非递归前序遍历
    void inOrder() const;     // 非递归中序遍历
    void postOrder() const;   // 非递归后序遍历
    void levelOrder() const;  // 层序遍历
    auto getRoot() const noexcept;
    /**
     * @todo: 非递归双序
     */
    // void doubleOrder() const; // 非递归双序遍历
    Uint depth() const;     // 求树的深度,递归
    Uint maxWidth() const;  // 求树的最大宽度,非递归
    Uint leafNum() const;   // 求树的叶子结点个数,非递归
};

template <class Elem>
BinTreeNode<Elem>::BinTreeNode() : leftChild(nullptr), rightChild(nullptr) {}

template <class Elem>
BinTreeNode<Elem>::BinTreeNode(const Elem &data, BinTreeNode<Elem> *lChild,
                               BinTreeNode<Elem> *rChild)
    : data(data), leftChild(lChild), rightChild(rChild) {}

template <class Elem>
LinkBinaryTree<Elem>::LinkBinaryTree() : root(nullptr) {}

template <class Elem>
LinkBinaryTree<Elem>::LinkBinaryTree(LinkBinaryTree<Elem> &&src) {
    this->root = src.root;
    src.root = nullptr;
}

template <class Elem>
LinkBinaryTree<Elem>::~LinkBinaryTree() {
    delete root;
    root = nullptr;
    /**
     * @note : 貌似直接 delete root 整颗树都会被删
     * 我认为可能是因为 delete root 需要释放 root 指向的结点
     * root 结点具有的 leftchild 和 rightchild 指针也被释放
     * 而这两个指针释放时也调用该结点的析构函数
     * 所以不断往下继续,只要 delete root 后都被删除了
     */
    // std::deque<BinTreeNode<Elem> *> que;
    // BinTreeNode<Elem> *cur = nullptr;
    // if (root != nullptr)
    //     que.push_front(root);
    // while (!que.empty())
    // {
    //     cur = que.front();
    //     que.pop_front();
    //     if (cur->leftChild != nullptr)
    //         que.push_back(cur->leftChild);
    //     if (cur->rightChild != nullptr)
    //         que.push_back(cur->rightChild);
    //     cur->leftChild = nullptr;
    //     cur->rightChild = nullptr;
    //     delete cur;
    // }
    // root = nullptr;
}

template <class Elem>
void LinkBinaryTree<Elem>::preOrder(const BinTreeNode<Elem> *rt) const {
    if (rt != nullptr) {
        std::cout << rt->data << ' ';
        preOrder(rt->leftChild);
        preOrder(rt->rightChild);
    }
}

template <class Elem>
void LinkBinaryTree<Elem>::inOrder(const BinTreeNode<Elem> *rt) const {
    if (rt != nullptr) {
        inOrder(rt->leftChild);
        std::cout << rt->data << ' ';
        inOrder(rt->rightChild);
    }
}

template <class Elem>
void LinkBinaryTree<Elem>::postOrder(const BinTreeNode<Elem> *rt) const {
    if (rt != nullptr) {
        postOrder(rt->leftChild);
        postOrder(rt->rightChild);
        std::cout << rt->data << ' ';
    }
}

template <class Elem>
void LinkBinaryTree<Elem>::levelOrder() const {
    std::deque<BinTreeNode<Elem> *> que;
    if (root != nullptr) que.push_back(root);
    while (!que.empty()) {
        std::cout << que.front()->data << ' ';
        if (que.front()->leftChild != nullptr)
            que.push_back(que.front()->leftChild);
        if (que.front()->rightChild != nullptr)
            que.push_back(que.front()->rightChild);
        que.pop_front();
        // 需要注意pop没有返回值
    }
    std::cout << '\n';
}

template <class Elem>
void LinkBinaryTree<Elem>::doubleOrder(const BinTreeNode<Elem> *rt) const {
    if (rt != nullptr) {
        std::cout << rt->data << ' ';
        doubleOrder(rt->leftChild);
        std::cout << rt->data << ' ';
        doubleOrder(rt->rightChild);
    }
}

template <class Elem>
void LinkBinaryTree<Elem>::preOrder() const {
    // // 使用栈非递归前序遍历
    // std::deque<BinTreeNode<Elem> *> stk;
    // // 用tmp记录被弹出的结点,判断是否存在右子树
    // BinTreeNode<Elem> *tmp = nullptr;
    // if (root != nullptr)
    // {
    //     stk.push_back(root);
    // }
    // while (!stk.empty())
    // {
    //     std::cout << stk.back()->data << ' ';
    //     tmp = stk.back();
    //     stk.pop_back();
    //     // 先入右孩子,保证先孩子先输出
    //     if (tmp->rightChild != nullptr)
    //     {
    //         stk.push_back(tmp->rightChild);
    //     }
    //     if (tmp->leftChild != nullptr)
    //     {
    //         stk.push_back(tmp->leftChild);
    //     }
    // }
    // std::cout << '\n';
    std::deque<BinTreeNode<Elem> *> stk;
    BinTreeNode<Elem> *rt = this->root;
    while (rt || (!stk.empty())) {
        if (rt) {
            stk.push_back(rt);
            std::cout << rt->data << ' ';
            rt = rt->leftChild;
        } else {
            rt = stk.back()->rightChild;
            stk.pop_back();
        }
    }
    std::cout << '\n';
}

// template <class Elem>
// void LinkBinaryTree<Elem>::inOrder() const
// {
//     // 使用栈非递归中序遍历
//     std::deque<BinTreeNode<Elem> *> stk;
//     // 使用标志位记录结点是否被访问过
//     std::deque<Uint> flag;
//     //
//     这里是因为当左子树全遍历完后,stk和flag都空,此时flag.back()会出错,所以先push_back一个0
//     flag.push_back(0);
//     // 用tmp记录被弹出的结点,判断是否存在右子树
//     BinTreeNode<Elem> *tmp = nullptr;
//     if (root != nullptr)
//     {
//         stk.push_back(root);
//         flag.push_back(0);
//     }
//     while (!stk.empty())
//     {
//         if (stk.back()->leftChild != nullptr && flag.back() == 0)
//         {
//             stk.push_back(stk.back()->leftChild);
//             flag.push_back(0);
//         }
//         else
//         {
//             std::cout << stk.back()->data << ' ';
//             tmp = stk.back();
//             stk.pop_back();
//             flag.pop_back();
//             (flag.back())++;
//             if (tmp->rightChild != nullptr)
//             {
//                 stk.push_back(tmp->rightChild);
//                 flag.push_back(0);
//             }
//         }
//     }
//     std::cout << '\n';
// }

template <class Elem>
void LinkBinaryTree<Elem>::inOrder() const {
    // 使用栈非递归中序遍历
    // 使用标志位记录结点是否被访问过
    // std::deque<Uint> flag;
    // 这里是因为当左子树全遍历完后,stk和flag都空,此时flag.back()会出错,所以先push_back一个0
    // flag.push_back(0);
    // 用tmp记录被弹出的结点,判断是否存在右子树
    std::deque<BinTreeNode<Elem> *> stk;
    BinTreeNode<Elem> *rt = this->root;
    BinTreeNode<Elem> *tmp = nullptr;
    while (rt || (!stk.empty())) {
        if (rt) {
            stk.push_back(rt);
            rt = rt->leftChild;
        } else {
            tmp = stk.back();
            stk.pop_back();
            std::cout << tmp->data << ' ';
            rt = tmp->rightChild;
        }
    }
    std::cout << '\n';
}

template <class Elem>
void LinkBinaryTree<Elem>::postOrder() const {
    /**
     * @todo : 完成非递归后序遍历
     * */
    // 使用栈非递归中序遍历
    std::deque<BinTreeNode<Elem> *> stk;
    // 使用标志位记录结点是否被访问过
    std::deque<Uint> flag;
    // 这里是因为当左子树全遍历完后,stk和flag都空,此时flag.back()会出错,所以先push_back一个0
    flag.push_back(0);
    // 用tmp记录被弹出的结点,判断是否存在右子树
    BinTreeNode<Elem> *tmp = nullptr;
    if (root != nullptr) {
        stk.push_back(root);
        flag.push_back(0);
    }
    while (!stk.empty()) {
        if (stk.back()->leftChild != nullptr && flag.back() == 0) {
            stk.push_back(stk.back()->leftChild);
            flag.push_back(0);
        } else {
            if (stk.back()->rightChild == nullptr || flag.back() == 2 ||
                tmp == stk.back()->rightChild) {
                tmp = stk.back();
                std::cout << stk.back()->data << ' ';
                stk.pop_back();
                flag.pop_back();
                flag.back()++;
            } else {
                stk.push_back(stk.back()->rightChild);
                flag.push_back(0);
            }
        }
    }
    std::cout << '\n';
}

template <class Elem>
typename LinkBinaryTree<Elem>::Uint LinkBinaryTree<Elem>::depth() const {
    if (root == nullptr)
        return 0;
    else {
        return depth(root);
    }
}

template <class Elem>
typename LinkBinaryTree<Elem>::Uint LinkBinaryTree<Elem>::depth(
    const BinTreeNode<Elem> *rt) const {
    if (rt == nullptr)
        return 0;
    else {
        Uint leftDepth = depth(rt->leftChild);
        Uint rightDepth = depth(rt->rightChild);
        return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
    }
}

template <class Elem>
typename LinkBinaryTree<Elem>::Uint LinkBinaryTree<Elem>::maxWidth() const {
    // 层序遍历,每层遍历完宽度即为队列长度,计算最大宽度即可
    // 最坏时间复杂度为O(n),n为结点个数
    std::deque<BinTreeNode<Elem> *> que;
    Uint count = 0;
    Uint countMax = 0;
    Uint maxWidth = 0;
    if (root != nullptr) {
        count++;
        que.push_back(root);
    }
    // count每次记录一层弹入的元素,下一次弹出countMax个元素,保证每次队列只有一层
    while (!que.empty()) {
        countMax = count;
        count = 0;
        for (Uint i = 1; i <= countMax; i++) {
            if (que.front()->leftChild != nullptr) {
                que.push_back(que.front()->leftChild);
                count++;
            }
            if (que.front()->rightChild != nullptr) {
                que.push_back(que.front()->rightChild);
                count++;
            }
            que.pop_front();
        }
        maxWidth = que.size() > maxWidth ? que.size() : maxWidth;
    }
    return maxWidth;
}

template <class Elem>
typename LinkBinaryTree<Elem>::Uint LinkBinaryTree<Elem>::leafNum(
    const BinTreeNode<Elem> *rt) const {
    if (rt == nullptr)
        return 0;
    else if (rt->leftChild == nullptr && rt->rightChild == nullptr)
        return 1;
    else {
        return leafNum(rt->leftChild) + leafNum(rt->rightChild);
    }
}

template <class Elem>
typename LinkBinaryTree<Elem>::Uint LinkBinaryTree<Elem>::leafNum() const {
    // 层序遍历,遇到叶子结点计数
    std::deque<BinTreeNode<Elem> *> que;
    Uint leafNum = 0;
    if (root != nullptr) que.push_back(root);
    while (!que.empty()) {
        if (que.front()->leftChild == nullptr &&
            que.front()->rightChild == nullptr)
            leafNum++;
        if (que.front()->leftChild != nullptr)
            que.push_back(que.front()->leftChild);
        if (que.front()->rightChild != nullptr)
            que.push_back(que.front()->rightChild);
        que.pop_front();
    }
    return leafNum;
}

template <class Elem>
void printTree(const LinkBinaryTree<Elem> &Bt, print printType) {
    switch (printType) {
        case print::PRE:
            Bt.preOrder(Bt.root);
            break;
        case print::IN:
            Bt.inOrder(Bt.root);
            break;
        case print::POST:
            Bt.postOrder(Bt.root);
            break;
        case print::LEVEL:
            Bt.levelOrder();
            break;
        case print::DOUBLE:
            Bt.doubleOrder(Bt.root);
            break;
        default:
            std::cout << "Error print::TYPE\n";
            break;
    }
    std::cout << '\n';
}

// 声明构建函数
// 对rt指针的引用保证rt指针的改变能够传递到上一层递归
template <class Elem>
BinTreeNode<Elem> *&LinkBinaryTree<Elem>::createHelp(BinTreeNode<Elem> *&rt,
                                                     const Elem pre[],
                                                     const Elem in[], int pleft,
                                                     int pright, int ileft,
                                                     int iright) {
    if (ileft > iright)
        rt = nullptr;
    else {
        // 中序和先序序列构建二叉树
        rt = new BinTreeNode<Elem>(pre[pleft], nullptr,
                                   nullptr);  // 创建根结点,左右孩子为默认空指针
        int mid = ileft;
        while (in[mid] != pre[pleft]) mid++;  // 找到根结点在中序序列中的位置
        // 递归创建左右子树,将左右孩子作为新子树的根结点
        createHelp(rt->leftChild, pre, in, pleft + 1, pleft + mid - ileft,
                   ileft, mid - 1);
        createHelp(rt->rightChild, pre, in, pleft + mid - ileft + 1, pright,
                   mid + 1, iright);
        /**
         * @note :
         * 递归栈上的createHelp函数返回后,rt指针会被销毁,但是rt指针指向的结点不会被销毁
         * 且由于 return 语句
         * 在最后,先递归创建左子树,再递归创建右子树后返回的rt并不会成为最终的root
         * 只有在整个递归栈一直到头后,最后一次递归返回的rt才是函数真正返回的有效指针
         */
    }
    return rt;
}

template <class Elem>
auto LinkBinaryTree<Elem>::getRoot() const noexcept {
    return this->root;
}

template <class Elem>
LinkBinaryTree<Elem> create(const Elem pre[], const Elem in[], const int size) {
    LinkBinaryTree<Elem> BinT;
    BinT.createHelp(BinT.root, pre, in, 0, size - 1, 0, size - 1);
    return BinT;
}

template <class Elem>
unsigned int leafNum(const LinkBinaryTree<Elem> &Bintree) {
    return Bintree.leafNum(Bintree.root);
}

template <typename Elem>
bool is_BST(const LinkBinaryTree<Elem> &bTree, bool ascending = true) noexcept {
    /**
     * NOTE: 中序遍历
     */

    BinTreeNode<Elem> *rt = bTree.getRoot();
    std::stack<BinTreeNode<Elem> *> stk;
    auto tmp = rt;
    auto par = rt;
    while (rt || !stk.empty()) {
        if (rt) {
            // NOTE: rt 非空时
            stk.push(rt);
            par = rt;
            rt = rt->leftChild;
        } else {
            tmp = stk.top();
            stk.pop();
            rt = tmp->rightChild;
            if (ascending) {
                if (tmp->leftChild && tmp->leftChild->data > tmp->data)
                    return false;
            } else {
                if (tmp->leftChild && tmp->leftChild->data < tmp->data)
                    return false;
            }
        }
    }
    return true;
}
}  // namespace BT

#endif  // BINARY_TREE_H
