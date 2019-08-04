//
// Created by 方伟 on 2019-07-28.
//

#ifndef MULTITHREAD_NEWTHREAD_H
#define MULTITHREAD_NEWTHREAD_H

#include <iostream>
#include <functional>

class NewThread{
public:
    typedef std::function<void()> threadFunc;

    explicit NewThread(const threadFunc& func):autoDelete(false),func_(func){
        std::cout<<"Thread"<<std::endl;
    }
     ~NewThread(){std::cout<<"~Thread"<<std::endl;}
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
        NewThread* td = static_cast<NewThread*>(arg);
        td->run();
        if(td->autoDelete)
            delete(td);
        return nullptr;
    }
    void run(){
        func_();
    }
    threadFunc func_;
    pthread_t threadId;
    bool autoDelete;
};

#endif //MULTITHREAD_NEWTHREAD_H
