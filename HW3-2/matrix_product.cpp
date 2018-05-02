#include <random>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <omp.h>
using namespace std;

#define MATRIX_SIZE 200
#define COLLAPSE_NUM 3

typedef double matrix_t;

matrix_t lhs[MATRIX_SIZE][MATRIX_SIZE];
matrix_t rhs[MATRIX_SIZE][MATRIX_SIZE];
matrix_t ans[MATRIX_SIZE][MATRIX_SIZE];

void product(){
    for (int i = 0; i < MATRIX_SIZE; i++){
        for (int k = 0; k < MATRIX_SIZE; k++){
        for (int j = 0; j < MATRIX_SIZE; j++){
                ans[i][j] += lhs[i][k]*rhs[k][j];
            }
        }
    }
}

void parallel_product(){
    # pragma omp parallel
    # pragma omp for collapse(3)
    // # pragma omp for
    for (int i = 0; i < MATRIX_SIZE; i++){
        for (int k = 0; k < MATRIX_SIZE; k++){
        for (int j = 0; j < MATRIX_SIZE; j++){
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
    cout << COLLAPSE_NUM << "," << MATRIX_SIZE << ","  << average_cpu_time << "," << average_wall_time << endl;
}
int main(int argc, char* argv[]){
    make_matrix(lhs,1);
    make_matrix(rhs,2);
    init_matrix(ans);
    int num_thread = stoi(argv[1]);
    // cout << "num_thread:" << num_thread << endl;
    omp_set_num_threads(num_thread);
    // cout << "omp_get_num_threads():" << omp_get_num_threads() << endl;
    #ifdef SIMGLE
    get_time(product);
    #endif
    #ifdef PARALLEL
    get_time(parallel_product);
    #endif
    // print_matrix(ans);
    return 0;
}