import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

file_name = 'all_time.csv'
fd = pd.read_csv(file_name,header=0)


# 提取一列, 索引为delay_times, 内容为对应的walltime
# 参数提供各种flag过滤
def get_column(num_thread, schedule_flag, chunk_num):
    if (num_thread == 1):
        temp = fd[fd.num_thread == 1]
    else:
        temp = fd[(fd.num_thread == num_thread) & (fd.schedule == schedule_flag) & (fd.chunk_num == chunk_num) & (fd.cache_flag == 0)]
    temp2 = temp.set_index(['delay_times'])
    temp3 = temp2.loc[~temp2.index.duplicated(keep='first')]
    return temp3.loc[:,['walltime']].sort_index()

# 提取一列，索引为chunk_num, 内容为对应的walltime
# 改进：得到加速比
def get_column_chunk_num(num_thread, cache_flag, schedule_flag, delay_times):
    series_time = fd[(fd.num_thread == 1) & (fd.delay_times == delay_times)]['walltime'] 
    temp = fd[
        (fd.num_thread == 4) &
        (fd.cache_flag == 0) &
        (fd.schedule == schedule_flag) &
        (fd.delay_times == delay_times)
    ]
    temp2 = temp.set_index(['chunk_num'])
    temp3 = temp2.loc[~temp2.index.duplicated(keep='first')].loc[:,['walltime']]
    print(temp3)
    temp3['speedup'] = temp3.apply(lambda row: series_time / row['walltime'], axis=1)
    return temp3.loc[:,['speedup']].sort_index()

# 提取另一列，索引为chunk_num, 内容为对应的walltime

# 画出串行，static，dynamic，guided的对比图
def draw_image_from_columns(dynamic_chunk_num, guided_chunk_num):
    all_column = pd.concat(
        [
            # 串行执行
            get_column(1,0,0),
            # static 默认参数
            get_column(4,1,0),
            # dynamic 调度
            get_column(4,2,dynamic_chunk_num),
            # guided 调度
            get_column(4,3,guided_chunk_num)
        ],
        axis=1,
        keys=[
            'serial execution',
            'default static schedule',
            'dynamic schedule',
            'guided schedule'
        ]
    )
    all_column.plot()
    plt.show()

# 画出dynamic与chunk_num之间的关系，参数为delay_times
def draw_dynamic_walltime_and_chunk_num(all_delay_times):
    all_column = pd.concat(
        [
            # delay_times == 1000
            get_column_chunk_num(4,0,2,delay_times) for delay_times in all_delay_times
        ],
        axis=1,
        keys=[
            'delay_times == '+str(delay_times) for delay_times in all_delay_times
        ]
    )
    all_column.plot()
    plt.show()


# draw_image_from_columns(1000,401)
draw_dynamic_walltime_and_chunk_num([100 + i*1000 for i in range(0, 10)])