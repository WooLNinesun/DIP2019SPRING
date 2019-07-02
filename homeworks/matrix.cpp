#ifndef __MATRIX_CPP
#define __MATRIX_CPP

#include "matrix.h"

// None Parameter Constructor
template <typename T>
Matrix<T>::Matrix() {}

// Parameter Constructor
template <typename T>
Matrix<T>::Matrix(unsigned rows, unsigned cols) {
    resize(rows, cols, 0);
}

template <typename T>
Matrix<T>::Matrix(unsigned rows, unsigned cols, T init) {
    resize(rows, cols, init);
}

// (Virtual) Destructor
template <typename T>
Matrix<T>::~Matrix() {}

template <typename T>
void Matrix<T>::resize(unsigned rows, unsigned cols, T init) {
    this->data.resize(rows * cols, init);
    this->rows = rows, this->cols = cols;
}

template <typename T>
unsigned Matrix<T>::size() {
    return this->rows * this->cols;
}

// Access the individual elements
template <typename T>
T &Matrix<T>::operator()(const unsigned &i, const unsigned &j) {
    return this->data[i * this->cols + j];
}
template <typename T>
T &Matrix<T>::operator()(const unsigned &i) {
    return this->data[i];
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &rhs) {
    Matrix result(*this);
    result += rhs;
    return result;
}

template <typename T>
Matrix<T> &Matrix<T>::operator+=(const Matrix<T> &rhs) {
    for (unsigned i = 0; i < size(); i++) {
        this->data[i] += rhs.data[i];
    }

    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &rhs) {
    Matrix result(*this);
    result -= rhs;
    return result;
}

template <typename T>
Matrix<T> &Matrix<T>::operator-=(const Matrix<T> &rhs) {
    for (unsigned i = 0; i < size(); i++) {
        this->data[i] -= rhs.data[i];
    }

    return *this;
}

#endif
