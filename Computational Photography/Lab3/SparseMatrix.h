//
// Created by 36202 on 29/03/2017.
//

#ifndef LAB3_SPARSEMATRIX_H
#define LAB3_SPARSEMATRIX_H
#define INDEX_OUT_OF_RANGE -2
#define OP_SUCCESS         0
#define ELEMENT_CONFLICT   -3
// 使用 COO的存储方式
#include<vector>
using namespace std;
class SparseMatrix {
private:
    int _row;
    int _col;
    int _numOfMembers;      // 非零元素的个数

    vector<double> value;
    vector<int> col_ind;    // 存储该元素是在第几列
    vector<int> row_ind;    // 存储每一行的开始位置
    void zerocheck();       // 删除矩阵中的0元素
public:
    const static double MINDOUBLE ;
    SparseMatrix(){
        _row = _col = _numOfMembers = 0;
        value.clear(); col_ind.clear(); row_ind.clear();
    }
    double & at(int row, int col);

    int insert(double val, int row, int col);
    void initializeFromVector(int row, int col, double* vals);

    //传入的参数表示的是向量b的内容以及向量b的长度
    double * Gauss_Seidel(double *array, int len) ;
};


#endif //LAB3_SPARSEMATRIX_H
