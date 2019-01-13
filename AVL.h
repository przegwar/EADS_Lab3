#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED

template <class K,class I>
class Node
{
    K key;
    I info;
    Node* right;
    Node* left;
    int height;

    public:
        Node(Node* newRight, Node* newLeft,K newKey, I newInfo)
        {
            right = newRight;
            left = newLeft;
            key = newKey;
            info = newInfo;
            height = 1;
        }

        I Get_Info()
        {
            return info;
        }

        K Get_Key()
        {
            return key;
        }

        Node* Get_Left()
        {
            return left;
        }

        Node* Get_Right()
        {
            return right;
        }

        int Get_Height()
        {
            return height;
        }


        void Set_Info(I newInfo)
        {
           info = newInfo;
        }

        void Set_Left(Node* newLeft)
        {
            left = newLeft;
        }

        void Set_Right(Node* newRight)
        {
            right = newRight;
        }

        void Set_Height(int newHeight)
        {
            height = newHeight;
        }

        void Set_Key(K newKey)
        {
            key = newKey;
        }
};

#endif // AVL_H_INCLUDED
