//
// Created by 方伟 on 2019-07-26.
//

#ifndef INC_0721_THREAD_H
#define INC_0721_THREAD_H

#include <iostream>
#include <pthread.h>

class Thread{
public:
    Thread():autoDelete(false){std::cout<<"Thread"<<std::endl;}
    virtual ~Thread(){std::cout<<"~Thread"<<std::endl;}
    void start(){
        std::cout<<"thread_start()"<<std::endl;
        pthread_create(&threadId, NULL, threadRun, this);
    }
    void join(){
        pthread_join(threadId, NULL);
    }

    void setAutoDelete(bool flag){
        autoDelete = flag;
    }
private:
    static void* threadRun(void* arg){
        Thread *thread = static_cast<Thread*>(arg);
        thread->run();
        if(thread->autoDelete)
            delete(thread);
        return nullptr;
    }
    virtual void run() = 0;
    pthread_t threadId;
    bool autoDelete;
};








#endif //INC_0721_THREAD_H
