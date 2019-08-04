//
// Created by 方伟 on 2019-07-21.
//

#ifndef INC_0714_SMARTPTR_H
#define INC_0714_SMARTPTR_H


#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename T>
class SmartPtr {
private:
    T* str;
    int* count;
public:
    SmartPtr(T* s):str(s),count(new int(1)){}
    SmartPtr():str(new T()),count(new int(1)){}
    ~SmartPtr(){
        --(*count);
        if(*count == 0) {
            delete str;
            delete count;
        }
    }
    SmartPtr(const SmartPtr& sm){
        str = sm.str;
        count = sm.count;
        ++(*count);
    }
    SmartPtr& operator=(const SmartPtr& sm){
        ++(*sm.count);
        --(*count);
        if(*count == 0){
            delete str;
            delete count;
        }
        str = sm.str;
        count = sm.count;
        return *this;
    }
    void getStr(){
        cout<<*str<<endl;
    }
};

#endif //INC_0714_SMARTPTR_H
