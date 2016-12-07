//Angelo Zamudio CS381 Summer 16'
//
#include <iostream>
#include "VNT.h"

using namespace std;

template<class T>
VNT<T>::VNT(){};

template<class T>
VNT<T>::VNT(int x, int y){
    rows = x;
    columns = y;
    cand_row = 0;
    cand_col= 0;
    vnt_matrix= SA<SA<T>>(rows);
    for (int k = 0; k < rows ; ++k) {
        vnt_matrix[k]= SA<T>(columns);
    }//for k
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            vnt_matrix[i][j]=INT_MAX;
        }//for i
    }//for i
};

template<class T>
VNT<T>::~VNT(){};

template<class T>
void VNT<T>::printMatrix(){
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if(vnt_matrix[i][j]==INT_MAX){
                cout<<" #"<<" ";
            }else{
                cout<<vnt_matrix[i][j]<<" ";
            }//else
        }//for j
        cout<<"\n";
    }//for i
    cout<<"\n";
}//printMatrix

template<class T>
bool VNT<T>::isEmpty(){
    return cand_row == 0 && cand_col == 0;
}

template<class T>
bool VNT<T>::isFull(){
    return cand_row==rows || cand_col==columns;
}

template<class T>
void VNT<T>::updateCandidate(int current_row, int current_column) {
    if (cand_col + 1 == columns) {
        cand_col = 0;
        cand_row = cand_row + 1;
    } else {
        cand_col = cand_col + 1;
    }
    return;
}//updateCandidate

template<class T>
void VNT<T>::resetCandidate(){
    if (cand_row >= rows) {
        cand_row = rows - 1;
        cand_col = columns - 1;
    } else if (cand_col - 1 < 0) {
        cand_row -= 1;
        cand_col = columns - 1;
    } else {
        cand_col -= 1;
    }
    return;
}

template<class T>
void VNT<T>::add(int x) {
    if(isFull()){//cand_row==rows || cand_col==columns){
        cout<<"VNT is FULL...";
        return;
    }
    int temp = 0;
    int curr_row = cand_row;
    int curr_col = cand_col;
    vnt_matrix[curr_row][curr_col] = x;
    int *current = &vnt_matrix[curr_row][curr_col];
    int *top, *left;

    while(curr_col >= 1 && curr_row >= 1) {
        top = &vnt_matrix[curr_row - 1][curr_col];
        left = &vnt_matrix[curr_row][curr_col - 1];
        if (*top > *current && *top > *left) {
            std::swap(*top, *current);
            curr_row = curr_row - 1;
            current = top;
        } else if (*left > *current && *left > *top) {
            std::swap(*left, *current);
            curr_col = curr_col - 1;
            current = left;
        } else if (*top < *current && *left == INT_MAX) {
            std::swap(*left, *current);
            curr_col = curr_col - 1;
            current = left;
        } else {
            break;
        }
    }//while

    if(curr_row >= 0){
        while(curr_row >= 1){
            top = &vnt_matrix[curr_row - 1][curr_col];
            if(*top > x) {
                swap(*top,*current);
                curr_row -= 1;
                current = top;
            }else{
                break;
            }//else
        }//while
    }//if curr_row

    if(curr_col > 0){
        while (curr_col >= 1) {
            left = &vnt_matrix[curr_row][curr_col - 1];
            if (*left > *current || *left == INT_MAX) {
                swap(*left, *current);
                curr_col -= 1;
                current = left;
            } else {
                break;
            }//else
        }//while
    }//if curr_col
    updateCandidate(curr_row,curr_col);
    return;
};

template<class T>
T VNT<T>::getMin() {
    if (isEmpty()) {
        cout << "VNT is Empty there is no min...";
        return 0;
    }
    resetCandidate();
    int min = vnt_matrix[0][0];
    vnt_matrix[0][0] = INT_MAX;
    swap(vnt_matrix[0][0], vnt_matrix[cand_row][cand_col]);
    int curr_row = 0;
    int curr_col = 0;
    int *current = &vnt_matrix[curr_row][curr_col];
    int *right, *bottom;

    while (curr_col <= columns - 2 && curr_row <= rows - 2) {
        right = &vnt_matrix[curr_row][curr_col + 1];
        bottom = &vnt_matrix[curr_row + 1][curr_col];

        if (*right < *current && *right < *bottom) {
            std::swap(*right, *current);
            current = right;
            curr_col += 1;
        } else if (*bottom < *current && *bottom < *right) {
            std::swap(*bottom, *current);
            current = bottom;
            curr_row += 1;
        } else {
            break;
        }
    }
    if (curr_col < columns - 1) {
        while (curr_col < columns - 2) {
            right = &vnt_matrix[curr_row][curr_col + 1];
            if (*right < *current) {
                swap(*right, *current);
                current = right;
                curr_col += 1;
            } else {
                break;
            }
        }
    }
    return min;
};

template<class T>
void VNT<T>::sort(int q[], int size){
    for (int i = 0; i < size; ++i) {
        this->add(q[i]);
    }
    return;
};

template<class T>
bool VNT<T>::find(int x) {
    bool found = false;
    if (isEmpty()) {
        cout<<"VNT is empty x not found...\n";
        return found;
    }//if

    int curr_row = 0, curr_col = columns - 1;
    int *current = &vnt_matrix[curr_row][curr_col];
    int *left, *bottom;
    while (curr_row < rows - 1 && curr_col > 0) {
        left = &vnt_matrix[curr_row][curr_col - 1];
        bottom = &vnt_matrix[curr_row + 1][curr_col];
        if (*current == x) {
            found = true;
            cout << x <<" found at: (" << curr_row << "," << curr_col << ")\n";
            return found;
        }else if (x > *current) {
            curr_row += 1;
            current = bottom;

        } else if (x < *current) {
            curr_col -= 1;
            current = left;
        }
    }//while
    while (curr_col > 0) {
        left = &vnt_matrix[curr_row][curr_col - 1];
        if (x < *current) {
            current = left;
            curr_col -= 1;
        } else if (x == *current) {
            found = true;
            cout << x <<" found at: (" << curr_row << "," << curr_col << ")\n";
            return found;
        }
    }//while
    while (curr_row < rows - 1) {
        bottom = &vnt_matrix[curr_row + 1][curr_col];
        if (x > *current) {
            current = bottom;
            curr_row += 1;
        } else if (x == *current) {
            found = true;
            cout <<x <<" found at: (" << curr_row << "," << curr_col << ")\n";
            return found;
        }//else if
    }//while
    if (*current == x) {
        found = true;
        cout << x <<" found is at: (" << curr_row << "," << curr_col << ")\n";
        return found;
    }//if
    if (!found) {
        cout <<x <<" is not in the matrix...\n";
    }//if
    return found;
};

template<class T>
SA<T>& VNT<T>::operator[](int i) {
    if(i < rows || i < columns){
        return vnt_matrix[i];
    }else{
        cout<<"Index "<< i << " out of bounds";
        exit(1);
    }
};



