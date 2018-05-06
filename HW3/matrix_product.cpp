#include <random>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <omp.h>
using namespace std;
#ifndef MATRIX_SIZE
#define MATRIX_SIZE 1200
#endif

#ifndef COLLAPSE_NUM
#define COLLAPSE_NUM 1
#endif

typedef double matrix_t;

matrix_t lhs[MATRIX_SIZE][MATRIX_SIZE];
matrix_t rhs[MATRIX_SIZE][MATRIX_SIZE];
matrix_t ans[MATRIX_SIZE][MATRIX_SIZE];

void product(){
    for (int i = 0; i < MATRIX_SIZE; i++){
        #ifdef OPT
        for (int k = 0; k < MATRIX_SIZE; k++){
            for (int j = 0; j < MATRIX_SIZE; j++){
                ans[i][j] += lhs[i][k]*rhs[k][j];
        #endif
        #ifdef NOT_OPT
        for (int j = 0; j < MATRIX_SIZE; j++){
            for (int k = 0; k < MATRIX_SIZE; k++){
                ans[i][j] += lhs[i][k]*rhs[k][j];
        #endif
            }
        }
    }
}

void parallel_product(){
    # pragma omp parallel
    # pragma omp for collapse(COLLAPSE_NUM)
    for (int i = 0; i < MATRIX_SIZE; i++){
        #ifdef OPT
        for (int k = 0; k < MATRIX_SIZE; k++){
            for (int j = 0; j < MATRIX_SIZE; j++){
        #endif
        #ifdef NOT_OPT
        for (int j = 0; j < MATRIX_SIZE; j++){
            for (int k = 0; k < MATRIX_SIZE; k++){
        #endif
                ans[i][j] += lhs[i][k]*rhs[k][j];
            }
            // printf("pid:%d \n", omp_get_thread_num());
        }
    }
}

void print_matrix(matrix_t mat[][MATRIX_SIZE]){
    for (int i = 0; i < MATRIX_SIZE; i++){
        for (int j = 0; j < MATRIX_SIZE; j++){
            cout << mat[i][j] << ",";
        }
        cout << endl;
    }
}

// 使用随机数生成矩阵
void make_matrix(matrix_t mat[][MATRIX_SIZE], int seed){
    srand(seed);
    for (int i = 0; i < MATRIX_SIZE; i++){
        for (int j = 0; j < MATRIX_SIZE; j++){
            mat[i][j] = double(rand()%100000)*1.1;
            // mat[i][j] = 2;
        }
    }
}

void init_matrix(matrix_t mat[][MATRIX_SIZE]){
    for (int i = 0; i < MATRIX_SIZE; i++){
        for (int j = 0; j < MATRIX_SIZE; j++){
            mat[i][j] = 0;
        }
    }
}

void get_time(void (*func)(), int repeat_time = 2){
    // TODO:设置重复次数
    clock_t startTime,endTime;
    double wall_time = 0;
    double full_time = 0;
    double full_wall_time = 0;
    for (int i = 0;i < repeat_time; i++){
        startTime = clock();
        wall_time = omp_get_wtime();
        func();
        endTime = clock();
        full_time += (double)(endTime - startTime) / CLOCKS_PER_SEC;
        full_wall_time += omp_get_wtime() - wall_time;
    }
    // cout << "Totle Time : " << setprecision(20) << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    double average_cpu_time = full_time / repeat_time;
    double average_wall_time = full_wall_time / repeat_time;
    // cout << "average_cpu_time : " << average_cpu_time << endl;
    // cout << "average_wall_time : " << average_wall_time << endl;
    #ifdef OPT
    cout << COLLAPSE_NUM << "," << MATRIX_SIZE << ","  << average_cpu_time << "," << average_wall_time << "," << 1 << endl;
    #endif
    #ifdef NOT_OPT
    cout << COLLAPSE_NUM << "," << MATRIX_SIZE << ","  << average_cpu_time << "," << average_wall_time << "," << 0 << endl;
    #endif
}

int str_to_int(char * str){
    int len = strlen(str);
    int num = 0;
    for (int i = 0; i < len; i++){
        num = (str[i]-'0') + num * 10;
    }
    return num;
}

int main(int argc, char* argv[]){
    // cout << MATRIX_SIZE << endl;
    make_matrix(lhs,1);
    make_matrix(rhs,2);
    init_matrix(ans);
    int num_thread = str_to_int(argv[1]);
    // cout << "num_thread:" << num_thread << endl;
    // cout << "num_thread:" << str_to_int(num_thread) << endl;
    omp_set_num_threads(num_thread);
    // cout << "omp_get_num_threads():" << omp_get_num_threads() << endl;
    #ifdef SINGLE
    get_time(product);
    #endif
    #ifdef PARALLEL
    get_time(parallel_product);
    #endif
    return 0;
}