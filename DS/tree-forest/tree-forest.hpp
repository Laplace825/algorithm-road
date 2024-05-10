#ifndef __TREE_FOREST_HPP
#define __TREE_FOREST_HPP

/*** ----------------------------
 * @author: Laplace
 * @date: 2024/03/14T12:59
 * @note: DS Tree - Forest
------------------------------*/
#include <algorithm>
#include <format>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

namespace tree {

template <typename ElemT>
class Tree {
   public:
    virtual ~Tree() = default;

   protected:
    template <typename Iterator, typename PrintType>
    static void print(Iterator &&begin, Iterator &&end, PrintType &&print) {
        try {
            std::cout << '|';
            for (auto it = begin; it != end; it++)
                std::cout << std::format("{:^2} |",
                                         static_cast<decltype(print)>(*it));
            std::cout << '\n';
        } catch (std::out_of_range &e) {
            std::cout << e.what() << '\n';
            throw;
        }
    }

    template <typename Container>
    static constexpr std::size_t height(Container &&container) {
        /***
         * @brief: from current node to root node
         */
        std::size_t maxheight{1};
        std::size_t height{1};  // at least have a root node
        int64_t parent{-1};
        for (auto it : container) {
            parent = static_cast<int64_t>(it);
            maxheight = std::max(maxheight, height);
            height = 1;
            while (parent != -1) {
                parent = static_cast<int64_t>(container[parent]);
                height++;
            }
        }
        return maxheight;
    }

    template <typename Container>
    static constexpr std::size_t degree(Container &&container) {
        auto maxVal = [](const auto &cont) -> int64_t {
            int64_t maxIndex{0};
            for (auto &it : cont) {
                if (static_cast<int64_t>(it) > maxIndex) maxIndex = it;
            }
            return maxIndex;
        };
        std::vector<std::size_t> hash(container.size(), 0);
        for (auto it = container.begin() + 1; it != container.end(); it++)
            hash.at(static_cast<int64_t>(*it))++;
        return maxVal(hash);
    }

    /**
     * @note: Version 1.0
     * from current node to root node
     *        counter records who has child
     */
    // template <typename Container>
    // static constexpr std::size_t leafNum(Container &&container)
    // {
    //     std::size_t leafNum{0};
    //     std::vector<bool> counter(container.size(), false);
    //     int64_t parent{-1};
    //     for (int64_t i = 0; i < container.size(); i++)
    //     {
    //         parent = static_cast<int64_t>(container[i]);
    //         if (parent != -1 && !counter[parent])
    //         {
    //             /***
    //              * @note: from current node to root node
    //              *        counter records who has child
    //              *        a trick to aviod duplicate counting
    //              *        -----*** but the loop still judge
    //              *                  that doesn't make sense ***------
    //              */
    //             counter[parent] = true;
    //         }
    //     }
    //     /**
    //      * @note: if you count the parent node, you can give up the loop
    //      below
    //      *        just put the parentNum++ under the code `counter[parent] =
    //      true;`
    //      *        and return container.size() - parentNum
    //      */
    //     for (auto it : counter)
    //     {
    //         if (!it)
    //             leafNum++;
    //     }
    //     return leafNum;
    // }

    /***
     * @note: Version 2.0
     */
    // template <typename Container>
    // static constexpr std::size_t leafNum(Container &&container)
    // {
    //     std::size_t parentNum{0};
    //     int64_t parent;
    //     std::vector<int64_t> unique(container.size(), -1);
    //     for (auto it = container.begin();
    //          it != container.end() && *(unique.end() - 1) !=
    //          static_cast<int64_t>(*(container.end() - 1)); it++)
    //     {
    //         /**
    //          * @brief: use vector to simulate stack
    //          *         in order to find unique element in container
    //          */
    //         // O(n)
    //         if (unique.empty())
    //         {
    //             unique.push_back(static_cast<int64_t>(*it));
    //             parentNum++;
    //         }
    //         else
    //         {
    //             if (*(unique.end() - 1) != static_cast<int64_t>(*it))
    //             {
    //                 unique.push_back(static_cast<int64_t>(*it));
    //                 parentNum++;
    //             }
    //         }
    //     }

    //     /***
    //      * @note: This is a trick,
    //      * to understand,please think about the parent_index already implies
    //      the parents exist
    //      * so when we finish unqiue operation, just counting who wasn't root
    //      is enough
    //      */
    //     return container.size() - parentNum;
    // }

    /***
     * @note : Version 3.0
     */

    template <typename Container>
    static constexpr std::size_t leafNum(Container &&container) {
        /**
         * @note ： one line code can replace the whole function
         *          space complexity is O(n),time complexity is O(n) (bad case
         * is O(n^2))
         */
        return container.size() - std::unordered_set<int64_t>(
                                      container.begin() + 1, container.end())
                                      .size();
    }
};

template <typename ElemT>
class SeqTree : public Tree<ElemT> {
   protected:
    struct Node {
        ElemT m_data;
        int64_t m_parent;
        Node() = default;
        explicit Node(const ElemT &data, int64_t parent)
            : m_data(data), m_parent(parent) {}
        operator int64_t() const { return m_parent; }
        operator ElemT() const { return m_data; }
    };

    std::vector<Node> m_node;

   public:
    SeqTree() = default;
    SeqTree(const SeqTree &) = default;
    SeqTree(SeqTree &&rval) : SeqTree() {
        using std::swap;
        swap(*this, rval);
    }
    SeqTree &operator=(SeqTree src) {
        using std::swap;
        swap(*this, src);
        return *this;
    }
    ~SeqTree() override = default;

    SeqTree(const std::vector<ElemT> &date, const std::vector<int64_t> &parent)
        : m_node(date.size()) {
        for (std::size_t i = 0; i < date.size(); i++) {
            m_node[i].m_data = date[i];
            m_node[i].m_parent = parent[i];
        }
    }
    SeqTree(const ElemT *date, const int64_t *parent, std::size_t size)
        : m_node(size) {
        for (std::size_t i = 0; i < size; i++) {
            m_node[i].m_data = date[i];
            m_node[i].m_parent = parent[i];
        }
    }
    void print() const {
        std::cout << std::string(4 * m_node.size() + 1, '-') << '\n';
        Tree<ElemT>::print(m_node.begin(), m_node.end(), m_node[0].m_data);

        std::cout << std::string(4 * m_node.size() + 1, '-') << '\n';
        Tree<ElemT>::print(m_node.begin(), m_node.end(), m_node[0].m_parent);

        std::cout << std::string(4 * m_node.size() + 1, '-') << '\n';
    }

    constexpr std::size_t height() noexcept {
        if (m_node.empty()) return 0;
        return static_cast<Tree<ElemT> *>(this)->height(m_node);
    }

    constexpr std::size_t degree() noexcept {
        if (m_node.empty()) return 0;
        return static_cast<Tree<ElemT> *>(this)->degree(m_node);
    }

    constexpr std::size_t leafNum() noexcept {
        if (m_node.empty()) return 0;
        return Tree<ElemT>::leafNum(m_node);
    }
};

template <typename ElemT>
class LinkTree : public Tree<ElemT> {
   protected:
    /**
     * @brief: Parents-children expression
     */

    // children Node
    struct CNode {
        // child's index can't be -1
        int64_t m_childindex;
        CNode *next;
        CNode() : m_childindex(-1), next(nullptr) {}
        explicit CNode(std::size_t index, CNode *nxt)
            : m_childindex(index), next(nxt) {}

        CNode(CNode &&rval) : CNode() {
            using std::swap;
            swap(*this, rval);
        }
        CNode &operator=(CNode src) {
            using std::swap;
            swap(*this, src);
            return *this;
        }
    };

    // parents Node
    struct PNode {
        ElemT m_data;
        int64_t m_parent;
        CNode *m_childlink;
        bool operator>(const PNode &rval) const {
            return m_parent > rval.m_parent;
        }

        operator int64_t() const { return m_parent; }
    };

    std::vector<PNode> m_node;

   public:
    LinkTree() = default;
    LinkTree(const ElemT *data, const int64_t *parent, std::size_t size)
        : m_node(size) {
        int64_t parIndex{0};
        for (std::size_t i = 0; i < size; i++) {
            m_node[i].m_data = data[i];
            // {-1, 0, 0, 0, 1, 1, 2, 3, 3, 3, 5, 5, 8, 8}
            m_node[i].m_parent = parent[i];
            parIndex = parent[i];
            // with head node
            m_node[i].m_childlink = new CNode;
            if (parIndex != -1) {
                CNode *cnode_link = new CNode(i, nullptr);
                CNode *trans = m_node[parIndex].m_childlink;
                while (parIndex != -1 && trans->next) {
                    // find the last node
                    trans = trans->next;
                }
                trans->next = cnode_link;
            }
        }
    }

    ~LinkTree() override {
        CNode *cnode{nullptr};
        CNode *tmp{nullptr};
        for (auto &it : m_node) {
            delete it.m_childlink;
            while (cnode) {
                tmp = cnode;
                cnode = cnode->next;
                delete tmp;
                tmp = nullptr;
            }
            it.m_childlink = nullptr;
        }
    }

    void print() noexcept {
        CNode *cnode{nullptr};
        for (auto &it : m_node) {
            std::cout << "| " << it.m_data << " | ";
            std::cout << std::format("{:>2} |", it.m_parent) << " -> ";
            cnode = it.m_childlink->next;
            while (cnode) {
                std::cout << cnode->m_childindex << " -> ";
                cnode = cnode->next;
            }
            std::cout << "null\n";
        }
    }

    std::size_t height_BFS() noexcept {
        if (m_node.empty())
            return 0;
        else if (m_node.size() == 1)
            return 1;
        // return static_cast<Tree<ElemT> *>(this)->height(m_node);
        std::queue<int64_t> curNode;
        std::queue<std::size_t> curLevel;
        std::size_t maxHeight{1};
        CNode *trans{nullptr};
        curLevel.push(1);
        curNode.push(0);
        // O(n) time complexity
        // O(n) space complexity
        // n is the number of nodes in the tree
        while (!curNode.empty()) {
            trans = m_node[curNode.front()].m_childlink->next;
            while (trans) {
                curNode.push(trans->m_childindex);
                curLevel.push(curLevel.front() + 1);
                trans = trans->next;
            }
            maxHeight = std::max(maxHeight, curLevel.front());
            curLevel.pop();
            curNode.pop();
        }
        return maxHeight;
    }

    std::size_t height_DFS() noexcept {
        if (m_node.empty())
            return 0;
        else if (m_node.size() == 1)
            return 1;
        return static_cast<Tree<ElemT> *>(this)->height(m_node);
    }

    std::size_t degree() noexcept {
        if (m_node.empty()) return 0;
        return static_cast<Tree<ElemT> *>(this)->degree(m_node);
    }

    std::size_t leafNum() noexcept {
        if (m_node.empty()) return 0;
        // return Tree<ElemT>::leafNum(m_node);
        std::size_t leafNum{0};
        for (auto &it : m_node) {
            if (it.m_childlink->next == nullptr) leafNum++;
        }
        return leafNum;
    }
};

}  // namespace tree

#endif  // __TREE_FOREST_HPP
