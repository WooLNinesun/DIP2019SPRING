#include <vector>

#ifndef __MATRIX_H
#define __MATRIX_H

using namespace std;

template <typename T>
class Matrix {
  public:
    vector<T> data;
    unsigned rows;
    unsigned cols;

  public:
    Matrix();
    Matrix(unsigned rows, unsigned cols);
    Matrix(unsigned rows, unsigned cols, T init);
    virtual ~Matrix();

  public:
    T &operator()(const unsigned &i, const unsigned &j);
    T &operator()(const unsigned &i);
    Matrix<T> operator+(const Matrix<T> &rhs);
    Matrix<T> &operator+=(const Matrix<T> &rhs);
    Matrix<T> operator-(const Matrix<T> &rhs);
    Matrix<T> &operator-=(const Matrix<T> &rhs);

  public:
    unsigned size();
    void resize(unsigned rows, unsigned cols, T init);
};

#include "matrix.cpp"

#endif
