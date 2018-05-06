#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <ctime>
#include "queue.hpp"
#define NUM_THREADS 64
#define MAX_PUSH_TIMES 1000
#define MAX_POP_TIMES MAX_PUSH_TIMES

int push_times = 0;
int push_key = 0;
int finish_push_key = 0;

int pop_times = 0;
int pop_key = 0;
int finish_pop_key = 0;
ThreadSafeQueue<int> myQueue;

// 生产者，将数字放入队列中
// 保证只会push1000次
void *producer(void *num)
{
    long cycle = (long)num;
    for (int i = 0; i < cycle; i++){
        myQueue.push(1);
    }
    pthread_exit(NULL);
}

void *consumer(void *num)
{
    long cycle = (long)num;
    for (int i = 0; i < cycle; i++){
        int r = myQueue.pop();
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t producer_thread[NUM_THREADS];
    pthread_t consumer_thread[NUM_THREADS];
    pthread_attr_t attr;
    int rc;
    long t;
    void *status;

    /* Initialize and set thread detached attribute */
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    int left_push_times = MAX_PUSH_TIMES;
    int average_push_times = MAX_PUSH_TIMES / NUM_THREADS;

    for (t = 0; t < NUM_THREADS; t++)
    {
        printf("Main: creating producer %ld\n", t);
        // 对64个线程分配任务，做到尽可能平均分配
        int cur_push_times = left_push_times / (NUM_THREADS-t);
        left_push_times = left_push_times - cur_push_times;
        printf("cur_push_times:%d", cur_push_times );
        
        rc = pthread_create(&producer_thread[t], &attr, producer, (void *)cur_push_times);
        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
        printf("Main: creating consumer %ld\n", t);
        rc = pthread_create(&consumer_thread[t], &attr, consumer, (void *)cur_push_times);
        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    /* Free attribute and wait for the other threads */
    pthread_attr_destroy(&attr);
    for (t = 0; t < NUM_THREADS; t++)
    {
        rc = pthread_join(producer_thread[t], &status);
        if (rc)
        {
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
        printf("Main: completed join with thread %ld having a status of %ld\n", t, (long)status);
        rc = pthread_join(consumer_thread[t], &status);
        if (rc)
        {
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
        printf("Main: completed join with thread %ld having a status of %ld\n", t, (long)status);
    }
    printf("push_times : %d \n", myQueue.get_push_times());
    printf("pop_times : %d \n", myQueue.get_pop_times());
    printf("queue size : %d \n", myQueue.size());
    printf("Main: program completed. Exiting.\n");
    pthread_exit(NULL);
}

