import sys
import matplotlib.pyplot as plt

# 从命令行参数中获取数据来源以及保存的图片文件名
data_file_name = sys.argv[1]
# save_image_name = sya.argv[2]
num_threads = []
num_collapse = []
matrix_size = []
cpu_times = []
wall_times = []
with open(data_file_name, 'r') as f:
    for line in f.readlines():
        num_str_list = line.split(',')
        if len(num_str_list) != 5:
            break
        num_threads.append(int(num_str_list[0]))
        cpu_times.append(float(num_str_list[3]))
        wall_times.append(float(num_str_list[4]))

plt.plot(num_threads[1:], wall_times[1:])
plt.xlabel('the number of threads')
plt.ylabel('average running time/second')
plt.title('the relation between the number of threads and thr running time of matrix\'s product')
# plt.text(60, .025, r'$\mu=100,\ \sigma=15$')
# plt.axis([40, 160, 0, 0.03])
plt.grid(True)

# 记录单线程的时间，之后会经常用
single_time = cpu_times[0]

# 对于多线程的程序而言，研究加速比
speedups = [single_time/i for i in wall_times]
plt.figure(2)
plt.plot(num_threads[1:], speedups[1:])
plt.xlabel('the numver of threads')
plt.ylabel('speedup') # 加速比
plt.title('the relation between speedup and the number of thread')
plt.grid(True)

# 研究效率
efficiencys = [speedup/num_thread for speedup,num_thread in zip(speedups,num_threads)]
plt.figure(3)
plt.plot(num_threads[1:], efficiencys[1:])
plt.xlabel('the number of threads')
plt.ylabel('efficiency')
plt.title('the relation between efficiency and the number of thread')
plt.grid(True)
plt.show()
