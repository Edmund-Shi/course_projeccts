#include <iostream>
#include <fstream>
#include "SparseMatrix.h"
using namespace std;
int main() {
    ifstream in("input.txt");
    cin.rdbuf(in.rdbuf());
    int row = 4,col = 4;
    double *data = new double[row*col];

    for (int i = 0; i < row*col; ++i) {
        cin >> data[i];
    }
    SparseMatrix matrix;
    matrix.initializeFromVector(row,col,data);
    double arrayb[]={6,25,-11,15};
    double *res;
    res = matrix.Gauss_Seidel(arrayb,4);
    for (int j = 0; j < row; ++j) {
        cout << res[j]<<endl;
    }
    delete[] data;
    return 0;
}