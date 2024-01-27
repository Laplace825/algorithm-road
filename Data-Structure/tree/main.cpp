#include "LinkBinaryTree.h"
#include "SqlBinaryTree.h"
#include <iostream>

int main()
{
    char pre[] = {'A', 'B', 'D', 'H', 'I', 'E', 'J', 'K', 'C', 'F'}; // 先序序列
    char in[] = {'H', 'D', 'I', 'B', 'J', 'K', 'E', 'A', 'C', 'F'};  // 中序序列
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
    // BT::printTree(LinkBtr, BT::PRE);
    // BT::printTree(LinkBtr, BT::IN);
    // BT::printTree(LinkBtr, BT::POST);
    // BT::printTree(LinkBtr, BT::LEVEL);
    // std::cout << "preOrder with no recursion: ";
    // LinkBtr.preOrder();
    std::cout << "inOrder with no recursion: ";
    LinkBtr.inOrder();
    // LinkBtr.postOrder();
    // std::cout << "depth: " << LinkBtr.depth() << '\n';
    // std::cout << "maxWideth: " << LinkBtr.maxWidth() << '\n';
    // std::cout << "leafNum: " << BT::leafNum(LinkBtr) << '\n';
    // char arr[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    // /*
    //         A
    //     ___//____
    //     B        C
    //  __//___   _//
    //  D     E   F
    // */
    // BT::SqlBinaryTree<char> sqlBtr{arr, 6};
    // BT::printTree(sqlBtr, BT::PRE);
    // BT::printTree(sqlBtr, BT::IN);
    // BT::printTree(sqlBtr, BT::POST);
    // BT::printTree(sqlBtr, BT::LEVEL);
    // std::cout << "findNearParent:" << sqlBtr.findNearParent(1, 4) << '\n';
}
