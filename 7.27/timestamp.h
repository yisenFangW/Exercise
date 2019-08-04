//
// Created by 方伟 on 2019-07-28.
//

#ifndef INC_7_27_TIMESTAMP_H
#define INC_7_27_TIMESTAMP_H

#include <cstdint>
#include <algorithm>
#include <string>

class Timestamp {
public:
    Timestamp():microSecondsSinceEpoch_(0){}

    explicit Timestamp(int64_t microSecondsSinceEpochArg):
        microSecondsSinceEpoch_(microSecondsSinceEpochArg){}

    void swap(Timestamp& tt){std::swap(microSecondsSinceEpoch_, tt.microSecondsSinceEpoch_);}

    std::string toString() const;
    std::string toFormatString() const;

    int64_t microSecondsSinceEpoch(){return microSecondsSinceEpoch_;}
    static Timestamp now();

    static const int kMicroSecondsPerSecond = 1000 * 1000;
private:
    int64_t microSecondsSinceEpoch_;
};


namespace TimeSt{
    inline int getNum(){
        return 1;
    }
}

inline bool operator==(Timestamp ltt, Timestamp rtt){
    return ltt.microSecondsSinceEpoch() == rtt.microSecondsSinceEpoch();
}

inline bool operator<(Timestamp ltt, Timestamp rtt){
    return ltt.microSecondsSinceEpoch() < rtt.microSecondsSinceEpoch();
}

inline double timedifference(Timestamp ltt, Timestamp rtt){
    int64_t diff = ltt.microSecondsSinceEpoch() - rtt.microSecondsSinceEpoch();
    return static_cast<double>(diff) / Timestamp::kMicroSecondsPerSecond;
}

inline Timestamp addTime(Timestamp tt, double seconds){
    int64_t delta = static_cast<int64_t> (seconds / Timestamp::kMicroSecondsPerSecond);
    return Timestamp(tt.microSecondsSinceEpoch() + delta);
}


#endif //INC_7_27_TIMESTAMP_H
