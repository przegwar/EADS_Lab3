#include <iostream>
#include "AVL_Main_Implementation.h"

using namespace std;

int main()
{
    AVL_Tree<int,int> avl_tree;
    avl_tree.Add_Node(1,1);
    avl_tree.Add_Node(2,2);
    avl_tree.Add_Node(3,3);
    avl_tree.Add_Node(4,4);
    avl_tree.Add_Node(5,5);
    avl_tree.Add_Node(6,6);
    avl_tree.Display_Tree();
    return 0;
}
