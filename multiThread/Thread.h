//
// Created by 方伟 on 2019-07-28.
//

#ifndef MULTITHREAD_THREAD_H
#define MULTITHREAD_THREAD_H

#include <pthread.h>
#include <iostream>

class Thread{
public:
    Thread():autoDelete(false){std::cout<<"Thread"<<std::endl;}
    virtual ~Thread(){std::cout<<"~Thread"<<std::endl;}
    void start(){
        std::cout<<"start run"<<std::endl;
        pthread_create(&threadId, NULL , threadRoutine, this);
    }
    void join(){
        pthread_join(threadId, NULL);
    }
    void setAutoDelete(bool flag){
        autoDelete = flag;
    }

private:
    static void* threadRoutine(void* arg){
        Thread* td = static_cast<Thread*>(arg);
        td->run();
        if(td->autoDelete)
            delete(td);
        return nullptr;
    }
    virtual void run() = 0;
    pthread_t threadId;
    bool autoDelete;
};

#endif //MULTITHREAD_THREAD_H
