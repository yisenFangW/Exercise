//
// Created by 方伟 on 2019-07-31.
//

#ifndef INC_7_27_MESSAGEQUEUE_H
#define INC_7_27_MESSAGEQUEUE_H

#include <deque>
#include <iostream>
#include <mutex>
#include <pthread.h>
#include "MutexLockGuard.h"


template <typename T>
class MessageQueue{
public:
    MessageQueue():size(0),
        mutex_(),cond_(){
    }
    void push(const T& t){
        //我开始没有生成对象，肯定不行的啊
        MutexLockGuard lock(mutex_);
        queue_.push_back(t);
    }
    T pop(){
        //因为这个函数改变了queue_的值，怎么阔以声明为const函数呢
        //在用condition时，必须要在前面用上mutex锁；
        MutexLockGuard lock(mutex_);
        while(queue_.empty()){
            pthread_cond_wait(&cond_, &mutex_);
        }
        T tmp = queue_.front();
        queue_.pop_front();
        return tmp;
    }
    size_t getQueueSize() const{
        return queue_.size();
    }
private:
    std::deque<T> queue_;
    size_t size;
    pthread_mutex_t mutex_;
    pthread_cond_t cond_;
};

#endif //INC_7_27_MESSAGEQUEUE_H
