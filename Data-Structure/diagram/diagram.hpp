#ifndef __DIAGRAM_HPP__
#define __DIAGRAM_HPP__

#include <iostream>
#include <vector>
#include <queue>
#include <functional>

namespace ds
{

    enum class TransType
    {
        DFS,
        BFS
    };

    // 有向图的邻接表
    template <typename Elem>
    class AdjListNet
    {
    protected:
        struct vexLinkNode
        {
            int64_t m_adjVex{-1};
            int64_t m_weight{};
            vexLinkNode *m_next{nullptr};
            vexLinkNode(int64_t adjVex, int64_t weight, vexLinkNode *next)
                : m_adjVex(adjVex), m_weight(weight), m_next(next)
            {
            }

            vexLinkNode() = default;
        };

        struct vexNode
        {
            Elem m_data;
            vexLinkNode *m_firstArc; // 指向第一个邻接点
            vexNode() = default;
        };

        std::vector<vexNode> m_vexs; // 顶点数组
        size_t ArcNum;               // 边数
        std::vector<bool> visited;   // 访问标志数组

    public:
        AdjListNet() = default;

        AdjListNet(const Elem *es, size_t vertexnum)
            : visited(vertexnum, false), m_vexs(vertexnum), ArcNum(0)
        {
            if (vertexnum < 0)
                throw std::out_of_range("vertexnum must be greater than 0");
            for (size_t i = 0; i < vertexnum; i++)
            {
                m_vexs[i].m_data = es[i];
                m_vexs[i].m_firstArc = new vexLinkNode();
            }
        }

        virtual void add_arc(int64_t index_dot1, int64_t index_dot2, int64_t weight)
        {
            /***
             * @note: 添加一条从 dot1 到 dot2 的弧(出), 将大的index放后面
             */
            if (index_dot1 < 0 || index_dot2 < 0)
                throw std::out_of_range("index out of range");

            vexLinkNode *tmp = new vexLinkNode(index_dot2, weight, nullptr);

            // 找到当前节点的最后一个邻接点
            vexLinkNode *p = m_vexs[index_dot1].m_firstArc->m_next;

            vexLinkNode *p_prior = m_vexs[index_dot1].m_firstArc;
            while (p)
            {
                if (p->m_adjVex >= index_dot2 && p_prior->m_adjVex <= index_dot2)
                    break;
                p = p->m_next;
                p_prior = p_prior->m_next;
            }
            if (!p)
            {
                p_prior->m_next = tmp;
            }
            else
            {
                tmp->m_next = p;
                p_prior->m_next = tmp;
            }
            ArcNum++;
        }

        virtual void remove_arc(int64_t index_dot1, int64_t index_dot2)
        {
            /**
             * @note: 删除一条从 dot1 到 dot2 的弧(出)
             */
            if (index_dot1 < 0 || index_dot2 < 0)
                throw std::out_of_range("index out of range");

            // 找到当前节点的最后一个邻接点
            vexLinkNode *p = m_vexs[index_dot1].m_firstArc;
            while (p != nullptr && p->m_next->m_adjVex != index_dot2)
                p = p->m_next;
            // 删除边
            if (p != nullptr)
            {
                vexLinkNode *tmp = p->m_next;
                p->m_next = tmp->m_next;
                delete tmp;
                ArcNum--;
            }
        }

        void print() noexcept
        {
            vexLinkNode *lnode{nullptr};
            for (auto &it : m_vexs)
            {
                std::cout << "| " << it.m_data << " |  -> ";
                lnode = it.m_firstArc->m_next;
                while (lnode)
                {
                    std::cout << "|id: " << lnode->m_adjVex << "|w:" << lnode->m_weight << " | -> ";
                    lnode = lnode->m_next;
                }
                std::cout << "null\n";
            }
        }

        void reset_visit()
        {
            visited.assign(visited.size(), false);
        }

    protected:
        void dfs(
            int64_t index_dot, const std::function<void(Elem &elem)> &funcTrans = [](Elem &elem) {})
        {
            /**
             * @note: 深度优先搜索
             * @param index_dot: 起始顶点
             */
            if (index_dot < 0 || index_dot >= m_vexs.size())
                throw std::out_of_range("index out of range");

            visited[index_dot] = true;
            funcTrans(m_vexs[index_dot].m_data);

            vexLinkNode *p = m_vexs[index_dot].m_firstArc->m_next;
            while (p)
            {
                // 访问未访问过的邻接点
                if (!visited[p->m_adjVex])
                {
                    dfs(p->m_adjVex, funcTrans);
                }
                p = p->m_next;
            }
        }

        void bfs(
            int64_t index_dot, const std::function<void(Elem &elem)> &funcTrans = [](Elem &elem) {})
        {
            std::queue<int64_t> queue;
            if (index_dot < 0 || index_dot >= m_vexs.size())
                throw std::out_of_range("index out of range");
            queue.push(index_dot);
            visited[index_dot] = true;
            int64_t index = queue.front();
            vexLinkNode *tmp = m_vexs[index].m_firstArc->m_next;
            while (!queue.empty())
            {
                index = queue.front();
                queue.pop();
                funcTrans(m_vexs[index].m_data);
                tmp = m_vexs[index].m_firstArc->m_next;
                while (tmp)
                {
                    if (!visited[tmp->m_adjVex])
                    {
                        queue.push(tmp->m_adjVex);
                        visited[tmp->m_adjVex] = true;
                    }
                    tmp = tmp->m_next;
                }
            }
        }

    public:
        void dfs_trans(
            int64_t index_dot = 0, const std::function<void(Elem &elem)> &funcTrans = [](Elem &elem)
                                   { std::cout << elem << " "; }) noexcept
        {
            dfs(index_dot, funcTrans);
            reset_visit();
            std::cout << '\n';
        }

        void bfs_trans(
            int64_t index_dot = 0, const std::function<void(Elem &elem)> &funcTrans = [](Elem &elem)
                                   { std::cout << elem << " "; }) noexcept
        {
            bfs(index_dot, funcTrans);
            reset_visit();
            std::cout << '\n';
        }

        bool dfs_arc_exist(int64_t index_dot1, int64_t index_dot2)
        {
            reset_visit();
            if (index_dot1 < 0 || index_dot2 < 0 || index_dot1 >= m_vexs.size() || index_dot2 >= m_vexs.size())
                throw std::out_of_range("index out of range");
            /**
             * @note: 利用dfs判断两个顶点之间是否连通
             */
            dfs(index_dot1);
            bool flag = visited[index_dot2];
            reset_visit();
            return flag;
        }

        bool bfs_arc_exist(int64_t index_dot1, int64_t index_dot2)
        {
            reset_visit();
            if (index_dot1 < 0 || index_dot2 < 0 || index_dot1 >= m_vexs.size() || index_dot2 >= m_vexs.size())
                throw std::out_of_range("index out of range");
            /**
             * @note: 利用dfs判断两个顶点之间是否连通
             */
            bfs(index_dot1);
            bool flag = visited[index_dot2];
            reset_visit();
            return flag;
        }
    };

    template <typename Elem>
    class AdjListDirNet : public AdjListNet<Elem>
    {
        // 有向图的邻接表
    public:
        AdjListDirNet(const Elem *es, size_t vertexnum) : AdjListNet<Elem>(es, vertexnum) {}

        void add_arc(int64_t index_dot1, int64_t index_dot2, int64_t weight) override
        {
            AdjListNet<Elem>::add_arc(index_dot1, index_dot2, weight);
        }

        void remove_arc(int64_t index_dot1, int64_t index_dot2) override
        {
            AdjListNet<Elem>::remove_arc(index_dot2, index_dot1);
        }
    };

    template <typename Elem>
    class AdjListUndirNet : public AdjListNet<Elem>
    {
        // 无向图的邻接表
    public:
        AdjListUndirNet(const Elem *es, size_t vertexnum) : AdjListNet<Elem>(es, vertexnum) {}

        void add_arc(int64_t index_dot1, int64_t index_dot2, int64_t weight) override
        {
            AdjListNet<Elem>::add_arc(index_dot1, index_dot2, weight);
            AdjListNet<Elem>::add_arc(index_dot2, index_dot1, weight);
        }

        void remove_arc(int64_t index_dot1, int64_t index_dot2) override
        {
            AdjListNet<Elem>::remove_arc(index_dot1, index_dot2);
            AdjListNet<Elem>::remove_arc(index_dot2, index_dot1);
        }
    };

    AdjListDirNet<int> get_graph_dire()
    {
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

    AdjListUndirNet<char> get_graph_undire()
    {
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

    template <class Graph>
    void Trans(Graph &graph, int64_t index_dot, TransType type)
    {
        switch (type)
        {
        case TransType::BFS:
            graph.bfs_trans(index_dot);
            break;

        case TransType::DFS:
            graph.dfs_trans(index_dot);
            break;
        }
    }
} // namespace ds
#endif // __DIAGRAM_HPP__