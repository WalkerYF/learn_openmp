#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
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
void *producer(void *t)
{
    long tid = (long)t;
    printf("Producer %ld starting...\n", tid);
    while(!finish_push_key){
        while(__sync_val_compare_and_swap(&push_key, 0, 1) == 1);
        // 临界区
        if(push_times < MAX_PUSH_TIMES){
            push_times++;
            myQueue.push(1);
            printf("push_times:%d\n", push_times);
            printf("queue.size():%d\n", myQueue.size());
        }
        else
            finish_push_key = 1;
        // 临界区结束
        push_key = 0;
    }
    printf("Producer %ld done.\n", tid);
    pthread_exit((void *)t);
}


// 保证只会pop1000次
void *consumer(void *t)
{
    long tid = (long)t;
    printf("Consumer %ld starting...\n", tid);
    while(!finish_pop_key){
        while(__sync_val_compare_and_swap(&pop_key, 0, 1) == 1);
        // 临界区
        if(pop_times < MAX_POP_TIMES){
            pop_times++;
            myQueue.pop();
            printf("pop_times:%d\n", pop_times);
            printf("queue.size():%d\n", myQueue.size());
        }
        else
            finish_pop_key = 1;
        // 临界区结束
        pop_key = 0;
    }
    printf("Consumer %ld done.\n", tid);
    pthread_exit((void *)t);
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

    for (t = 0; t < NUM_THREADS; t++)
    {
        printf("Main: creating producer %ld\n", t);
        rc = pthread_create(&producer_thread[t], &attr, producer, (void *)t);
        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }

    }

    for (t = 0; t < NUM_THREADS; t++)
    {
        printf("Main: creating consumer %ld\n", t);
        rc = pthread_create(&consumer_thread[t], &attr, consumer, (void *)t);
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

