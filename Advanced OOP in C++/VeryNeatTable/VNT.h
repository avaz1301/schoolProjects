//Angelo Zamudio CS381 Summer 16'

//
#include<iostream>
#include <climits>
#include "SafeArray.cpp"

#ifndef VERYNEATTABLE_VNT_H
#define VERYNEATTABLE_VNT_H



template<class T>
class VNT{
private:
    int rows, columns, cand_row, cand_col;
    SA<SA<T>> vnt_matrix;
public:
    VNT();

    VNT(int, int);

    ~VNT();

    void updateCandidate(int, int);

    void resetCandidate();

    bool isEmpty();

    bool isFull();

    void printMatrix();

    void add(int);

    T getMin();

    void sort(int [] ,int);

    bool find(int);

    SA<T>& operator[](int);
};



#endif //VERYNEATTABLE_VNT_H
