import sys
import matplotlib.pyplot as pt
# print ("脚本名：", sys.argv[0])
# for i in range(1, len(sys.argv)):
#     print ("参数", i, sys.argv[i])

# 从命令行参数中获取数据来源以及保存的图片文件名
data_file_name = sys.argv[1]
# save_image_name = sya.argv[2]
xs = []
times = []
with open(data_file_name, 'r') as f:
    for line in f.readlines():
        num_str_list = line.split(',')
        xs.append(int(num_str_list[0]))
        times.append(float(num_str_list[1]))
pt.plot(xs, times)
pt.show()
