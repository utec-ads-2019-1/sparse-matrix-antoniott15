

#include <stdexcept>
#include "node.h"
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class Matrix
{
private:
    Node<T> *x;
    Node<T> *y;
    int rows, columns;

public:
    Matrix();
    Matrix(int numberofRows, int numberofColumns)
    {
        rows = numberofRows;
        columns = numberofColumns;
        x = new Node<T>();
        y = new Node<T>();
        x->down = new Node<T>(0);
        Node<T> *temp = x->down;

        for (int i = 1; i < numberofRows; ++i)
        {
            temp->down = new Node<T>(i);
            temp = temp->down;
        }

        y->next = new Node<T>(0);
        temp = y->next;

        for (int i = 1; i < numberofColumns; ++i)
        {
            temp->next = new Node<T>(i);
            temp = temp->next;
        }
    };

    void set(int positionX, int positionY, T data)
    {
        if (positionX >= rows || positionY >= columns)
        {
            throw std::invalid_argument( "Invalid argument" );
        }
        Node<T> *TempRow = this->x;
        for (int i = 0; i < positionX; i++)
        {
            TempRow = TempRow->down;
        }

        if (TempRow->next)
        {
            while ((TempRow->next->positionX < positionX) && TempRow->next)
            {
                TempRow = TempRow->next;
            }
        }

        Node<T> *TempCol = y;
        for (int i = 0; i < positionY; i++)
        {
            TempCol = TempCol->next;
        }
        if (TempCol->down)
        {
            while ((TempCol->down->positionY < positionY) && TempCol->down)
            {
                TempCol = TempCol->down;
            }
        }
        Node<T> *setTemp = new Node<T>(TempRow->next, TempCol->down, positionX, positionY, data);
        TempRow->next = setTemp;
        TempCol->down = setTemp;
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
            }
            return 0;
        }
        return 0;
    }
    Matrix<T> operator*(T scalar)
    {
        Matrix<T> result(rows, columns);
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                if ((*this)(i, j))
                {
                    result.set(i,j,(((*this)(i,j)*scalar)));
                }
            }
        }
        return result;
    }
  
    Matrix<T> operator*(Matrix<T> other)
    {
        if(this->columns == other.rows)
            {  
                Matrix<T> result(rows,columns);
          
                      for (int i = 0; i < rows; ++i)
                      {
                        for (int j = 0; j < columns; ++j)
                          {
                           if ((*this)(i,j)+(other)(i,j))
                           {
                              result.set(i,j,((*this)(i,j)+(other)(i,j)));
                           }
                          }
                      }
                      return result;
            }else
            {
                return *this;
                throw std::invalid_argument( "Invalid argument" );
            }
    }
    Matrix<T> operator+(Matrix<T> other){
    if(this->columns == other.columns && this->rows == other.rows)
            {  
                Matrix<int> result(rows,columns);
          
                      for (int i = 0; i < rows; ++i)
                      {
                          for (int j = 0; j < columns; ++j)
                          {
                           if ((*this)(i,j)+(other)(i,j))
                           {
                              result.set(i,j,((*this)(i,j)+(other)(i,j)));
                           }
                          }
                      }
                      return result;
            }
            return *this;
            throw std::invalid_argument( "Invalid argument" );
        }
    Matrix<T> operator-(Matrix<T> other){
        if(this->columns == other.columns && this->rows == other.rows)
            {
                Matrix<T> result(rows,columns);
               
                for (int i = 0; i < rows; ++i)
                {
                    for (int j = 0; j < columns; ++j)
                    {
                        if ((*this)(i,j)-(other)(i,j))
                        {
                           result.set(i,j,((*this)(i,j)-(other)(i,j)));
                        }              
                    }
                }
                return result;
            }
             return *this;
            throw std::invalid_argument( "Invalid argument" );
    }

    Matrix<T> transpose(){

        Matrix<int> result(columns,rows);
            for (int i = 0; i < rows; ++i)
            { 
                for (int j = 0; j < columns; ++j)
                {
                    cout << "i " << i << " j: " <<j << endl;
                    result.set(j,i,(*this)(i,j));

                }
            }
            return result;
    }
    void print(){
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
                {
                    int number = (*this)(i,j);
                    cout << number << "\t";
                }
                cout << "\n";
        }
    }


    //~Matrix();
};



int main()
{
    Matrix<int> matrix(3, 5);

    matrix.set(1, 2, 3);
    matrix.set(2, 1, 10);
    matrix.set(1, 3, 13);
    matrix.set(1, 1, 43);
    matrix.set(2, 2, 32);
    matrix.set(2, 4, 34);

    (matrix.transpose()).print();

    return 0;
}
