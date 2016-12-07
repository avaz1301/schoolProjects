//
// Created by Angelo Zamudio
#include<iostream>
#include "SafeArray.cpp"
#include "SafeMatrix.h"

using namespace std;

template<class T>
SafeMatrix<T>::SafeMatrix() {
    rows=0;
    cols=0;
    matrix_ptr=NULL;
}

template<class T>
SafeMatrix<T>::SafeMatrix(int r, int c) {
    rows = r;
    cols = c;
    matrix_ptr=new SA<T>*[rows];
    for (int i = 0; i < rows; ++i) {
        matrix_ptr[i]= new SA<T>(cols);
    }//for i

}

template <class T>
void SafeMatrix<T>::populateMatrix(){
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            (*matrix_ptr[i])[j] = rand() & 30;
        }//for j
    }//for i
}//populate matrix

template<class T>
void SafeMatrix<T>::printMatrix() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout<<(*matrix_ptr[i])[j]<<" ";
        }//for j
        cout<<"\n";
    }//for i
}//print matrix

template<class T>
SafeMatrix<T>::~SafeMatrix() {
    for (int i = 0; i < rows ; ++i) {
        delete matrix_ptr[i];
    }//for i
}//destructor

template<class T>
SafeMatrix<T>& SafeMatrix<T>::operator=(const SafeMatrix<T> s){
    if (this == &s)return *this;
    delete matrix_ptr;
    rows=s.rows;
    cols=s.cols;
    matrix_ptr=new SA<T>*[s.rows];
    for (int i = 0; i < s.rows; ++i) {
        matrix_ptr[i] = new SA<T>(s.cols);
        for (int j = 0; j < s.cols; ++j) {
            (*matrix_ptr[i])[j] = (*s.matrix_ptr[i])[j];
        }//for j
    }
    return *this;
}

template<class T>
SafeMatrix<T> SafeMatrix<T>::operator*(const SafeMatrix<T> &b){
    SafeMatrix<int> temp = SafeMatrix<int>(this->rows,b.cols);
    if(this->cols != b.rows){
        cout<<"Matrix A and B are not multiplication compatible.\n";
        cout<<"# of Columns in Matrix A not equal # of Rows in Matrix B.\n";
        cout<<"Returning empty matrix...\n";
        return temp;
    }else{
        SafeMatrix<int> temp = SafeMatrix<int>(this->rows,b.cols);
        int new_sum=0;
        for (int i = 0; i < this->rows ; i++) {
            for (int j = 0; j < b.cols; j++) {
                for(int m=0; m < this->cols; m++){
                    new_sum+=(*this->matrix_ptr[i])[m] * (*b.matrix_ptr[m])[j];
                }//for m
                (*temp.matrix_ptr[i])[j]=new_sum;
                new_sum=0;
            }//for j
        }//for i
        return temp;
    }

};








