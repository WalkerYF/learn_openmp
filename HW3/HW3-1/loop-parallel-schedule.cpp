#include <iostream>
#include <ctime>
#include <omp.h>
using namespace std;

#ifndef DELAY_MIN_TIMES
#define DELAY_MIN_TIMES 100
#endif

#ifndef DELAY_MAX_TIMES
#define DELAY_MAX_TIMES 10000
#endif

// #ifndef DELAY_TIMES
// #define DELAY_TIMES 10000
// #endif

int data[DELAY_MAX_TIMES][DELAY_MAX_TIMES];
int sum = 0;
int num_threads = 0;

void parallel_delay(int times){
    # pragma omp parallel
    {
        num_threads = omp_get_num_threads();
        # pragma omp for schedule(runtime)
        for (int i = 0; i < times; i++){
            for (int j = 0; j < times; j++){
                #ifdef NO_CACHE
                sum += i*j;
                #endif
                #ifdef USE_CACHE
                data[i][j] = i*j;
                #endif
            }
            // cout << omp_get_thread_num() << endl;
            // cout << omp_get_num_threads() << endl;
        }
    }
}

void delay(int times){
    num_threads = omp_get_num_threads();
    for (int i = 0; i < times; i++){
        for (int j = 0; j < times; j++){
            #ifdef NO_CACHE
            sum += i*j;
            #endif
            #ifdef USE_CACHE
            data[i][j] = i*j;
            #endif
        }
    }
}

void get_time(void (*func)(int ),int delay_times, int repeat_time = 3){
    clock_t startTime,endTime;
    double wall_time = 0;
    double full_time = 0;
    double full_wall_time = 0;
    for (int i = 0;i < repeat_time; i++){
        startTime = clock();
        wall_time = omp_get_wtime();
        func(delay_times);
        endTime = clock();
        full_time += (double)(endTime - startTime) / CLOCKS_PER_SEC;
        full_wall_time += omp_get_wtime() - wall_time;
    }
    double average_cpu_time = full_time / repeat_time;
    double average_wall_time = full_wall_time / repeat_time;
    omp_sched_t this_kind;
    int chunk_num = 0;
    omp_get_schedule(&this_kind, &chunk_num);

    cout << num_threads << ",";
    #ifdef NO_CACHE
    cout << 0 << ",";
    #endif
    #ifdef USE_CACHE
    cout << 1 << ",";
    #endif
    cout << this_kind << "," << chunk_num << "," << delay_times << "," << average_cpu_time << "," << average_wall_time << endl;
}


int main(){
    omp_set_num_threads(4);
    // 对不同的延时均进行测试
    for (int i = DELAY_MIN_TIMES; i <= DELAY_MAX_TIMES; i = i+100){
        #ifdef PARALLEL
        get_time(parallel_delay, i);
        #endif
        #ifdef SINGLE
        get_time(delay, i);
        #endif
    }
    return 0;
}