#include "LinkBinaryTree.h"
#include "SqlBinaryTree.h"
#include <iostream>

int main()
{
    constexpr char pre[] = {'A', 'B', 'D', 'H', 'I', 'E', 'J', 'K', 'C', 'F'}; // 先序序列
    constexpr char in[] = {'H', 'D', 'I', 'B', 'J', 'K', 'E', 'A', 'C', 'F'};  // 中序序列
    /*
            A
        __//___
        B       C
     _//___     //_
     D     E      F
  _//_  _//_
  H  I  J
       //_
         K
    */
    BT::LinkBinaryTree<char> LinkBtr{std::move(BT::create(pre, in, 10))};
    std::cout << "pre,in,post,double with recursion: ";
    BT::printTree(LinkBtr, BT::print::PRE);
    std::cout << "==================\n";
    BT::printTree(LinkBtr, BT::print::IN);
    std::cout << "==================\n";
    BT::printTree(LinkBtr, BT::print::POST);
    std::cout << "==================\n";
    BT::printTree(LinkBtr, BT::print::DOUBLE);
    std::cout << "==================\n";
    std::cout << "pre,in,post,level with no recursion: \n";
    LinkBtr.preOrder();
    std::cout << "==================\n";
    LinkBtr.inOrder();
    std::cout << "==================\n";
    LinkBtr.postOrder();
    std::cout << "==================\n";
    LinkBtr.levelOrder();
    std::cout << "==================\n";
    std::cout << "depth: " << LinkBtr.depth() << '\n';
    std::cout << "maxWideth: " << LinkBtr.maxWidth() << '\n';
    std::cout << "leafNum: " << BT::leafNum(LinkBtr) << '\n';
    constexpr char arr[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    // /*
    //         A
    //     ___//____
    //     B        C
    //  __//___   _//
    //  D     E   F
    // */
    BT::SqlBinaryTree<char> sqlBtr{arr, 6};
    std::cout << "pre,in,post,level with recursion: \n";
    std::cout << "==================\n";
    BT::printTree(sqlBtr, BT::print::PRE);
    std::cout << "==================\n";
    BT::printTree(sqlBtr, BT::print::IN);
    std::cout << "==================\n";
    BT::printTree(sqlBtr, BT::print::POST);
    std::cout << "==================\n";
    BT::printTree(sqlBtr, BT::print::LEVEL);
    std::cout << "==================\n";
    std::cout << "findNearParent:" << sqlBtr.findNearParent(1, 4) << '\n';
}
