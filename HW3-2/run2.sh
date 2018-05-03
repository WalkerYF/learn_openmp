#!/bin/bash
# cpp 文件名，嵌套层数，矩阵大小，是否优化（OPT,NOT_OPT)
#输入输入
g++.exe $1 -o a.exe -fopenmp -std=c++11 -D SINGLE -D COLLAPSE_NUM=$2 -D MATRIX_SIZE=$3 -D $4
g++.exe $1 -o b.exe -fopenmp -std=c++11 -D PARALLEL -D COLLAPSE_NUM=$2 -D MATRIX_SIZE=$3 -D $4
SAVE_DATA_FILE=$5

# 串行时间的计算
time=`./a.exe 10`
echo 1,$time >> $SAVE_DATA_FILE

# 并行时间的计算
for ((varible=2;varible<=30;varible = varible+2));do
    echo "OMP_NUM_THREADS: $varible | COLLAPSE:$2 | MATRIX_SIZE:$3 | OPT:$4 |"
    time=`./b.exe $varible`
    echo $varible,$time >> $SAVE_DATA_FILE
done
for ((varible=30;varible<=850;varible = varible+10));do
    echo "OMP_NUM_THREADS: $varible | COLLAPSE:$2 | MATRIX_SIZE:$3 | OPT:$4 |"
    time=`./b.exe $varible`
    echo $varible,$time >> $SAVE_DATA_FILE
done
