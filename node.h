#ifndef SPARSE_MATRIX_NODE_H
#define SPARSE_MATRIX_NODE_H

template <typename T>
class Node
{
public:
    int positionX, positionY;
    T data;
    Node *next, *down;

    Node()
    {
        next = nullptr;
        down = nullptr;
    };
    Node(int position)
    {
        positionX = position;
        next = nullptr;
        down = nullptr;
    }

    Node(Node *next, Node *down, int posX, int posY, T data)
    {
        this->positionX = posX;
        this->positionY = posY;
        this->next = next;
        this->down = down;
        this->data = data;
    }
};

#endif //SPARSE_MATRIX_NODE_H
