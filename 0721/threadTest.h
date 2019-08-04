//
// Created by 方伟 on 2019-07-26.
//

#ifndef INC_0721_THREADTEST_H
#define INC_0721_THREADTEST_H
#include "thread.h"
#include <iostream>
#include <unistd.h>

class ThreadTest : public Thread {
public:
    ThreadTest(int count):count_(count){std::cout<<"ThreadTest"<<std::endl;}
    virtual ~ThreadTest(){std::cout<<"~ThreadTest"<<std::endl;}
    void run(){
        std::cout<<"test_run()"<<std::endl;
        while(count_--){
            std::cout<<count_+1<<std::endl;
            sleep(1);
        }
    }
private:
    int count_;
};


#endif //INC_0721_THREADTEST_H
