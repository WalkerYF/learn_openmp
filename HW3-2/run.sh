#!/bin/bash
SAVE_DATA_FILE="time.csv"
DRAW_DATA_FILE="draw_image.py"
export QT_DEVICE_PIXEL_RATIO=0
export QT_AUTO_SCREEN_SCALE_FACTOR=1
rm save.data

# 串行时间的计算
time=`./b.out`
echo 1,$time >> $SAVE_DATA_FILE

# 并行时间的计算
for ((varible=2;varible<=5;varible = varible+1));do
    export OMP_NUM_THREADS=$varible
    echo "OMP_NUM_THREADS is  $OMP_NUM_THREADS"
    time=`./a.out`
    echo $OMP_NUM_THREADS,$time >> $SAVE_DATA_FILE
done

python.exe $DRAW_DATA_FILE $SAVE_DATA_FILE