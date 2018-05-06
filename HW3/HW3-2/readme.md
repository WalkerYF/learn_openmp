# 第二题

代码及数据文件相关说明

## 环境

在ubuntu下测试。
CPU为i3-3110M

## 代码

run_all.sh 多次传入不同的参数调用run.sh，用于在服务器上自动地跑完多种情况的程序，不用每次都要手动改代码，这样子只需要运行一次run.sh就可以跑完所有情况的程序并记录时间
run.sh 使用参数，编译出所需要的可执行程序，并将运行时间结果写入到文件中。
matrix_product.cpp 矩阵乘法的实现，注意使用了很多宏变量来帮助编译生成多种可执行文件
read_data.py 用于读取all_time.csv 并且作图

## 数据

all_time.csv
数据分为5列，分别为
num_thread,collaspe,size,cputime,walltime,cache_opt


