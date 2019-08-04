#include <iostream>
#include <thread>
#include <mutex>
#include "ThreadTest.h"
#include "NewThread.h"

using namespace std;

std::mutex myMutex;

void foo()
{
//    std::thread::id this_id = std::this_thread::get_id();
//    myMutex.lock();
//    std::cout << "thread_func: id = " << this_id  << std::endl;
//    myMutex.unlock();
    for(int i=0;i<5;++i) {
        cout << "new thread: "<< i << endl;
        sleep(1);
    }
}

int main()
{
//    for (int i = 0; i < 4; i++)
//    {
//        std::thread t(foo, i);
//        t.join();
//        cout<<"main:"<< i <<endl;
//    }
//    ThreadTest* tt = new ThreadTest();
//    tt->setAutoDelete(true);
//    tt->start();
//    tt->join();
    NewThread* nt = new NewThread(foo);
    nt->setAutoDelete(true);
    nt->start();
    nt->join();
    getchar();
    return 0;
}