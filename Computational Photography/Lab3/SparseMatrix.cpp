//
// Created by 36202 on 29/03/2017.
//
#include "SparseMatrix.h"
#include "Utility.h"
#include <algorithm>
const double SparseMatrix::MINDOUBLE = 0.00001;

double& SparseMatrix::at(int row, int col)
{
    zerocheck();
    double zero = 0;
    if (row>_row || col >_col || row <0||col <0){
        // ERROR
        return zero;
    }
    int index=-1; // 当前元素在数组中的位置
    vector<int>::iterator tmp;
    for (int i = 0; i < value.size(); ++i) {
        if(row == row_ind[i]){
            index = i;
            break;
        }
    }
    if ( -1 != index){
        while(row_ind[index] == row){
            if (col_ind[index] == col){
                return value[index];
            }
            index++;
        }
    }
    index = insert(0,row,col);
    return value[index];

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

// return value:
// Error: error number
// Successful: the index of new element
int SparseMatrix::insert(double val, int row, int col)
{
    zerocheck();
    if (row > _row || col > _col || row <0 || col < 0) {
        // ERROR
        return INDEX_OUT_OF_RANGE;
    }
    // no checks for exist element
//    if(at(row,col) != 0){
//        // already have an element
//        return ELEMENT_CONFLICT;
//    }
    // insert a new element
    vector<int>::iterator rowit,colit;
    vector<double>::iterator valit;

    rowit = row_ind.begin();
    colit= col_ind.begin();
    valit = value.begin();

    int i;
    for (i = 0; i < _numOfMembers; ++i) {
        if (row_ind[i] == row || row_ind[i]>row){
            break;
        }
        rowit++;colit++;valit++;
    }
    if ( i == _numOfMembers){
        row_ind.push_back(row);
        col_ind.push_back(col);
        value.push_back(val);
    }else {
        row_ind.insert(rowit,row);
        col_ind.insert(colit,col);
        value.insert(valit,val);
    }
    _numOfMembers++;
    return i;
}

void SparseMatrix::zerocheck() {
    vector<int>::iterator rowit,colit;
    vector<double>::iterator valit;

    rowit = row_ind.begin();
    colit = col_ind.begin();
    valit = value.begin();

    for (int i = 0; i < _numOfMembers; ++i) {
        if(abs(0 - *valit) < MINDOUBLE){
            value.erase(valit);
            row_ind.erase(rowit);
            col_ind.erase(colit);
            _numOfMembers--;
        }else{
            valit++;
            rowit++;
            colit++;
        }

    }
}

double * SparseMatrix::Gauss_Seidel(double *array, int len) {
    if (len != _row || _row != _col){
        return  NULL;
    }
    Utility utility;
    double *res = new double[len];
    double *last = new double[len]; // 用于存储上一次的计算结果
    utility.ArrayCopy(res,array,len);
    utility.ArrayCopy(last,res,len);
    while (1){
        // repeat until last == res
        for(int i = 0;i<len;i++){
            double row_sum_before = 0,row_sum_after = 0;
            for (int j = 0; j < i; ++j) {
                row_sum_before += at(i,j)*res[j];
            }
            for (int k = i+1; k < len; ++k) {
                row_sum_after+=at(i,k)*last[k];
            }
            res[i] = (1/at(i,i))*(array[i] - row_sum_before - row_sum_after);
        }
        if (utility.ArrayCmp(res,last,len) == 0){
            break;
        }else {
            utility.ArrayCopy(last,res,len);
        }
    }
    delete[] last;
    return res;
}


