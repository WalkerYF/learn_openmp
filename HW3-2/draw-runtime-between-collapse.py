import sys
import matplotlib.pyplot as plt

# 从命令行参数中获取数据来源以及保存的图片文件名
data_file_name_1 = "times-1-no-opt-200.csv"
data_file_name_2 = "times-2-no-opt-200.csv"
data_file_name_3 = "times-3-no-opt-200.csv"
# save_image_name = sya.argv[2]
num_threads = []
num_collapse = []
matrix_size = []
cpu_times = []
wall_times = []

def read_file_get_num_and_time(file_name):
    cur_num_threads = []
    cur_wall_times = []
    with open(file_name, 'r') as f:
        for line in f.readlines():
            num_str_list = line.split(',')
            if len(num_str_list) != 5:
                break
            cur_num_threads.append(int(num_str_list[0]))
            # cpu_times.append(float(num_str_list[3]))
            cur_wall_times.append(float(num_str_list[4]))
    return cur_num_threads,cur_wall_times

num_threads_1,wall_times_1 = read_file_get_num_and_time(data_file_name_1)
num_threads_2,wall_times_2 = read_file_get_num_and_time(data_file_name_2)
num_threads_3,wall_times_3 = read_file_get_num_and_time(data_file_name_3)


plt.plot(num_threads_1[1:], wall_times_1[1:], 'b--',label='collaspe(1)')
plt.plot(num_threads_2[1:], wall_times_2[1:], 'r*-',label='collaspe(2)')
plt.plot(num_threads_3[1:], wall_times_3[1:], 'g^-',label='collaspe(3)')
plt.xlabel('the number of threads')
plt.ylabel('average running time/second')
plt.title('the relation between the number of threads and thr running time of matrix\'s product')
# plt.text(60, .025, r'$\mu=100,\ \sigma=15$')
# plt.axis([40, 160, 0, 0.03])
plt.grid(True)
plt.show()
