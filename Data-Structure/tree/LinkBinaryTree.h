#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include <iostream>
namespace BT
{

    enum print
    {
        PRE,
        IN,
        POST
    };
    // 各种声明
    template <class Elem>
    class LinkBinaryTree;
    template <class Elem>
    class BinTreeNode;
    template <class Elem>
    LinkBinaryTree<Elem> create(const Elem pre[], const Elem in[], int size);
    template <class Elem>
    void printTree(const LinkBinaryTree<Elem> &Bt, print printType);

    // 定义
    template <class Elem>
    class BinTreeNode
    {
        friend class LinkBinaryTree<Elem>; // 将LinkBinaryTree类设为友元类
        friend LinkBinaryTree<Elem> create<Elem>(const Elem pre[], const Elem in[], int size);
        friend void printTree<Elem>(const LinkBinaryTree<Elem> &Bt, print printType);

    protected:
        Elem data;                     // 数据域
        BinTreeNode<Elem> *leftChild;  // 左孩子指针域
        BinTreeNode<Elem> *rightChild; // 右孩子指针域
        BinTreeNode();                 // 默认构造
        BinTreeNode(const Elem &data, BinTreeNode<Elem> *lChild,
                    BinTreeNode<Elem> *rChild); // 带参数的构造函数
    };

    template <class Elem>
    class LinkBinaryTree
    {
        friend class BinTreeNode<Elem>; // 将BinTreeNode类设为友元类
        // 将构建函数设为友元
        friend LinkBinaryTree<Elem> create<Elem>(const Elem pre[], const Elem in[], int size);
        friend void printTree<Elem>(const LinkBinaryTree<Elem> &Bt, print printType);

    protected:
        BinTreeNode<Elem> *root; // 根结点指针
        void createHelp(BinTreeNode<Elem> *&root, const Elem pre[], const Elem in[], int pleft, int pright, int ileft, int iright);

    public:
        LinkBinaryTree(); // 默认构造函数
        LinkBinaryTree(LinkBinaryTree<Elem> &&src);
        LinkBinaryTree(const LinkBinaryTree<Elem> &src) = delete;
        void preOrder(const BinTreeNode<Elem> *rt) const;  // 先序遍历
        void inOrder(const BinTreeNode<Elem> *rt) const;   // 中序遍历
        void postOrder(const BinTreeNode<Elem> *rt) const; // 后序遍历
    };

    template <class Elem>
    BinTreeNode<Elem>::BinTreeNode()
        : leftChild(nullptr), rightChild(nullptr)
    {
    }

    template <class Elem>
    BinTreeNode<Elem>::BinTreeNode(const Elem &data, BinTreeNode<Elem> *lChild,
                                   BinTreeNode<Elem> *rChild)
        : data(data), leftChild(lChild), rightChild(rChild)
    {
    }

    template <class Elem>
    LinkBinaryTree<Elem>::LinkBinaryTree()
        : root(nullptr)
    {
    }

    template <class Elem>
    LinkBinaryTree<Elem>::LinkBinaryTree(LinkBinaryTree<Elem> &&src)
    {
        this->root = src.root;
        src.root = nullptr;
    }

    template <class Elem>
    void LinkBinaryTree<Elem>::preOrder(const BinTreeNode<Elem> *rt) const
    {
        if (rt != nullptr)
        {
            std::cout << rt->data << ' ';
            preOrder(rt->leftChild);
            preOrder(rt->rightChild);
        }
    }

    template <class Elem>
    void LinkBinaryTree<Elem>::inOrder(const BinTreeNode<Elem> *rt) const
    {
        if (rt != nullptr)
        {
            inOrder(rt->leftChild);
            std::cout << rt->data << ' ';
            inOrder(rt->rightChild);
        }
    }

    template <class Elem>
    void LinkBinaryTree<Elem>::postOrder(const BinTreeNode<Elem> *rt) const
    {
        if (rt != nullptr)
        {
            postOrder(rt->leftChild);
            postOrder(rt->rightChild);
            std::cout << rt->data << ' ';
        }
    }
    template <class Elem>
    void printTree(const LinkBinaryTree<Elem> &Bt, print printType)
    {
        switch (printType)
        {
        case PRE:
            Bt.preOrder(Bt.root);
            break;

        case IN:
            Bt.inOrder(Bt.root);
            break;

        case POST:
            Bt.postOrder(Bt.root);
            break;
        default:
            std::cout << "Error print::TYPE\n";
        }
        std::cout << '\n';
    }
    // 声明构建函数
    template <class Elem>
    void LinkBinaryTree<Elem>::createHelp(BinTreeNode<Elem> *&rt, const Elem pre[], const Elem in[], int pleft, int pright, int ileft, int iright)
    {
        if (ileft > iright)
            rt = nullptr;
        else
        {
            rt = new BinTreeNode<Elem>(pre[pleft], nullptr, nullptr);
            int mid = ileft;
            while (in[mid] != pre[pleft])
                mid++;
            createHelp(rt->leftChild, pre, in, pleft + 1, pleft + mid - ileft, ileft, mid - 1);
            createHelp(rt->rightChild, pre, in, pleft + mid - ileft + 1, pright, mid + 1, iright);
        }
    }

    template <class Elem>
    LinkBinaryTree<Elem> create(const Elem pre[], const Elem in[], const int size)
    {
        BinTreeNode<Elem> *root;
        LinkBinaryTree<Elem> BinT;
        BinT.createHelp(root, pre, in, 0, size - 1, 0, size - 1);
        BinT.root = root;
        root = nullptr;
        return BinT;
    }
} // namespace BT

#endif // BINARY_TREE_H