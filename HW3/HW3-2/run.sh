#!/bin/bash
# 参数说明
# 1. cpp文件名
# 2. 嵌套层数
# 3. 矩阵大小
# 4. 是否优化（OPT,NOT_OPT) 
# 5. 保存数据文件名
# 6. 最大线程数量 
# EXE=.exe  用于在wsl下运行window程序，在linux下请注释这条
MAX_NUM_THREADS=$6
g++$EXE $1 -o a.exe -fopenmp -std=c++11 -D SINGLE -D COLLAPSE_NUM=$2 -D MATRIX_SIZE=$3 -D $4
g++$EXE $1 -o b.exe -fopenmp -std=c++11 -D PARALLEL -D COLLAPSE_NUM=$2 -D MATRIX_SIZE=$3 -D $4
SAVE_DATA_FILE=$5

# 串行时间的计算
time=`./a.exe 10`
echo 1,$time >> $SAVE_DATA_FILE

# 并行时间的计算
for ((varible=2;varible<=$MAX_NUM_THREADS;varible = varible+1));do
    echo "OMP_NUM_THREADS: $varible | COLLAPSE:$2 | MATRIX_SIZE:$3 | OPT:$4 |"
    time=`./b.exe $varible`
    echo $varible,$time >> $SAVE_DATA_FILE
done
# for ((varible=30;varible<=850;varible = varible+10));do
#    echo "OMP_NUM_THREADS: $varible | COLLAPSE:$2 | MATRIX_SIZE:$3 | OPT:$4 |"
#    time=`./b.exe $varible`
#    echo $varible,$time >> $SAVE_DATA_FILE
# done
