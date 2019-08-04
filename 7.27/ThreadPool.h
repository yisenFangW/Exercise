//
// Created by 方伟 on 2019-08-01.
//

#ifndef INC_7_27_THREADPOOL_H
#define INC_7_27_THREADPOOL_H

#include <iostream>
#include <deque>
#include <vector>
#include <mutex>
#include <pthread.h>
#include <string>
#include <functional>
#include "MessageQueue.h"
#include "Thread.h"

using namespace std;

class ThreadPool {
    typedef function<void()> Task;

public:
    ThreadPool(const string& s = string("ThreadPool")):name_(s){}
    ~ThreadPool(){}

    void setMaxSize(size_t num){ maxQueueSize_ = num; }

    void start(int numThread);

    void stop();

    const string& name(){return name_;}

    size_t queueSize() const;

    void run(Task f);


private:
    bool isFull() const;
    void runInThread();

    string name_;
    bool running_;
    pthread_mutex_t mutex;
    Task task;
    vector<unique_ptr<Thread>> thread_;
    deque<Task> queue_;
    size_t maxQueueSize_;
};


#endif //INC_7_27_THREADPOOL_H
