//
// Created by 方伟 on 2019-08-01.
//

#ifndef INC_7_27_THREAD_H
#define INC_7_27_THREAD_H

#include <pthread.h>
#include <iostream>
#include <string>
#include <functional>

class Thread{
    typedef std::function<void()> ThreadFunc;
public:
    Thread(const ThreadFunc& func)
            :func_(func),autoDelete(false),
            started_(false){
        std::cout<<"Thread started"<<std::endl;
    }
    ~Thread(){
        std::cout<<"Thread end"<<std::endl;
    }

    void start(){
        pthread_create(&pthreadId, NULL, threadRoutine, this);
    }
    void join(){
        pthread_join(pthreadId, NULL);
    }
    void setAutoDelete(bool flag){
        autoDelete = flag;
    }

private:
    static void* threadRoutine(void* arg){
        Thread* td = static_cast<Thread*> (arg);
        td->run();
        if(td->autoDelete)
            delete(td);
        return nullptr;
    }
    void run(){
        func_();
    }
    pthread_t pthreadId;
    ThreadFunc func_;
    bool autoDelete;
    bool started_;
};

#endif //INC_7_27_THREAD_H
