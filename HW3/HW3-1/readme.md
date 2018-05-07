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
