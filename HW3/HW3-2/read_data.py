import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# 得到具有特定性质的一列walltime
def get_column(fd, collaspe, opt, max_num_thread=1000, size=1200):
    temp = fd[(fd.collaspe == collaspe) & (fd.cache_opt == opt) & (fd.num_thread < max_num_thread) & (fd['size'] == size)]
    temp2 = temp.set_index(['num_thread'])
    temp3 = temp2.loc[~temp2.index.duplicated(keep='first')]
    return temp3.loc[:,['walltime']].sort_index()

# 画图 cache优化后的
def draw_image_collaspe_opt(max_num_thread, size):
    all_collaspe = pd.concat([
            get_column(fd,1,1,max_num_thread, size),
            get_column(fd,2,1,max_num_thread, size),
            get_column(fd,3,1,max_num_thread, size)
        ],
        axis=1,
        keys=['collaspe_1','collaspe_2','collaspe_3']
    )
    print(all_collaspe.info())
    all_collaspe.plot()
    plt.ylabel('wall time/s')
    plt.show()

# 画图 没有对cache进行优化
def draw_image_collaspe_no_opt(max_num_thread, size):
    all_collaspe = pd.concat([
            get_column(fd,1,0,max_num_thread, size),
            get_column(fd,2,0,max_num_thread, size),
            get_column(fd,3,0,max_num_thread, size)
        ],
        axis=1,
        keys=['collaspe_1_no_opt','collaspe_2_no_opt','collaspe_3_no_opt']
    )
    print(all_collaspe.info())
    all_collaspe.plot()
    plt.ylabel('wall time/s')
    plt.show()

# 画图 画在一起
def draw_image_collaspe_all(max_num_thread, size):
    all_collaspe = pd.concat([
            get_column(fd,1,1,max_num_thread, size),
            get_column(fd,2,1,max_num_thread, size),
            get_column(fd,3,1,max_num_thread, size),
            get_column(fd,1,0,max_num_thread, size),
            get_column(fd,2,0,max_num_thread, size),
            get_column(fd,3,0,max_num_thread, size)
        ],
        axis=1,
        keys=[
            'collaspe_1',
            'collaspe_2',
            'collaspe_3',
            'collaspe_1_no_opt',
            'collaspe_2_no_opt',
            'collaspe_3_no_opt'
        ]
    )
    print(all_collaspe.info())
    all_collaspe.plot()
    plt.ylabel('wall time/s')
    plt.show()

# 含有矩阵维度为500,700 的数据
# file_name = 'all_time_win.csv'
# 含有矩阵维度为1200的数据
file_name = 'all_time.csv'
fd = pd.read_csv(file_name, header=0)
matrix_size = 1200
# draw_image_collaspe_opt(1000, matrix_size)
# draw_image_collaspe_no_opt(1000, matrix_size)
draw_image_collaspe_all(1000, matrix_size)
