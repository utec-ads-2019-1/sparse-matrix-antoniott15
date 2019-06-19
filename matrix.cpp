

#include <stdexcept>
#include "node.h"
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class Matrix
{
public:
    Node<T> *x;
    Node<T> *y;
    int columns;
    int rows;

public:
    Matrix();
    Matrix(int numbersOfX, int numbersOfY)
    {
        rows = numbersOfX;
        columns = numbersOfY;
        x = new Node<T>();
        y = new Node<T>();

        x->down = new Node<T>(0);

        Node<T> *temp = x->down;
        for (int i = 1; i < numbersOfX; ++i)
        {
            temp->down = new Node<T>(i);
            temp = temp->down;
        }

        y->next = new Node<T>(0);
        temp = y->next;

        for (int i = 1; i < numbersOfY; ++i)
        {
            temp->next = new Node<T>(i);
            temp = temp->next;
        }
    }

    void set(int posX, int posY, T data) const
    {

        if (posX >= rows || posY >= columns)
        {
            throw std::out_of_range("Out of range.");
        }
        else
        {
            Node<T> *tempRows = this->x;
            for (int i = 0; i < posX; ++i)
            {
                tempRows = tempRows->down;
            }
            if (tempRows->next)
            {
                while ((tempRows->next->positionX < posX) && tempRows->next)
                {
                    tempRows = tempRows->next;
                }
            }
            Node<T> *tempColumns = this->y;
            for (int i = 0; i < posY; ++i)
            {
                tempColumns = tempColumns->next;
            }
            if (tempColumns->down)
            {
                while ((tempColumns->down->positionY < posY) && tempColumns->down)
                {
                    tempColumns = tempColumns->down;
                }
            }
            Node<T> *tempSet = new Node<T>(tempRows->next, tempColumns->down, posX, posY, data);
            tempRows->next = tempSet;
            tempColumns->down = tempSet;
        }
    }

    T operator()(int posX, int posY)
    {
        Node<T> *temp = y;
        for (int i = 0; i < posY; ++i)
        {
            temp = temp->next;
        }
        if (temp->down)
        {
            while (temp->down)
            {
                if (temp->down->positionX == posX)
                {
                    return temp->down->data;
                }
                temp = temp->down;
            }
            return 0;
        }
        else
        {
            return 0;
        }
    }

    Matrix<T> operator*(Matrix<T> other)
    {

        if (this->columns == other.rows)
        {
            Matrix<int> result(rows, other.columns);

            for (int i = 0; i < rows; ++i)
            {
                int temp = 0;

                for (int j = 0; j < other.columns; ++j)
                {
                    for (int k = 0; k < columns; ++k)
                    {

                        temp += (((*this)(i, k)) * ((other)(k, j)));
                    }
                    if (temp)
                    {
                        result.set(i, j, temp);
                    }
                }
            }
            return result;
        }
        else
        {
            throw std::invalid_argument("Invalid argument.");
        }
    }

    Matrix<T> operator*(T scalar)
    {

        Matrix<int> result(rows, columns);
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                if ((*this)(i, j))
                {
                    result.set(i, j, (((*this)(i, j) * scalar)));
                }
            }
        }
        return result;
    }

    Matrix<T> operator+(Matrix<T> other)
    {

        if (this->columns == other.columns && this->rows == other.rows)
        {
            Matrix<int> result(rows, columns);

            for (int i = 0; i < rows; ++i)
            {
                for (int j = 0; j < columns; ++j)
                {
                    if ((*this)(i, j) + (other)(i, j))
                    {
                        result.set(i, j, ((*this)(i, j) + (other)(i, j)));
                    }
                }
            }
            return result;
        }
        else
        {
            throw std::invalid_argument("Invalid argument.");
        }
    }

    Matrix<T> operator-(Matrix<T> other)
    {

        if (this->columns == other.columns && this->rows == other.rows)
        {
            Matrix<int> result(rows, columns);

            for (int i = 0; i < rows; ++i)
            {
                for (int j = 0; j < columns; ++j)
                {
                    if ((*this)(i, j) - (other)(i, j))
                    {
                        result.set(i, j, ((*this)(i, j) - (other)(i, j)));
                    }
                }
            }
            return result;
        }
        else
        {
            throw std::invalid_argument("Invalid argument.");
        }
    }

    Matrix<T> transpose()
    {
        Matrix<int> result(columns, rows);

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                if ((*this)(i, j))
                {
                    result.set(j, i, (*this)(i, j));
                }
            }
        }
        return result;
    }

    void print()
    {
        for (int x = 0; x < rows; ++x)
        {
            for (int y = 0; y < columns; ++y)
            {
                int d = (*this)(x, y);
                cout << d << " \t";
            }
            cout << endl;
        }
    }

    //~Matrix();
};

int main()
{

    Matrix<int> matrixA(5, 5);
    Matrix<int> matrixB(5, 5);

    matrixA.set(0, 0, 5);
    matrixA.set(1, 2, 5);
    matrixA.set(1, 3, 5);
    matrixA.set(0, 2, 5);
    matrixA.set(2, 3, 5);
    matrixA.set(1, 4, 5);
    matrixA.set(4, 1, 5);
    matrixA.set(3, 2, 5);
    matrixA.set(3, 3, 5);
    matrixA.set(3, 4, 5);
    matrixA.set(2, 4, 5);
    matrixA.set(0, 1, 4);
    matrixA.set(0, 1, 7);

    matrixB.set(0, 0, 5);
    matrixB.set(1, 2, 5);
    matrixB.set(1, 3, 5);
    matrixB.set(0, 2, 5);
    matrixB.set(2, 3, 5);
    matrixB.set(1, 4, 5);
    matrixB.set(4, 1, 5);
    matrixB.set(3, 2, 3);
    matrixB.set(3, 3, 5);
    matrixB.set(3, 4, 2);
    matrixB.set(2, 4, 5);
    matrixB.set(0, 1, 4);
    matrixB.set(0, 1, 10);

    matrixA.print();
    cout << "====================" << endl;
    auto j = matrixA * 3;
    j.print();
    cout << "====================" << endl;

    cout << "====================" << endl;

    (matrixA * matrixB).print();
    cout << "====================" << endl;

    (matrixA + matrixB).print();

    cout << "====================" << endl;

    matrixA.transpose();
    cout << "====================" << endl;

    (matrixA - matrixB).print();

    cout << "====================" << endl;
    return 0;
}
