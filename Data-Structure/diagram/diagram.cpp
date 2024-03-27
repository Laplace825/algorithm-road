#include <iostream>
#include "diagram.hpp"

int main()
{
    auto dir_graph = ds::get_graph_dire();
    dir_graph.print();
    dir_graph.dfs_trans(0);
    dir_graph.bfs_trans(0);
    ds::Trans(dir_graph, 0, ds::TransType::DFS);
    auto undir_graph = ds::get_graph_undire();
    undir_graph.print();
    undir_graph.dfs_trans(0);
    undir_graph.bfs_trans(0);
    ds::Trans(undir_graph, 0, ds::TransType::BFS);
    std::cout << dir_graph.bfs_arc_exist(1, 3) << std::endl;
}
