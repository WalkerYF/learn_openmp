import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

file_name = 'all_time.csv'
fd = pd.read_csv(file_name,header=0)


# 提取一列, 索引为delay_times, 内容为对应的walltime
# 提取一列, 索引为delay_times, 内容为对应的walltime,及加速比
# 参数提供各种flag过滤
def get_column(num_thread, schedule_flag, chunk_num):
    if (num_thread == 1):
        temp = fd[fd.num_thread == 1]
    else:
        temp = fd[(fd.num_thread == num_thread) & (fd.schedule == schedule_flag) & (fd.chunk_num == chunk_num) & (fd.cache_flag == 0)]
    temp2 = temp.set_index(['delay_times'])
    temp3 = temp2.loc[~temp2.index.duplicated(keep='first')]
    return temp3.loc[:,['walltime']].sort_index()


# 提取另一列，索引为chunk_num, 内容为对应的walltime


print(get_column(4, 1, 0))
# static调度
get_column(4, 1,0)
# 没有使用多线程
get_column(1, 0, 0).plot()
plt.show()