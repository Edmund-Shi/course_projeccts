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
    // cout << matrix.at(1,1)<<endl;
    cout << matrix.at(0,3)<<endl;
    matrix.insert(2.3,0,3);
    cout<<matrix.at(0,3)<<endl;
    //matrix.insert(9,3,3);

    cout << matrix.at(3,3)<<endl;
    delete[] data;
    return 0;
}