#ifndef __DIAGRAM_HPP__
#define __DIAGRAM_HPP__

#include <chrono>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

namespace ds {

class timer {
    // 毫秒计时器
   private:
    std::chrono::time_point<std::chrono::steady_clock> start_time;

   public:
    timer() : start_time(std::chrono::steady_clock::now()) {}

    void reset() noexcept { start_time = std::chrono::steady_clock::now(); }

    int64_t elapsed() const noexcept {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(
                   std::chrono::steady_clock::now() - start_time)
            .count();
    }
};

enum class TransType { DFS, BFS };

// 有向图的邻接表
template <typename Elem>
class AdjListNet {
   protected:
    struct vexLinkNode {
        int64_t m_adjVex{-1};
        int64_t m_weight{};
        vexLinkNode *m_next{nullptr};

        vexLinkNode(int64_t adjVex, int64_t weight, vexLinkNode *next)
            : m_adjVex(adjVex), m_weight(weight), m_next(next) {}

        vexLinkNode() = default;
    };

    struct vexNode {
        Elem m_data;
        vexLinkNode *m_firstArc;  // 指向第一个邻接点
        vexNode() = default;
    };

    std::vector<vexNode> m_vexs;  // 顶点数组
    std::vector<bool> visited;    // 访问标志数组

   public:
    AdjListNet() = default;

    AdjListNet(const Elem *es, size_t vertexnum)
        : visited(vertexnum, false), m_vexs(vertexnum) {
        if (vertexnum < 0)
            throw std::out_of_range("vertexnum must be greater than 0");
        for (size_t i = 0; i < vertexnum; i++) {
            m_vexs[i].m_data = es[i];
            m_vexs[i].m_firstArc = new vexLinkNode();
        }
    }

    virtual void add_arc(int64_t index_dot1, int64_t index_dot2,
                         int64_t weight) {
        /***
         * @note: 添加一条从 dot1 到 dot2 的弧(出), 将大的index放后面
         */
        if (index_dot1 < 0 || index_dot2 < 0)
            throw std::out_of_range("index out of range");

        vexLinkNode *tmp = new vexLinkNode(index_dot2, weight, nullptr);

        // 找到当前节点的最后一个邻接点
        vexLinkNode *p = m_vexs[index_dot1].m_firstArc->m_next;

        vexLinkNode *p_prior = m_vexs[index_dot1].m_firstArc;
        while (p) {
            if (p->m_adjVex >= index_dot2 && p_prior->m_adjVex <= index_dot2)
                break;
            p = p->m_next;
            p_prior = p_prior->m_next;
        }
        if (!p) {
            p_prior->m_next = tmp;
        } else {
            tmp->m_next = p;
            p_prior->m_next = tmp;
        }
    }

    virtual void remove_arc(int64_t index_dot1, int64_t index_dot2) {
        /**
         * @note: 删除一条从 dot1 到 dot2 的弧(出)
         */
        if (index_dot1 < 0 || index_dot2 < 0)
            throw std::out_of_range("index out of range");

        // 找到当前节点的最后一个邻接点
        vexLinkNode *p = m_vexs[index_dot1].m_firstArc;
        while (p != nullptr && p->m_next->m_adjVex != index_dot2) p = p->m_next;
        // 删除边
        if (p != nullptr) {
            vexLinkNode *tmp = p->m_next;
            p->m_next = tmp->m_next;
            delete tmp;
        }
    }

    void print() noexcept {
        vexLinkNode *lnode{nullptr};
        for (auto &it : m_vexs) {
            std::cout << "| " << it.m_data << " |  -> ";
            lnode = it.m_firstArc->m_next;
            while (lnode) {
                std::cout << "|id: " << lnode->m_adjVex
                          << "|w:" << lnode->m_weight << " | -> ";
                lnode = lnode->m_next;
            }
            std::cout << "null\n";
        }
    }

    void reset_visit() { visited.assign(visited.size(), false); }

   protected:
    void dfs(
        int64_t index_dot,
        const std::function<void(Elem &elem)> &funcTrans = [](Elem &elem) {}) {
        /**
         * @note: 深度优先搜索
         * @param index_dot: 起始顶点
         */
        if (index_dot < 0 || index_dot >= m_vexs.size())
            throw std::out_of_range("index out of range");

        visited[index_dot] = true;
        funcTrans(m_vexs[index_dot].m_data);

        vexLinkNode *p = m_vexs[index_dot].m_firstArc->m_next;
        while (p) {
            // 访问未访问过的邻接点
            if (!visited[p->m_adjVex]) {
                dfs(p->m_adjVex, funcTrans);
            }
            p = p->m_next;
        }
    }

    void bfs(
        int64_t index_dot,
        const std::function<void(Elem &elem)> &funcTrans = [](Elem &elem) {}) {
        std::queue<int64_t> queue;
        if (index_dot < 0 || index_dot >= m_vexs.size())
            throw std::out_of_range("index out of range");
        queue.push(index_dot);
        visited[index_dot] = true;
        int64_t index = queue.front();
        vexLinkNode *tmp = m_vexs[index].m_firstArc->m_next;
        while (!queue.empty()) {
            index = queue.front();
            queue.pop();
            funcTrans(m_vexs[index].m_data);
            tmp = m_vexs[index].m_firstArc->m_next;
            while (tmp) {
                if (!visited[tmp->m_adjVex]) {
                    queue.push(tmp->m_adjVex);
                    visited[tmp->m_adjVex] = true;
                }
                tmp = tmp->m_next;
            }
        }
    }

   public:
    void dfs_trans(
        int64_t index_dot = 0,
        const std::function<void(Elem &elem)> &funcTrans = [](Elem &elem) {
            std::cout << elem << " ";
        }) noexcept {
        dfs(index_dot, funcTrans);
        reset_visit();
        std::cout << '\n';
    }

    void bfs_trans(
        int64_t index_dot = 0,
        const std::function<void(Elem &elem)> &funcTrans = [](Elem &elem) {
            std::cout << elem << " ";
        }) noexcept {
        bfs(index_dot, funcTrans);
        reset_visit();
        std::cout << '\n';
    }

    bool dfs_arc_exist(int64_t index_dot1, int64_t index_dot2) {
        if (index_dot1 < 0 || index_dot2 < 0 || index_dot1 >= m_vexs.size() ||
            index_dot2 >= m_vexs.size())
            throw std::out_of_range("index out of range");
        /**
         * @note: 利用dfs判断两个顶点之间是否连通
         */
        dfs(index_dot1);
        bool flag = visited[index_dot2];
        reset_visit();
        return flag;
    }

    bool bfs_arc_exist(int64_t index_dot1, int64_t index_dot2) {
        if (index_dot1 < 0 || index_dot2 < 0 || index_dot1 >= m_vexs.size() ||
            index_dot2 >= m_vexs.size())
            throw std::out_of_range("index out of range");
        /**
         * @note: 利用dfs判断两个顶点之间是否连通
         */
        bfs(index_dot1);
        bool flag = visited[index_dot2];
        reset_visit();
        return flag;
    }

    auto conect_compoent() noexcept {
        /**
         * @note: 返回dfs遍历的连通分量的节点下标
         */
        std::vector<size_t> res;
        for (size_t i = 0; i < m_vexs.size(); i++) {
            if (!visited[i]) {
                dfs(i);
                res.push_back(i);
            }
        }
        reset_visit();
        return res;
    }
};

template <typename Elem>
class AdjListDirNet : public AdjListNet<Elem> {
    // 有向图的邻接表
   public:
    AdjListDirNet(const Elem *es, size_t vertexnum)
        : AdjListNet<Elem>(es, vertexnum) {}

    void add_arc(int64_t index_dot1, int64_t index_dot2,
                 int64_t weight) override {
        AdjListNet<Elem>::add_arc(index_dot1, index_dot2, weight);
    }

    void remove_arc(int64_t index_dot1, int64_t index_dot2) override {
        AdjListNet<Elem>::remove_arc(index_dot2, index_dot1);
    }

    auto topo_sort() noexcept {
        /**
         * NOTE: 返回拓扑排序的下标结果
         * BFS 统计入度
         * 基于DFS进行拓扑排序
         */
        std::vector<int64_t> res;                                // 结果数组
        std::vector<bool> Indegree(this->m_vexs.size(), false);  // 入度数组
        std::queue<int64_t> queue;  // BFS 遍历队列
        queue.push(0);
        this->visited[0] = true;
        int64_t index = queue.front();
        typename AdjListDirNet<Elem>::vexLinkNode *tmp =
            this->m_vexs[index].m_firstArc->m_next;
        while (!queue.empty()) {
            // BFS 遍历
            index = queue.front();
            queue.pop();
            tmp = this->m_vexs[index].m_firstArc->m_next;
            while (tmp) {
                if (!this->visited[tmp->m_adjVex]) {
                    queue.push(tmp->m_adjVex);
                    this->visited[tmp->m_adjVex] = true;
                    Indegree[tmp->m_adjVex] = true;
                }
                // 入度自增
                tmp = tmp->m_next;
            }
        }

        // 把入度为 0 的点的下标拿进来
        for (size_t i = 0; i < Indegree.size(); i++) {
            if (!Indegree[i]) queue.push(i);
        }
        this->reset_visit();
        while (!queue.empty()) {
            // NOTE: 所有入度为0的节点开始DFS
            if (!this->visited[queue.back()]) {
                topoSortDFSHelp(queue.back(), res);
                queue.pop();
            }
        }

        auto left = 0;
        auto right = res.size() - 1;
        while (left < right) {
            std::swap(res[left], res[right]);
            left++;
            right--;
        }
        this->reset_visit();
        return res;
    }

   private:
    void topoSortDFSHelp(int64_t index_dot, std::vector<int64_t> &stk) {
        this->visited[index_dot] = true;
        typename AdjListDirNet<Elem>::vexLinkNode *p =
            this->m_vexs[index_dot].m_firstArc->m_next;
        while (p) {
            if (!this->visited[p->m_adjVex]) {
                topoSortDFSHelp(p->m_adjVex, stk);
            }
            p = p->m_next;
        }
        /***
         * NOTE: 当前点的所有邻接点都访问过后,将当前点加入栈
         * 逆拓扑排序的思路
         */
        stk.push_back(index_dot);  // 用的是数组,所以之后还需要反转
    }
};

template <typename Elem>
class AdjListUndirNet : public AdjListNet<Elem> {
    // 无向图的邻接表
   public:
    AdjListUndirNet(const Elem *es, size_t vertexnum)
        : AdjListNet<Elem>(es, vertexnum) {}

    void add_arc(int64_t index_dot1, int64_t index_dot2,
                 int64_t weight) override {
        AdjListNet<Elem>::add_arc(index_dot1, index_dot2, weight);
        AdjListNet<Elem>::add_arc(index_dot2, index_dot1, weight);
    }

    void remove_arc(int64_t index_dot1, int64_t index_dot2) override {
        AdjListNet<Elem>::remove_arc(index_dot1, index_dot2);
        AdjListNet<Elem>::remove_arc(index_dot2, index_dot1);
    }

    bool path_exist(size_t pathlen) {
        /**
         * @note: 判断是否存在长度为 pathlen 的简单路径(不存在重复顶点的路径)
         *        获取连通分量的下标,然后对每个连通分量进行dfs遍历,判断是否存在长度为
         * pathlen 的路径
         */
        size_t arcs{0};
        std::vector<size_t> conectComponesArr = this->conect_compoent();

        for (const auto &i : conectComponesArr) {
            this->dfs(conectComponesArr[i], [&arcs](Elem &e) { arcs++; });
            if (arcs >= pathlen) return true;
            this->reset_visit();
        }

        return false;
    }

    bool is_tree() {
        /**
         * @note: 判断该图是否是一棵树
         * 判断连通分量是否为1,且无环
         *
         */
        auto conect_compoent = [this]() noexcept {
            /**
             * @note: 返回dfs遍历的连通分量的节点下标
             */
            std::vector<size_t> res;
            for (size_t i = 0; i < this->m_vexs.size(); i++) {
                if (!this->visited[i]) {
                    this->dfs(i);
                    res.push_back(i);
                }
            }
            this->reset_visit();
            return res;
        };

        if (conect_compoent().size() != 1)
            return false;  // 连通分量不为1返回false

        /**
         * @note: 继续判断连通图是否有环
         */
        int64_t ArcNum{0};
        this->dfs(0, [&ArcNum](const auto &elem) { ArcNum++; });
        if (ArcNum == this->m_vexs.size() - 1)
            return true;  // 无环且有N-1条边返回true
        else
            return false;  // 无环但有N条边返回false
    }
};

template <typename Elem>
class AdjMatrixNet {
    // 邻接矩阵
   protected:
    std::vector<Elem> m_data;
    std::vector<std::vector<int64_t>> m_vexs;
    std::vector<bool> visited;
    size_t ArcNum;

   public:
    AdjMatrixNet() = default;

    AdjMatrixNet(const Elem *es, size_t vertexnum)
        : m_data(es, es + vertexnum),
          ArcNum(0),
          visited(vertexnum, false),
          m_vexs(vertexnum, std::vector<int64_t>(vertexnum, 0)) {}

    virtual void add_arc(int64_t index_dot1, int64_t index_dot2,
                         int64_t weight) {
        if (index_dot1 < 0 || index_dot2 < 0 || index_dot1 >= m_data.size() ||
            index_dot2 >= m_data.size())
            throw std::out_of_range("index out of range");

        if (!m_vexs[index_dot1][index_dot2]) {
            m_vexs[index_dot1][index_dot2] = 1;
            ArcNum++;
        }
    }

    virtual void remove_arc(int64_t index_dot1, int64_t index_dot2) {
        if (index_dot1 < 0 || index_dot2 < 0 || index_dot1 >= m_data.size() ||
            index_dot2 >= m_data.size())
            throw std::out_of_range("index out of range");
        if (m_vexs[index_dot1][index_dot2]) {
            m_vexs[index_dot1][index_dot2] = 0;
            ArcNum--;
        }
    }
};

template <typename Elem>
class AdjMatrixUnDirNet : public AdjMatrixNet<Elem> {
    // 无向图的邻接矩阵
   public:
    using AdjMatrixNet<Elem>::AdjMatrixNet;

    void add_arc(int64_t index_dot1, int64_t index_dot2,
                 int64_t weight) override {
        AdjMatrixNet<Elem>::add_arc(index_dot1, index_dot2, weight);
        AdjMatrixNet<Elem>::add_arc(index_dot2, index_dot1, weight);
    }

    void remove_arc(int64_t index_dot1, int64_t index_dot2) override {
        AdjMatrixNet<Elem>::remove_arc(index_dot1, index_dot2);
        AdjMatrixNet<Elem>::remove_arc(index_dot2, index_dot1);
    }
};

template <typename Elem>
class AdjMatrixDirNet : public AdjMatrixNet<Elem> {
    // 无向图的邻接矩阵
   public:
    using AdjMatrixNet<Elem>::AdjMatrixNet;

    void add_arc(int64_t index_dot1, int64_t index_dot2,
                 int64_t weight) override {
        AdjMatrixNet<Elem>::add_arc(index_dot1, index_dot2, weight);
    }

    void remove_arc(int64_t index_dot1, int64_t index_dot2) override {
        AdjMatrixNet<Elem>::remove_arc(index_dot1, index_dot2);
    }

    /**
     * @note: 返回拓扑排序
     */
    // 该函数实现拓扑排序并返回结果数组
    auto topologicalSort() const {
        std::vector<int64_t> res;  // 存储拓扑排序结果的数组
        std::vector<int64_t> inDegree(this->m_data.size(),
                                      0);  // 记录每个顶点的入度

        // 计算每个顶点的入度
        for (size_t i = 0; i < this->m_data.size(); i++) {
            for (size_t j = 0; j < this->m_data.size(); j++) {
                if (this->m_vexs[i][j]) inDegree[j]++;
            }
        }

        std::queue<int64_t> queue;  // 用于存储入度为0的顶点
        for (size_t i = 0; i < inDegree.size(); i++) {
            if (inDegree[i] == 0) queue.push(i);
        }

        // 开始拓扑排序
        while (!queue.empty()) {
            int64_t index = queue.front();
            queue.pop();
            res.push_back(index);  // 将入度为0的顶点加入结果数组
            for (size_t i = 0; i < this->m_data.size(); i++) {
                if (this->m_vexs[index][i]) {
                    inDegree[i]--;  // 将与当前顶点相连的顶点的入度减一
                    if (inDegree[i] == 0)
                        queue.push(i);  // 如果入度变为0，则加入队列
                }
            }
        }

        // 若结果数组长度不等于顶点数，说明图中存在环，抛出异常
        if (res.size() != this->m_data.size())
            throw std::runtime_error("directed graph has a cycle");
        return res;  // 返回拓扑排序结果数组
    }

    size_t longest_path() noexcept {
        // 实现拓扑排序并计算最长路径的函数
        // 计算有向无环图中的最长路径

        // 拓扑排序下标序列
        auto res = topologicalSort();
        std::vector<int64_t> path(this->m_data.size(), 0);
        // 计算路径长度的函数 for (size_t i = 0; i < res.size(); i++) {
        for (size_t i = 0; i < this->m_vexs.size(); i++) {
            for (size_t j = 0; j < i; j++) {
                // 如果顶点 res[j] 到顶点 res[i] 之间有边
                if (this->m_vexs[res[j]][res[i]])
                    /**
                     * @ NOTE:
                     * 基于之前已有相邻顶点的路径长度更新当前顶点的路径长度,
                     * 所以是取之前的路径长度+1或者当前点的长度的较大值
                     * 取较大值是因为可能存在多条路径到达当前顶点
                     */
                    // 更新顶点 res[i] 的路径长度为顶点 res[j] 的路径长度加
                    // res[1] 或者不变的较大值 NOTE:带权图时把 1 替换为权值
                    // this->m_vexs[res[j]][res[i]]
                    path[res[i]] =
                        path[res[i]] >
                                path[res[j]] + this->m_vexs[res[j]][res[i]]
                            ? path[res[i]]
                            : path[res[j]] + this->m_vexs[res[j]][res[i]];
            }
        }
        size_t maxPath{0};
        for (const auto &i : path) {
            maxPath = i > maxPath ? i : maxPath;
        }
        return maxPath;
    }

    int64_t exit_path_length(int64_t index_dot1, int64_t index_dot2,
                             int64_t k) const {
        /**
         * @param:
         * k: 路径长度
         * @note:
         * 判断是否存在长度为 k 的路径数,不含回路
         * 使用快速幂得到 k 次幂的矩阵
         */
        if (index_dot1 < 0 || index_dot2 < 0 ||
            index_dot1 >= this->m_vexs.size() ||
            index_dot2 >= this->m_vexs.size())
            throw std::out_of_range("index out of range");
        if (k < 1) throw std::invalid_argument("k must be greater than 0");

        if (k == 1) return this->m_vexs[index_dot1][index_dot2];

        auto martixMultiply =
            [](const std::vector<std::vector<int64_t>> &mtrix_1,
               const std::vector<std::vector<int64_t>> &mtrix_2) {
                std::vector<std::vector<int64_t>> res(
                    mtrix_1.size(), std::vector<int64_t>(mtrix_1.size(), 0));

                // 必然是 n x n 的方阵
                for (int i = 0; i < mtrix_1.size(); i++)
                    for (int j = 0; j < mtrix_1.size(); j++)
                        for (int kk = 0; kk < mtrix_1.size(); kk++)
                            res[i][j] += mtrix_1[i][kk] * mtrix_2[kk][j];

                return res;
            };

        auto res = std::vector<std::vector<int64_t>>(
            this->m_vexs.size(), std::vector<int64_t>(this->m_vexs.size(), 1));
        auto res_tmp = this->m_vexs;

        while (k > 1) {
            if (k & 1) {
                res = martixMultiply(res, res_tmp);
            }
            res_tmp = martixMultiply(res_tmp, res_tmp);
            k >>= 1;
        }

        return res_tmp[index_dot1][index_dot2];
    }
};

AdjListDirNet<int> get_graph_dire() {
    int *es = new int[]{0, 1, 2, 3, 4, 5, 6};
    AdjListDirNet<int> graph_dire(es, 7);
    graph_dire.add_arc(0, 4, 5);
    graph_dire.add_arc(0, 1, 8);
    graph_dire.add_arc(0, 3, 4);
    graph_dire.add_arc(4, 1, 2);
    graph_dire.add_arc(1, 2, 3);
    graph_dire.add_arc(4, 5, 2);
    graph_dire.add_arc(4, 2, 7);
    graph_dire.add_arc(3, 4, 1);
    graph_dire.add_arc(5, 6, 9);
    graph_dire.add_arc(5, 2, 3);
    graph_dire.add_arc(2, 6, 6);
    delete[] es;
    return graph_dire;
}

AdjListUndirNet<char> get_graph_undire() {
    char *es = new char[]{'A', 'B', 'C', 'D', 'E', 'F'};
    AdjListUndirNet<char> graph_undire(es, 6);
    graph_undire.add_arc(0, 1, 12);

    graph_undire.add_arc(0, 2, 3);

    graph_undire.add_arc(0, 4, 9);

    graph_undire.add_arc(0, 5, 10);

    graph_undire.add_arc(1, 5, 6);

    graph_undire.add_arc(1, 3, 2);

    graph_undire.add_arc(2, 5, 6);

    graph_undire.add_arc(2, 3, 2);

    graph_undire.add_arc(3, 5, 7);

    graph_undire.add_arc(4, 5, 4);

    graph_undire.add_arc(3, 4, 4);
    delete[] es;
    return graph_undire;
}

AdjMatrixDirNet<int> get_graph_matrix_dire() {
    int *es = new int[]{0, 1, 2, 3, 4, 5, 6};
    AdjMatrixDirNet<int> graph_matrix_dire(es, 7);
    graph_matrix_dire.add_arc(0, 4, 5);
    graph_matrix_dire.add_arc(0, 1, 8);
    graph_matrix_dire.add_arc(0, 3, 4);
    graph_matrix_dire.add_arc(4, 1, 2);
    graph_matrix_dire.add_arc(1, 2, 3);
    graph_matrix_dire.add_arc(4, 5, 2);
    graph_matrix_dire.add_arc(4, 2, 7);
    graph_matrix_dire.add_arc(3, 4, 1);
    graph_matrix_dire.add_arc(5, 6, 9);
    graph_matrix_dire.add_arc(5, 2, 3);
    graph_matrix_dire.add_arc(2, 6, 6);
    delete[] es;
    return graph_matrix_dire;
}

template <class Graph>
void Trans(Graph &graph, int64_t index_dot, TransType type) {
    switch (type) {
        case TransType::BFS:
            graph.bfs_trans(index_dot);
            break;

        case TransType::DFS:
            graph.dfs_trans(index_dot);
            break;
    }
}

}  // namespace ds
#endif  // __DIAGRAM_HPP__
