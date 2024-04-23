/*
 * @Author: laplace825
 * @Date: 2024-03-25 19:17:14
 * @LastEditors: laplace825
 * @LastEditTime: 2024-04-17 08:44:10
 * @FilePath: /algorithm-road/Data-Structure/diagram/diagram.cpp
 * @Description: 
 * 
 * Copyright (c) 2024 by laplace825, All Rights Reserved. 
 */
#include <iostream>
#include "diagram.hpp"
#include <format>

int main() {
    auto dirListGraph = ds::get_graph_dire();
    auto undirListGraph = ds::get_graph_undire();
    auto dirMatrixGraph = ds::get_graph_matrix_dire();

    std::cout << "Dir List Graph\n";
    dirListGraph.print();
    std::cout << std::format("bfs_arc_exist(1,3){}\n",
                             dirListGraph.bfs_arc_exist(1, 3));
    std::cout << "========================================\n";

    std::cout << "dir List Graph\n";
    undirListGraph.print();
    std::cout << std::format("is tree?:{}\n", undirListGraph.is_tree());
    std::cout << std::format("the {} length path exist:{}\n", 4, undirListGraph.path_exist(4));
    std::cout << std::format("the {} length path exist:{}\n", 8, undirListGraph.path_exist(8));
    std::cout << "=========================================\n";
    std::cout << "Undir Matrix Graph\n";
    std::cout << std::format("the {} length path exist between {} and {} is {}\n", 2, 1,
                             4, dirMatrixGraph.exit_path_length(1, 4, 2));
    std::cout << std::format("the {} length path exist between {} and {} is {}\n", 2, 0,
                             2, dirMatrixGraph.exit_path_length(0, 2, 2));
    std::cout << std::format("the longest path is {}\n", dirMatrixGraph.longest_path());
    auto afterTopo = dirMatrixGraph.topologicalSort();
    std::cout << "After Topological Sort\n";
    std::for_each(
            afterTopo.begin(), afterTopo.end(),
            [](int i) { std::cout << i << " "; }
    );
    std::cout << "\n======================================\n";

    return 0;
}