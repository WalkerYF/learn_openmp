#!/bin/bash
MATRIX_SIZE=1200
SAVE_FILE_SIZE=all_time.csv
./run2.sh matrix_product.cpp 1 $MATRIX_SIZE OPT $SAVE_FILE_SIZE 
./run2.sh matrix_product.cpp 2 $MATRIX_SIZE OPT $SAVE_FILE_SIZE
./run2.sh matrix_product.cpp 3 $MATRIX_SIZE OPT $SAVE_FILE_SIZE
./run2.sh matrix_product.cpp 1 $MATRIX_SIZE NOT_OPT $SAVE_FILE_SIZE 
./run2.sh matrix_product.cpp 2 $MATRIX_SIZE NOT_OPT $SAVE_FILE_SIZE
./run2.sh matrix_product.cpp 3 $MATRIX_SIZE NOT_OPT $SAVE_FILE_SIZE
