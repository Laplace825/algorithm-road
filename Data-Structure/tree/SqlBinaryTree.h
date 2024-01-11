#ifndef SQL_BINARY_TREE_H
#define SQL_BINARY_TREE_H
#include <cstring>

namespace BT
{
    // 声明顺序二叉树类
    template <typename T>
    class SqlBinaryTree;
    // 声明打印函数
    template <typename T>
    void printTree(SqlBinaryTree<T> &sqlBt, print printType);
    template <typename T>
    class SqlBinaryTree
    {
        friend void printTree<T>(SqlBinaryTree<T> &sqlBt, print printType);

    protected:
        T *data;
        unsigned int length;

    public:
        SqlBinaryTree();                            // 默认构造
        SqlBinaryTree(const SqlBinaryTree<T> &src); // 拷贝
        SqlBinaryTree(SqlBinaryTree<T> &&src);      // 移动构造
        SqlBinaryTree(const T arr[], int size);     // 数组
        ~SqlBinaryTree() { delete[] data; length = 0;}
        // 均使用递归实现,index表示根节点在数组中的下标,默认为0
        void preOrder(int index = 0) const;
        void inOrder(int index = 0) const;
        void postOrder(int index = 0) const;
        void levelOrder() const;

        T &operator[](int index) { return data[index]; }
        T &findNearParent(int ind_1st, int ind_2nd) const;
    };

    template <typename T>
    SqlBinaryTree<T>::SqlBinaryTree()
        : data(nullptr), length(0) {}

    template <typename T>
    SqlBinaryTree<T>::SqlBinaryTree(const SqlBinaryTree<T> &src)
        : data(new T[src.length]), length(src.length)
    {
        memcpy(data, src.data, length);
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
        : data(new T[size]), length(size)
    {
        memcpy(data, arr, size);
    }

    template <typename T>
    void SqlBinaryTree<T>::preOrder(int index) const
    {
        if (index >= length)
            return;
        std::cout << data[index] << ' ';
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        preOrder(left);
        preOrder(right);
    }

    template <typename T>
    void SqlBinaryTree<T>::inOrder(int index) const
    {
        if (index >= length)
            return;
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        inOrder(left);
        std::cout << data[index] << ' ';
        inOrder(right);
    }

    template <typename T>
    void SqlBinaryTree<T>::postOrder(int index) const
    {
        if (index >= length)
            return;
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        postOrder(left);
        postOrder(right);
        std::cout << data[index] << ' ';
    }

    template <typename T>
    void SqlBinaryTree<T>::levelOrder() const
    {
        for (int i = 0; i < length; ++i)
            std::cout << data[i] << ' ';
    }

    template <typename T>
    T &SqlBinaryTree<T>::findNearParent(int ind_1st, int ind_2nd) const
    {
        // 找到两个节点的最近公共祖先
        if (ind_1st >= length || ind_2nd >= length)
            throw "Error index";

        /**
         * @note : 这里需要注意偶数的情况,偶数整除2会导致位置多1
         *
         *
         * 递归版
            if (ind_1st != ind_2nd)
            {
                if (ind_1st > ind_2nd)
                    findNearParent(ind_1st % 2 == 0 ? ind_1st = ind_1st / 2 - 1 : ind_1st /= 2, ind_2nd);
                if (ind_1st < ind_2nd)
                    findNearParent(ind_1st, ind_2nd % 2 == 0 ? ind_2nd = ind_2nd / 2 - 1 : ind_2nd /= 2);
            }
        */
        while (ind_1st != ind_2nd)
        {
            if (ind_1st > ind_2nd)
                ind_1st % 2 == 0 ? ind_1st = ind_1st / 2 - 1 : ind_1st /= 2;
            if (ind_1st < ind_2nd)
                ind_2nd % 2 == 0 ? ind_2nd = ind_2nd / 2 - 1 : ind_2nd /= 2;
        }
        return data[ind_1st]; // 返回最近公共祖先
    }

    template <typename T>
    void printTree(SqlBinaryTree<T> &sqlBt, print printType)
    {
        switch (printType)
        {
        case PRE:
            sqlBt.preOrder(0);
            break;
        case IN:
            sqlBt.inOrder(0);
            break;
        case POST:
            sqlBt.postOrder(0);
            break;
        case LEVEL:
            sqlBt.levelOrder();
            break;
        default:
            std::cout << "Error print::TYPE\n";
            break;
        }
        std::cout << '\n';
    }
} // namespace BT

#endif // SQL_BINARY_TREE_H