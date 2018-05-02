#include <random>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#define MATRIX_SIZE 700
using namespace std;

typedef double matrix_t;

matrix_t lhs[MATRIX_SIZE][MATRIX_SIZE];
matrix_t rhs[MATRIX_SIZE][MATRIX_SIZE];
matrix_t ans[MATRIX_SIZE][MATRIX_SIZE];
void product(){
    # pragma omp parallel for
    for (int i = 0; i < MATRIX_SIZE; i++){
        # pragma omp parallel for
        for (int j = 0; j < MATRIX_SIZE; j++){
            # pragma omp parallel for
            for (int k = 0; k < MATRIX_SIZE; k++){
                ans[i][j] += lhs[i][k]*rhs[k][j];
            }
        }
    }
}
// void product(){
//     for (int i = 0; i < MATRIX_SIZE; i++){
//         for (int j = 0; j < MATRIX_SIZE; j++){
//             for (int k = 0; k < MATRIX_SIZE; k++){
//                 ans[i][j] += lhs[i][k]*rhs[k][j];
//             }
//         }
//     }
// }

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

int main(){
    make_matrix(lhs,1);
    make_matrix(rhs,2);
    init_matrix(ans);

    clock_t startTime,endTime;
    int repeat_time = 2;
    double full_time = 0;
    for (int i = 0;i < repeat_time; i++){
        startTime = clock();
        product();
        endTime = clock();
        full_time += (double)(endTime - startTime) / CLOCKS_PER_SEC;
    }
    // cout << "Totle Time : " << setprecision(20) << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    double avarage_time = full_time / repeat_time;
    cout << avarage_time <<  endl;
    // print_matrix(ans);
    return 0;
}