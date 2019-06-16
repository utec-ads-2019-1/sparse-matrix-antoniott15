#ifndef SPARSE_MATRIX_MATRIX_H
#define SPARSE_MATRIX_MATRIX_H

#include <stdexcept>
#include "node.h"
using namespace std;

template <typename T>
class Matrix
{
private:
    Node<T> *hRows;
    Node<T> *hColumns;
    int rows, columns;

public:
    Matrix(int rows, int columns)
    {
        this->rows = rows;
        this->columns = columns;
        hRows = new Node<T>();
        hColumns = new Node<T>();
        hRows->down = new Node<T>(0);
        Node<T> *temp = hRows->down;

        for (int i = 1; i < rows; ++i)
        {
            temp->down = new Node<T>(i);
            temp = temp->down;
        }

        hColumns->next = new Node<T>(0);
        temp = hColumns->next;

        for (int i = 1; i < columns; ++i)
        {
            temp->next = new Node<T>(i);
            temp = temp->next;
        }
    };

    void set(int rows,int columns, T data){
        if(rows >= this->rows || columns >= this->columns){
            throw;
        }
        Node<T>* TempRow = this->rows;
        for(int i = 0; i < rows; i++){
            TempRow = TempRow->down;
        }

        if(TempRow->next){
            while((TempRow->next->positionX < rows)&&TempRow->next){
                TempRow=TempRow->next;
            }
        }

    }
    T operator()(int, int) const;
    Matrix<T> operator*(T scalar) const;
    Matrix<T> operator*(Matrix<T> other) const;
    Matrix<T> operator+(Matrix<T> other) const;
    Matrix<T> operator-(Matrix<T> other) const;
    Matrix<T> transpose() const;
    void print() const;

    ~Matrix();
};

#endif //SPARSE_MATRIX_MATRIX_H