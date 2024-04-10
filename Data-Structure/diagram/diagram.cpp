#include <iostream>
#include "diagram.hpp"
#include <format>

int main() {
    auto dirListGraph = ds::get_graph_dire();
    auto undirListGraph = ds::get_graph_undire();
    auto undirMatrixGraph = ds::get_graph_matrix_dire();

    std::cout << "Dir List Graph\n";
    dirListGraph.print();
    std::cout << std::format("bfs_arc_exist(1,3){}\n",
                             dirListGraph.bfs_arc_exist(1, 3));
    std::cout << "========================================\n";

    std::cout << "Undir List Graph\n";
    undirListGraph.print();
    std::cout << std::format("is tree?:{}\n", undirListGraph.is_tree());
    std::cout << std::format("the {} length path exist:{}\n", 4, undirListGraph.path_exist(4));
    std::cout << std::format("the {} length path exist:{}\n", 8, undirListGraph.path_exist(8));
    std::cout << "=========================================\n";

    std::cout << "Undir Matrix Graph\n";
    std::cout << std::format("the {} length path exist between {} and {} is {}\n", 2, 1,
                             4, undirMatrixGraph.exit_path_length(1, 4, 2));
    std::cout << std::format("the {} length path exist between {} and {} is {}\n", 1, 1,
                             4, undirMatrixGraph.exit_path_length(1, 4, 1));
    std::cout << std::format("the longest path is {}\n", undirMatrixGraph.longest_path());
    auto afterTopo = undirMatrixGraph.topologicalSort();
    std::cout << "After Topological Sort\n";
    std::for_each(
            afterTopo.begin(), afterTopo.end(),
            [](int i) { std::cout << i << " "; }
    );
    std::cout << "\n======================================\n";

    return 0;
}
