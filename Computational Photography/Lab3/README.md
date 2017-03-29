# Lab 3 - 实现稀疏矩阵以及高斯赛达尔迭代法

本实验要求自行实现一种稀疏矩阵。推荐的稀疏矩阵存储方式包括：

1. Compressed Row Storage
2. Compressed Sparse Column
3. 其他形式的稀疏矩阵存储方式


该实验实现的方式是COO的方法。

稀疏矩阵必须起码具备以下的几种最基本的功能：

1. at(row, col): 根据row和column的系数来查询矩阵里面的元素的数值
2. insert(val, row, col)： 将val替换/插入到（row, col）这个位置去
3. initializeFromVector(rows, cols, vals): 根据向量来初始化一个稀疏矩阵。其中rows, cols, vals皆为等长度的向量。rows里面存的是行系数，cols里面存的是列系数，vals里面存的是数值。