//
// Created by 方伟 on 2019-07-30.
//

#ifndef INC_7_27_THREADTEST_H
#define INC_7_27_THREADTEST_H

#include <pthread.h>
#include <mutex>
#include <iostream>

class ThreadTest{
public:
    ThreadTest(){
        pthread_create(&pid1, NULL, func1, NULL);
        pthread_create(&pid2, NULL, func2, NULL);
    }
    ~ThreadTest(){
        //pthread_join(pid1, NULL);
        //pthread_join(pid2, NULL);
    }

    void join(){
        pthread_join(pid1, NULL);
        pthread_join(pid2, NULL);
    }
private:
    static pthread_mutex_t mutex_;
    static pthread_cond_t cond_;
    static int count;
    pthread_t pid1, pid2;

    static void* func1(void* arg){
        pthread_mutex_lock(&mutex_);
        ++count;
        std::cout<<count<<std::endl;
        pthread_mutex_unlock(&mutex_);
    }
    static void* func2(void* arg){
        pthread_mutex_lock(&mutex_);
        std::cout<<"func2"<<std::endl;
        while(count >= 100)
            count = 0;
        pthread_mutex_unlock(&mutex_);
    }
};

int ThreadTest::count = 0;
pthread_mutex_t ThreadTest::mutex_ = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t ThreadTest::cond_ = PTHREAD_COND_INITIALIZER;

#endif //INC_7_27_THREADTEST_H
