#!/bin/bash
SAVE_DATA_FILE=$1
NUM_THREAD=$2
DRAW_DATA_FILE="draw_image.py"
export QT_DEVICE_PIXEL_RATIO=0
export QT_AUTO_SCREEN_SCALE_FACTOR=1
export PATH=/mnt/f/ProgramData/Anaconda3:$PATH

python.exe $DRAW_DATA_FILE $SAVE_DATA_FILE