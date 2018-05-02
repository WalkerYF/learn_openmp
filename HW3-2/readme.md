# 作业三

## 第一题

### 题目

Consider a simple loop that calls a function dummy containing a programmable delay.All invocations of the function are independent of the others. Partition this loop across four threads using static, dynamic, and guided scheduling. Document the result of this experiment as the delay within the dummy function becomes large.


## 第二题

### 题目

Implement and test the OpenMP program for computing a matrix-matrix (50 * 50) product. Use the OMP_NUM_THREADS environment veriable to control the number of threads and plot the performance with varying numbers of threads. Consider three cases in which 
(i)only the outermost loop is parallelized.
(ii)the outer two loops are parallelized. 
and (iii) all three loops are parallelized. 
What is the observed result from these three cases?

#### 做一个与运行线程数


#### i

在只有一层循环并行化的情况下，设置环境变量`OMP_NUM_THREADS`为20，计算700阶的矩阵乘法，得到下面的结果。

![](figure/2018-05-02-13-46-53.png)

|测试类型|运行时间|
|-|-|
|具有多线程优化 | 0.948s|
|没有多线程优化 | 2.349s|

很明显，在具有多线程优化的情况下，该矩阵乘法运行得更快。

#### 两层循环并行化

慢了

#### 三层循环并行化

更慢
