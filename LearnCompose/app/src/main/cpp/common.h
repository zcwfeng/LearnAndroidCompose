//
// Created by zcwfeng on 2023/8/29.
//
#ifndef LEARNCOMPOSE_COMMON_H
#define LEARNCOMPOSE_COMMON_H
#define TAG "zcwfeng.top"
#include "android/log.h"
// __VA_ARGS__ 代表...的可变参数
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__);
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__);
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__);
#endif //LEARNCOMPOSE_COMMON_H
