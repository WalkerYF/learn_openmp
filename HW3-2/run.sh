#!/bin/bash
SAVE_DATA_FILE="save.data"
DRAW_DATA_FILE="draw_image.py"
export QT_DEVICE_PIXEL_RATIO=0
export QT_AUTO_SCREEN_SCALE_FACTOR=1
rm save.data
for ((varible=2;varible<=101;varible = varible+10));do
    export OMP_NUM_THREADS=$varible
    echo "OMP_NUM_THREADS is  $OMP_NUM_THREADS"
    time=`./a.out`
    echo $OMP_NUM_THREADS,$time >> save.data
done

python.exe $DRAW_DATA_FILE $SAVE_DATA_FILE