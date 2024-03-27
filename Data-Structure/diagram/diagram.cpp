#include <iostream>
#include "diagram.hpp"

int main()
{
    auto graph = ds::get_graph_dire();
    graph.print();
    graph.dfs_trans(0);
    graph.bfs_trans(0);
    ds::Trans(graph, 0, ds::TransType::DFS);
}
