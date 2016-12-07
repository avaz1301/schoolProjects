//
// Created by Angelo Zamudio
//
#include<iostream>
#include "SafeArray.h"

 // forward declaration
template<class T>
class SafeMatrix;

#ifndef SAFEMATRIX_H
#define SAFEMATRIX_H



template<class T>
class SafeMatrix {
private:
    int rows, cols;
    SA<T>** matrix_ptr;
public:
    SafeMatrix();

    SafeMatrix(int r, int c);

    void populateMatrix();

    void printMatrix();

    SafeMatrix operator*(const SafeMatrix &b);

    SafeMatrix& operator=(const SafeMatrix s);

    ~SafeMatrix();
};


#endif //SAFEARRAY_SAFEMATRIX_H
