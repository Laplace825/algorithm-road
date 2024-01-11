#include "LinkBinaryTree.h"
#include "SqlBinaryTree.h"
#include <iostream>

int main()
{
    char pre[] = {'A', 'B', 'D', 'E', 'G', 'H', 'C', 'F', 'I'}; // 先序序列
    char in[] = {'D', 'B', 'G', 'E', 'H', 'A', 'C', 'F', 'I'};  // 中序序列
    /*
            A
        ____||___
        B       C
     ___||___   ||_
     D     E      F
          _||_   ||_
         G   H     I
    */
    BT::LinkBinaryTree<char> LinkBtr{std::move(BT::create(pre, in, 9))};
    BT::printTree(LinkBtr, BT::PRE);
    BT::printTree(LinkBtr, BT::IN);
    BT::printTree(LinkBtr, BT::POST);
    char arr[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    /*
            A
        ____||___
        B       C
     ___||___   _||
     D     E   F
    */
    BT::SqlBinaryTree<char> sqlBtr{arr, 6};
    BT::printTree(sqlBtr, BT::PRE);
    BT::printTree(sqlBtr, BT::IN);
    BT::printTree(sqlBtr, BT::POST);
    std::cout << sqlBtr.findNearParent(1, 4) << '\n';
}
