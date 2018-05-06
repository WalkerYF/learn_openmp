#!/bin/bash
MATRIX_SIZE=700
SAVE_FILE_SIZE=all_time_win.csv
MAX_NUM_THREADS=50
echo 'num_thread,collaspe,size,cputime,walltime,cache_opt' >> $SAVE_FILE_SIZE
./run.sh matrix_product.cpp 1 $MATRIX_SIZE OPT $SAVE_FILE_SIZE $MAX_NUM_THREADS
./run.sh matrix_product.cpp 2 $MATRIX_SIZE OPT $SAVE_FILE_SIZE $MAX_NUM_THREADS
./run.sh matrix_product.cpp 3 $MATRIX_SIZE OPT $SAVE_FILE_SIZE $MAX_NUM_THREADS
./run.sh matrix_product.cpp 1 $MATRIX_SIZE NOT_OPT $SAVE_FILE_SIZE $MAX_NUM_THREADS
./run.sh matrix_product.cpp 2 $MATRIX_SIZE NOT_OPT $SAVE_FILE_SIZE $MAX_NUM_THREADS
./run.sh matrix_product.cpp 3 $MATRIX_SIZE NOT_OPT $SAVE_FILE_SIZE $MAX_NUM_THREADS

rm a.exe
rm b.exe