# 第一题

固定在四个线程中跑出来的。

## 数据说明

all_time.csv

|第一列|二|三|四|五|六|七|
|-|-|-|-|-|-|-|
|线程数|是否用cache|调度类型|chunk大小|延时大小|CPU时间|wall time|
|num_thread|cache_flag|schedule| chunk_num| delay_times| cputime| walltime|

其中调度类型中
1：static
2：dynamic
3：guided

## 代码说明

1. "./loop-parallel-schedule.cpp"用来测试调度算法的代码
1. "save.cpp"。没啥， 就是想存点东西
1. run.sh：自动化测试脚本


## 数据处理

1. 人为选择一个比较合适的参数，然后跑出对应的运行时间。
    1. 对不同的延迟，适当选择不同的参数。
    1. 延迟渐渐增大，
1. 画一个图
    1. 串行
    1. static
    1. dynamic
    1. guided
1. 对dynamic调度，我想找到最优的chunk_num。
    1. 对同一个延时，找到使walltime最小的chunk_num
        1. 取得延时列表，对每一个延时，取得对应的walltime列表，然后去最小walltime对应的索引，并将这个chunk_num与对应的延时放到新列表中。
1. 对guided调度，我同样想找到最优的chunk_num