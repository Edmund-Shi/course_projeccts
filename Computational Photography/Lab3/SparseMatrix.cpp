//
// Created by 36202 on 29/03/2017.
//
#include "SparseMatrix.h"
#include <algorithm>

double SparseMatrix::at(int row, int col)
{
    if (row>_row || col >_col || row <0||col <0){
        // ERROR
        return 0;
    }
    int trow,tcol;
    int index=-1; // 当前元素在数组中的位置
    vector<int>::iterator tmp;
    for (int i = 0; i < _numOfMembers; ++i) {
        if(row == row_ind[i]){
            index = i;
            break;
        }
    }
    if ( -1 == index){
        // Element not found.
        return 0;
    }
    while(row_ind[index] == row){
        if (col_ind[index] == col){
            return value[index];
        }
        index++;
    }
    // element not found.
    return 0;
}

void SparseMatrix::initializeFromVector(int row, int col, double* vals)
{
    // 初始化成员变量
    _row = row;
    _col = col;
    _numOfMembers = 0;
    value.clear();
    col_ind.clear();
    row_ind.clear();

    for (int i = 0; i < row;i++) {
        for (int j = 0; j < col;j++) {
            if (vals[i*row+j]!=0){
                value.push_back(vals[i*row + j]);
                _numOfMembers++;
                col_ind.push_back(j);
                row_ind.push_back(i);
            }
        }
    }
}

int SparseMatrix::insert(double val, int row, int col)
{
    if (row > _row || col > _col || row <0 || col < 0) {
        // ERROR
        return INDEX_OUT_OF_RANGE;
    }
    if(at(row,col) != 0){
        // already have an element
        return ELEMENT_CONFLICT;
    }
    // insert a new element
    return OP_SUCCESS;
}


