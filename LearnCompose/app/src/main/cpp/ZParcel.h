//
// Created by zcwfeng on 2023/9/7.
//

#ifndef LEARNCOMPOSE_ZPARCEL_H
#define LEARNCOMPOSE_ZPARCEL_H
#include <malloc.h>


class ZParcel {
private:
    long mDataPos = 0;
    char * mData = 0;
    void changePos(int pos);
    long *stringObj = NULL;

public:
    ZParcel();
    int readInt();
    void writeInt(int val);
    void setDataPosition(int mDataPos);
    virtual ~ZParcel();
};


#endif //LEARNCOMPOSE_ZPARCEL_H
