
# Lab 5 - 非线性最小二乘

本次实验我们实现 Gauss Newton 法求解简单的非线性最小二乘问题。实现的方式主要是通过实现老师给出的接口。

## 接口要求

你需要实现名为 `Solver####` 的类，其中 `####` 代表你学号的后四位。 
这个类需要继承自接口类 `GaussNewtonSolver` ，我们提供了头文件，请下载 hw3_gn.h 并包含在你的优化器类中。 
你需要严格按照接口要求实现，否则会扣分。

`GaussNewtonSolver` 的定义如下：
```cpp
class GaussNewtonSolver {
public:
    virtual double solve(
               ResidualFunction *f, // 目标函数
               double *X,           // 输入作为初值，输出作为结果
               GaussNewtonParams param = GaussNewtonParams(), // 优化参数
               GaussNewtonReport *report = nullptr // 优化结果报告
               ) = 0;
};
```
* 当你的类的 `solve` 函数被调用时，它将采用 Gauss Newton 法最小化函数 `f` 。
* 输入时数组 `X` 内包含初始点，并且在优化后将被修改为最优点，维度需要与目标函数定义的维度一致。
* `param` 是 GN 算法运行的各种相关参数。
* 如果 `report` 不是空指针，优化完成后应当把相关的报告记录到 `report` 。
* 函数返回值是优化得到的目标函数的最优值。

目标函数通过继承接口类 `ResidualFunction` 进行定义：
```cpp
class ResidualFunction {
public:
    virtual int nR() const = 0;
    virtual int nX() const = 0;
    virtual void eval(double *R, double *J, double *X) = 0;
};
```
`nR` 函数需要返回余项向量的维度。类似的，`nX` 函数需要返回变量 `X` 的维度。 
`eval` 运行时读入 `X` 将计算得到的余项和Jacobian写入 `R` 和 `J` 。 
* 计算得到的余项向量需要写入到 `R` ，`R`需要预先分配好，长度为 `nR`。 
* 计算得到的 Jacobian 需要写入到 `J` ，`J` 需要预先分配好，大小为 `nR*nX`。 
* 输入的 `X` 是一个长度为 `nX` 的数组，包含所有的变量。

**注意：你的优化器需要负责在优化开始前分配好 R 和 J 需要的空间，在结束后销毁。X 作为输入，由用户（调用 solve 的程序）分配并填充好初始值**

## 测试文件
作为测试，我们求解从三维点云拟合椭球的问题，测试文件为 ellipse753.txt 

## 说明
* 该实验用到的矩阵乘法由OpenCV提供
* 文件编码：UTF-8
