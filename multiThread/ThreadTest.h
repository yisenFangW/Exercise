//
// Created by 方伟 on 2019-07-28.
//

#ifndef MULTITHREAD_THREADTEST_H
#define MULTITHREAD_THREADTEST_H
#include "Thread.h"
#include "unistd.h"

class ThreadTest: public Thread {
public:
    ThreadTest(){std::cout<<"ThreadTest"<<std::endl;}
    virtual ~ThreadTest(){std::cout<<"~ThreadTest"<<std::endl;}
    void run(){
        for(int i=0;i<5;++i){
            std::cout<<"this is a new thread: "<<i<<std::endl;
            sleep(1);
        }
    }
private:

};


#endif //MULTITHREAD_THREADTEST_H
