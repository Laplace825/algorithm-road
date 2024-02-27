#ifndef SQL_BINARY_TREE_H
#define SQL_BINARY_TREE_H
#include <iostream>
#include <cstring>

namespace BT
{
    // 声明顺序二叉树类
    template <typename T>
    class SqlBinaryTree;
    // 声明打印函数
    template <typename T>
    void printTree(SqlBinaryTree<T> &sqlBt, print printType = print::PRE, unsigned int index = 1);
    template <typename T>
    class SqlBinaryTree
    {
        friend void printTree<T>(SqlBinaryTree<T> &sqlBt, print printType, unsigned int index);

    protected:
        T *data;
        unsigned int length;

    public:
        SqlBinaryTree();                            // 默认构造
        SqlBinaryTree(const SqlBinaryTree<T> &src); // 拷贝
        SqlBinaryTree(SqlBinaryTree<T> &&src);      // 移动构造
        SqlBinaryTree(const T arr[], int size);     // 数组
        ~SqlBinaryTree()
        {
            delete[] data;
            length = 0;
        }
        // 均使用递归实现,index表示根节点在数组中的下标,默认为0
        void preOrder(unsigned int index = 1) const;
        void inOrder(unsigned int index = 1) const;
        void postOrder(unsigned int index = 1) const;
        void levelOrder(unsigned int index = 1) const;

        T &operator[](int index) { return data[index]; }
        T &findNearParent(int ind_1st, int ind_2nd) const;
    };

    template <typename T>
    SqlBinaryTree<T>::SqlBinaryTree()
        : data(nullptr), length(0) {}

    template <typename T>
    SqlBinaryTree<T>::SqlBinaryTree(const SqlBinaryTree<T> &src)
        : data(new T[src.length + 1]), length(src.length)
    {
        memcpy(data + 1, src.data, length);
    }

    template <typename T>
    SqlBinaryTree<T>::SqlBinaryTree(SqlBinaryTree<T> &&src)
        : data(src.data), length(src.length)
    {
        src.data = nullptr;
        src.length = 0;
    }

    template <typename T>
    SqlBinaryTree<T>::SqlBinaryTree(const T arr[], int size)
        : data(new T[size + 1]), length(size)
    {
        std::copy(arr, arr + size, data + 1);
    }

    template <typename T>
    void SqlBinaryTree<T>::preOrder(unsigned int index) const
    {
        if (index > length)
            return;
        std::cout << data[index] << ' ';
        int left = 2 * index;
        int right = 2 * index + 1;
        preOrder(left);
        preOrder(right);
    }

    template <typename T>
    void SqlBinaryTree<T>::inOrder(unsigned int index) const
    {
        if (index > length)
            return;
        int left = 2 * index;
        int right = 2 * index + 1;
        inOrder(left);
        std::cout << data[index] << ' ';
        inOrder(right);
    }

    template <typename T>
    void SqlBinaryTree<T>::postOrder(unsigned int index) const
    {
        if (index > length)
            return;
        int left = 2 * index;
        int right = 2 * index + 1;
        postOrder(left);
        postOrder(right);
        std::cout << data[index] << ' ';
    }

    template <typename T>
    void SqlBinaryTree<T>::levelOrder(unsigned int index) const
    {
        for (int i = index; i <= length; ++i)
            std::cout << data[i] << ' ';
    }

    template <typename T>
    T &SqlBinaryTree<T>::findNearParent(int ind_1st, int ind_2nd) const
    {
        // 找到两个节点的最近公共祖先
        if (ind_1st >= length || ind_2nd >= length)
            throw std::invalid_argument("Error index");

        /**
         * @note :
         * 这里需要注意偶数的情况,偶数整除2会导致位置多1
         * 递归版
            if (ind_1st != ind_2nd)
            {
                if (ind_1st > ind_2nd)
                    findNearParent(ind_1st % 2 == 0 ? ind_1st = ind_1st / 2 - 1 : ind_1st /= 2, ind_2nd);
                if (ind_1st < ind_2nd)
                    findNearParent(ind_1st, ind_2nd % 2 == 0 ? ind_2nd = ind_2nd / 2 - 1 : ind_2nd /= 2);
            }
        */
        // auto Max = [&]() -> int &
        // {
        //     return ind_1st > ind_2nd ? ind_1st : ind_2nd;
        // };
        while (ind_1st != ind_2nd)
        {
            if (ind_1st > ind_2nd)
                ind_1st % 2 == 0 ? ind_1st = ind_1st / 2 - 1 : ind_1st /= 2;
            if (ind_1st < ind_2nd)
                ind_2nd % 2 == 0 ? ind_2nd = ind_2nd / 2 - 1 : ind_2nd /= 2;
            // int &max_index = Max();
            // max_index % 2 == 0 ? max_index = max_index /= 2 : max_index = max_index / 2 - 1;
        }
        return data[ind_1st]; // 返回最近公共祖先
    }

    template <typename T>
    void printTree(SqlBinaryTree<T> &sqlBt, print printType, unsigned int index)
    {
        switch (printType)
        {
        case print::PRE:
            sqlBt.preOrder(index);
            break;
        case print::IN:
            sqlBt.inOrder(index);
            break;
        case print::POST:
            sqlBt.postOrder(index);
            break;
        case print::LEVEL:
            sqlBt.levelOrder(index);
            break;
        default:
            std::cout << "Error print::TYPE\n";
            break;
        }
        std::cout << '\n';
    }
} // namespace BT

#endif // SQL_BINARY_TREE_H