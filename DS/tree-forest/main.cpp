#include "tree-forest.hpp"
#include <memory>
#include <vector>
#include <chrono>

class TimerKeeper
{
public:
    TimerKeeper() : start_time(std::chrono::high_resolution_clock::now()) {}
    ~TimerKeeper()
    {
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration =
            std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
        std::cout << "Time taken: " << duration.count() << " ns" << std::endl;
    }

private:
    std::chrono::high_resolution_clock::time_point start_time;
};

int main()
{
    std::unique_ptr<char> data(new char[]{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                          'I', 'J', 'K', 'L', 'M', 'N', 'Z'});
    std::unique_ptr<int64_t> index(
        new int64_t[]{-1, 0, 1, 2, 3, 4, 5, 5, 7, 8, 9, 10, 11, 12, 13});

    tree::SeqTree<char> stree(data.get(), index.get(), 15);
    stree.print();
    std::cout << "Height: " << stree.height() << '\n';
    std::cout << "degree: " << stree.degree() << '\n';
    std::cout << "leaf: " << stree.leafNum() << '\n';
    std::cout << "--------------------------------\n";
    tree::LinkTree<char> ltree(data.get(), index.get(), 15);
    ltree.print();
    std::cout << "Height: " << ltree.height_DFS() << '\n';
    std::cout << "degree: " << ltree.degree() << '\n';
    std::cout << "leaf: " << ltree.leafNum() << '\n';
    std::cout << "--------------------------------\n";

    {
        std::cout << "With BFS:";
        TimerKeeper tk;
        ltree.height_BFS();
    }
    // 十倍差距，说明DFS更快
    {
        std::cout << "With DFS:";
        TimerKeeper tk;
        ltree.height_DFS();
    }
}
