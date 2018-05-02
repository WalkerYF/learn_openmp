#!/bin/bash
SAVE_DATA_FILE=$1
NUM_THREAD=$2
DRAW_DATA_FILE="draw_image.py"
export QT_DEVICE_PIXEL_RATIO=0
export QT_AUTO_SCREEN_SCALE_FACTOR=1
export PATH=/mnt/f/ProgramData/Anaconda3:$PATH
make
# 串行时间的计算
time=`./a.exe 10`
echo 1,$time > $SAVE_DATA_FILE

# 并行时间的计算
for ((varible=2;varible<=8;varible = varible+2));do
    echo "OMP_NUM_THREADS is  $OMP_NUM_THREADS"
    time=`./b.exe $varible`
    echo $varible,$time >> $SAVE_DATA_FILE
done
for ((varible=10;varible<=300;varible = varible+10));do
    echo "OMP_NUM_THREADS is  $OMP_NUM_THREADS"
    time=`./b.exe $varible`
    echo $varible,$time >> $SAVE_DATA_FILE
done
for ((varible=310;varible<=$NUM_THREAD;varible = varible+50));do
    echo "OMP_NUM_THREADS is  $OMP_NUM_THREADS"
    time=`./b.exe $varible`
    echo $varible,$time >> $SAVE_DATA_FILE
done

python.exe $DRAW_DATA_FILE $SAVE_DATA_FILE