#!/bin/bash
# EXE=.exe  用于在wsl下运行window程序，在linux下请注释这条
FILE_NAME=loop-parallel-schedule.cpp
SAVE_DATA_FILE=all_time.csv
DELAY_MIN_TIMES=100
DELAY_MAX_TIMES=10001
# 设置程序对CACHE的使用，有NO_CACHE和USE_CACHE两种
CACHE_FLAG=NO_CACHE
g++$EXE $FILE_NAME -o a.exe -fopenmp -std=c++11 -D SINGLE -D DELAY_MIN_TIMES=$DELAY_MIN_TIMES -D DELAY_MAX_TIMES=$DELAY_MAX_TIMES -D $CACHE_FLAG
g++$EXE $FILE_NAME -o b.exe -fopenmp -std=c++11 -D PARALLEL -D DELAY_MIN_TIMES=$DELAY_MIN_TIMES -D DELAY_MAX_TIMES=$DELAY_MAX_TIMES -D $CACHE_FLAG
echo "complie completed!"

# echo "num_thread,cache_flag,schedule,chunk_num,delay_times,cputime,walltime" >> $SAVE_DATA_FILE

# 计算串行时间
# ./a.exe >> $SAVE_DATA_FILE

# # 设置参数变化情况
# MIN_TRUNK=2500
# MAX_TRUNK=1
# # 先进行一次不使用参数的
# export OMP_SCHEDULE="static"
# echo "|OMP_SCHEDULE:$OMP_SCHEDULE|"
# ./b.exe >> $SAVE_DATA_FILE
# # 参数意义：分配给每个线程 size次连续的迭代计算
# for ((variable=$MIN_TRUNK;variable<=$MAX_TRUNK;variable = variable+1));do
#     export OMP_SCHEDULE="static, $variable"
#     echo "|OMP_SCHEDULE:$OMP_SCHEDULE|"
#     ./b.exe >> $SAVE_DATA_FILE
# done


# # 设置参数变化情况
# MIN_TRUNK=50
# MAX_TRUNK=4500
# # 先进行一次不使用参数的
# export OMP_SCHEDULE="dynamic"
# # echo "|OMP_SCHEDULE:$OMP_SCHEDULE|"
# #./b.exe >> $SAVE_DATA_FILE
# # 参数意义：每次分配的迭代次数
# for ((variable=$MIN_TRUNK;variable<=$MAX_TRUNK;variable = variable+50));do
#     export OMP_SCHEDULE="dynamic, $variable"
#     echo "|OMP_SCHEDULE:$OMP_SCHEDULE|"
#     ./b.exe >> $SAVE_DATA_FILE
# done


# 设置参数变化情况
MIN_TRUNK=510
MAX_TRUNK=2000
# 先进行一次不使用参数的
export OMP_SCHEDULE="guided"
echo "|OMP_SCHEDULE:$OMP_SCHEDULE|"
./b.exe >> $SAVE_DATA_FILE
# 参数意义：迭代块的大小会按指数级下降到指定的size大小
for ((variable=$MIN_TRUNK;variable<=$MAX_TRUNK;variable = variable+100));do
    export OMP_SCHEDULE="guided, $variable"
    echo "|OMP_SCHEDULE:$OMP_SCHEDULE|"
    ./b.exe >> $SAVE_DATA_FILE
done

rm *.exe
