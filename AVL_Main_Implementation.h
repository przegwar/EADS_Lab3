#ifndef AVL_MAIN_IMPLEMENTATION_H_INCLUDED
#define AVL_MAIN_IMPLEMENTATION_H_INCLUDED

#include <iostream>
#include <stack>
#include "AVL.h"
using namespace std;

template<typename K, typename I>
class AVL_Tree
{
    Node<K,I>* head = NULL;

    void Display_Preorder(Node<K,I> *root)
    {
        if(root != NULL)
        {
            std::cout<< root->Get_Info();
            Display_Preorder(root->Get_Left());
            Display_Preorder(root->Get_Right());
        }
    }

    void Display_Inorder(Node<K,I> *root)
    {
        if(root != NULL)
        {
            if(root->Get_Left()) Display_Inorder(root->Get_Left());
            std::cout<< root->Get_Info();
            if(root->Get_Right()) Display_Inorder(root->Get_Right());
        }
    }

    int Count_Nodes(Node<K,I> *tree)
    {
        int c =  1;
        if (tree ==NULL)
            return 0;
        else
        {
            c += Count_Nodes(tree->Get_Left());
            c += Count_Nodes(tree->Get_Right());
            return c;
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

    Node<K,I> * Minimal_Value_Node (Node<K,I>* node)
    {
        Node<K,I>* current = node;
        while (current->Get_Left() != NULL)
            current = current->Get_Left();

        return current;
    }

    Node<K,I>* Insert_Node(Node<K,I>* node, K key, I info)
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

    Node<K,I>* Delete_Node(Node<K,I>* root, int key)
    {
        if (root == NULL)
            return root;

        if ( key < root->Get_Key() )
            root->Set_Left(Delete_Node(root->Get_Left(), key));

        else if( key > root->Get_Key() )
            root->Set_Right(Delete_Node(root->Get_Right(), key));

        else
        {
            if( (root->Get_Left() == NULL) || (root->Get_Right() == NULL) )
            {
                Node<K,I> *temp = root->Get_Left() ? root->Get_Left() : root->Get_Right();

                if (temp == NULL)
                {
                    temp = root;
                    root = NULL;
                }
                else
                 *root = *temp;

                delete(temp);
            }
            else
            {
                Node<K,I>* temp = Minimal_Value_Node(root->Get_Right());

                root->Set_Key(temp->Get_Key());
                root->Set_Info(temp->Get_Info());

                root->Set_Right(Delete_Node(root->Get_Right(), temp->Get_Key()));
            }
        }

        if (root == NULL)
          return root;

        root->Set_Height( 1 + max(Height(root->Get_Left()),
                               Height(root->Get_Right())));

        int balance = Get_Balance(root);

        if (balance > 1 && Get_Balance(root->Get_Left()) >= 0)
            return Right_Rotate(root);

        if (balance > 1 && Get_Balance(root->Get_Left()) < 0)
        {
            root->Set_Left(Left_Rotate(root->Get_Left()));
            return Right_Rotate(root);
        }

        if (balance < -1 && Get_Balance(root->Get_Right()) <= 0)
            return Left_Rotate(root);

        if (balance < -1 && Get_Balance(root->Get_Right()) > 0)
        {
            root->Set_Right(Right_Rotate(root->Get_Right()));
            return Left_Rotate(root);
        }

        return root;
    }

    static Node<K,I> * Copy_Nodes( Node<K,I> * t)
    {
        if ( t != NULL )
        {
            Node<K,I>* left = Copy_Nodes( t->Get_Left() );
            Node<K,I>* right = Copy_Nodes( t->Get_Right());
            return new Node<K,I>(right, left,t->Get_Key(), t->Get_Info(),t->Get_Height());
        }
        else
        {
            return NULL;
        }
    }

    static void Destroy_Nodes( Node<K,I> * t)
    {
        if ( t != NULL )
        {
            Destroy_Nodes( t->Get_Left() );
            Destroy_Nodes( t->Get_Right());
            delete(t);
        }
    }

    K Find_By_Info(Node<K,I> *root, I seekedInfo)
    {
        if(root != NULL)
        {
            if(root->Get_Info()==seekedInfo)
            {
                return root->Get_Key();
            }
            else
            {
                Find_By_Info(root->Get_Left(),seekedInfo);
                Find_By_Info(root->Get_Right(),seekedInfo);
            }
        }
        else return NULL;
    }

    I Find_By_Key(Node<K,I> *root, K seekedKey)
    {
        if(root != NULL)
        {
            if(root->Get_Key()==seekedKey)
            {
                return root->Get_Info();
            }
            else
            {
                Find_By_Key(root->Get_Left(),seekedKey);
                Find_By_Key(root->Get_Right(),seekedKey);
            }
        }
        else return NULL;
    }

public:

    AVL_Tree<K,I>() = default;

    AVL_Tree( const AVL_Tree & rhs )
    {
        head = Copy_Nodes( rhs.head );
    }

    void Display_Tree()
    {
        Display_Preorder(head);
        std::cout<<endl;
    }

    void operator=(const AVL_Tree & rhs)
    {
        Destroy_Nodes(head);
        head = Copy_Nodes( rhs.head );
    }

    void Clear_Tree()
    {
        Destroy_Nodes(head);
        head = NULL;
    }

    void Add_Node(K key,I info)
    {
        head = Insert_Node(head,key,info);
    }

    int Size()
    {
        return Count_Nodes(head);
    }

    K Find_Key_By_Info(I seekedInfo)
    {
        return Find_By_Info(head,seekedInfo);
    }

    I Find_Info_By_Key(K seekedKey)
    {
        return Find_By_Key(head,seekedKey);
    }

    void Delete(K key)
    {
        head = Delete_Node(head,key);
    }
};

#endif // AVL_MAIN_IMPLEMENTATION_H_INCLUDED
