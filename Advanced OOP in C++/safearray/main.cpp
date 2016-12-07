//
// Created by Angelo Zamudio
//
#include <iostream>
#include "SafeMatrix.cpp"
using namespace std;

int main(int argc, char * argv[]) {

    int rows_a;
    int cols_a;
    int rows_b;
    int cols_b;
    cout<<"Enter # of rows and columns for matrix A and B...\n";
    cout<<"\nEnter Matrix A row #: ";
    cin>>rows_a;
    cout<<"Enter Matrix A column #: ";
    cin>>cols_a;
    cout<<"Enter Matrix B row #: ";
    cin>> rows_b;
    cout<<"Enter Matrix B column #: ";
    cin>>cols_b;
    cout<<"\n";
    SafeMatrix<int> a(rows_a,cols_a);
    a.populateMatrix();
    cout<<"Matrix A ("<<rows_a<<" x "<<cols_a<<"): \n";
    a.printMatrix();
    cout<<"\n";
    SafeMatrix<int> b(rows_b,cols_b);
    b.populateMatrix();
    cout<<"Matrix B ("<<rows_b<<" x "<<cols_b<<"): \n";
    b.printMatrix();
    cout<<"\n";

    SafeMatrix<int>prod;
    prod=a*b;
    cout<<"Product Matrix ("<<rows_a<<" x "<<cols_b<<"):\n";
    prod.printMatrix();
    return 0;
}