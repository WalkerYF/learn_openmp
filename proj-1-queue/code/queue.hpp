#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <iostream>
#include <queue>
#include <pthread.h>
#include <ctime>

template <typename T>
class ThreadSafeQueue{
public:
    ThreadSafeQueue(int size = 200){
        this->pop_times = 0;
        this->push_times = 0;
        this->_size = size;
    }
    void push(T contents){
        while(this->full());
        pthread_mutex_lock(&this->_mutex);
        // printf("Get the %s lock!\n","mutex in push" );
        _queue.push(contents);
        this->push_times++;
        // printf("Release the %s lock!\n","mutex in push" );
        pthread_mutex_unlock(&this->_mutex);
    }
    T pop(){
        while(_queue.size() == 0);
        pthread_mutex_lock(&this->_mutex);
        // printf("Get the %s lock!\n","mutex in pop" );
        // 自旋锁，如果队列空，锁住直至有新元素加入
        T r = _queue.front();
        _queue.pop();
        this->pop_times++;
        // printf("Release the %s lock!\n","mutex in pop" );
        pthread_mutex_unlock(&this->_mutex);
        return r;
    }
    T front(){
        return _queue.front();
    }
    T back(){
        return _queue.back();
    }
    T size(){
        return _queue.size();
    }
    T full(){
        return _size == this->size();
    }
    int get_push_times(){
        return push_times;
    }
    int get_pop_times(){
        return pop_times;
    }
private:
    std::queue<T> _queue;
    pthread_mutex_t _mutex;
    int _size;
    int push_times;
    int pop_times;
};

#endif
