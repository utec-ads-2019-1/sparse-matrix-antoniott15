#ifndef SPARSE_MATRIX_NODE_H
#define SPARSE_MATRIX_NODE_H

template <typename T>
class Matrix;

template <typename T>
class Node
{
public:
    int positionX, positionY;
    T data;
    Node<T> *next, *down;

    Node()
    {
        this->next = nullptr;
        this->down = nullptr;
    };
    Node(int position)
    {
        this->positionX = positionX;
        this->next = nullptr;
        this->down = nullptr;
    }

    Node(Node *next, Node *down, int positionX, int positionY, T data)
    {
        this->positionX = positionX;
        this->positionY = positionY;
        this->next = next;
        this->down = down;
        this->data = data;
    }
    friend class Matrix<T>;
};

#endif //SPARSE_MATRIX_NODE_H
