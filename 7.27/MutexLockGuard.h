//
// Created by 方伟 on 2019-07-31.
//

#ifndef INC_7_27_MUTEXLOCKGUARD_H
#define INC_7_27_MUTEXLOCKGUARD_H

#include <pthread.h>
#include <mutex>

class MutexLockGuard{
public:
    MutexLockGuard(pthread_mutex_t& m):mutex_(m){
        pthread_mutex_lock(&mutex_);
    }
    ~MutexLockGuard(){
        pthread_mutex_unlock(&mutex_);
    }

private:
    pthread_mutex_t mutex_;
};

#endif //INC_7_27_MUTEXLOCKGUARD_H
