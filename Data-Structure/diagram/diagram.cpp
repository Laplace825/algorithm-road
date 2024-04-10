#include <iostream>
#include "diagram.hpp"

int main()
{
    auto dir_graph = ds::get_graph_dire();
    for (const auto &i : dir_graph.topo_sort())
        std::cout << i << ' ';
    std::cout << '\n';
    //     dir_graph.print();
    //     dir_graph.dfs_trans(0);
    //     dir_graph.bfs_trans(0);
    //     ds::Trans(dir_graph, 0, ds::TransType::DFS);
    //     auto undir_graph = ds::get_graph_undire();
    //     undir_graph.print();
    //     undir_graph.dfs_trans(1);
    //     undir_graph.bfs_trans(0);
    //     ds::Trans(undir_graph, 0, ds::TransType::BFS);
    //     std::cout << dir_graph.bfs_arc_exist(1, 3) << std::endl;
    //     std::cout << undir_graph.path_exist(3) << '\n';
    //     std::cout << dir_graph.longest_path() << '\n';
    //     ds::timer ti;
    //     std::cout << undir_graph.path_exist(3) << '\n';
    //     std::cout << ti.elapsed() << '\n';
    //     ti.reset();
    //     undir_graph.dfs_trans(0);
    //     std::cout << ti.elapsed() << '\n';

    auto dir_graph_Matrix = ds::get_graph_matrix_dire();
    auto res = dir_graph_Matrix.topologicalSort();
    // std::cout << dir_graph_Matrix.longest_path() << '\n';
    //     std::cout << dir_graph_Matrix.exit_path_number(0, 4, 2) << std::endl;
    // auto undir_list_graph = ds::get_graph_undire();
    // undir_list_graph.print();
    // std::cout << undir_list_graph.is_tree() << std::endl;
}
