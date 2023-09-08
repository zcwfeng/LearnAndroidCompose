//
// Created by zcwfeng on 2023/9/7.
//

#include "ZParcel.h"
ZParcel::ZParcel() {
    this->mData = static_cast<char *>(malloc(1024));
}

ZParcel::~ZParcel() {
    if(this->mData){
        free(this->mData);
    }
    if(this->mData){
        this->mData = NULL;
    }
}

int ZParcel::readInt() {
    int ret = * reinterpret_cast<int*>(this->mData + this->mDataPos);
    changePos(sizeof(int));
    return ret;
}

void ZParcel::writeInt(int val) {
    *reinterpret_cast<int *>(mData + mDataPos) = val;
    changePos(sizeof(val));
}

void ZParcel::setDataPosition(int mDataPos) {
    this->mDataPos = mDataPos;
}

void ZParcel::changePos(int pos) {
    this->mDataPos += pos;
}
