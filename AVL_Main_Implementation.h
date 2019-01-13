#ifndef AVL_MAIN_IMPLEMENTATION_H_INCLUDED
#define AVL_MAIN_IMPLEMENTATION_H_INCLUDED

#include <iostream>
#include "AVL.h"
using namespace std;

template<class K, class I>
class AVL_Tree
{
    Node<K,I>* head = NULL;

    void Display_Tree_Preorder(struct Node<K,I> *root)
    {
        if(root != NULL)
        {
            std::cout<< root->Get_Info();
            Display_Tree_Preorder(root->Get_Left());
            Display_Tree_Preorder(root->Get_Right());
        }
    }

    Node<K,I>* New_Node(K key,I info)
    {
        Node<K,I>* new_node = new Node<K,I>(NULL,NULL,key,info);
        head = head == NULL ? new_node:head;
        return new_node;
    }

    int Height(Node<K,I>* node)
    {
        if(node == NULL)
        {
            return 0;
        }
        return node->Get_Height();
    }

    int Get_Balance(Node<K,I>* node)
    {
        if (node == NULL)
            return 0;
        return Height(node->Get_Left()) - Height(node->Get_Right());
    }

    Node<K,I> *Right_Rotate(Node<K,I> *node1)
    {
        Node<K,I> *node2 = node1->Get_Left();
        Node<K,I> *node3 = node2->Get_Right();

        node2->Set_Right(node1);
        node1->Set_Left(node3);

        node1->Set_Height(max(Height(node1->Get_Left()), Height(node1->Get_Right()))+1);
        node2->Set_Height(max(Height(node2->Get_Left()), Height(node2->Get_Right()))+1);

        return node2;
    }

    Node<K,I> *Left_Rotate(Node<K,I> *node2)
    {
        Node<K,I> *node1 = node2->Get_Right();
        Node<K,I> *node3 = node1->Get_Left();

        node1->Set_Left(node2);
        node2->Set_Right(node3);

        node2->Set_Height(max(Height(node2->Get_Left()), Height(node2->Get_Right()))+1);
        node1->Set_Height(max(Height(node1->Get_Left()), Height(node1->Get_Right()))+1);

        return node1;
    }

    struct Node<K,I>* Insert_Node(Node<K,I>* node, K key, I info)
    {
        if (node == NULL)
            return(New_Node(key,info));

        if (key < node->Get_Key())
            node->Set_Left(Insert_Node(node->Get_Left(), key,info));
        else if (key > node->Get_Key())
            node->Set_Right(Insert_Node(node->Get_Right(), key,info));
        else
            return node;

        node->Set_Height(1 + max(Height(node->Get_Left()),
                               Height(node->Get_Right())));

        int balance = Get_Balance(node);

        if (balance > 1 && key < node->Get_Left()->Get_Key())
            return Right_Rotate(node);

        if (balance < -1 && key> node->Get_Right()->Get_Key())
            return Left_Rotate(node);

        if (balance > 1 && key > node->Get_Left()->Get_Key())
        {
            node->Set_Left(Left_Rotate(node->Get_Left()));
            return Right_Rotate(node);
        }

        if (balance < -1 && key < node->Get_Right()->Get_Key())
        {
            node->Set_Right(Right_Rotate(node->Get_Right()));
            return Left_Rotate(node);
        }

        return node;
    }

public:


    void Display_Tree()
    {
        Display_Tree_Preorder(head);
    }

    void Add_Node(K key,I info)
    {
        head = Insert_Node(head,key,info);
    }
};

#endif // AVL_MAIN_IMPLEMENTATION_H_INCLUDED
