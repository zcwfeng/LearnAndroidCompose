#include <jni.h>
//#include "inc/fmod.hpp"
#include <fmod.hpp>
#include <unistd.h>
//
// Created by zcwfeng on 2023/8/28.
//
#include "common.h"
#include "pthread.h"

// 此处代码是，上层六个常量所对应的，六个宏

#undef top_zcwfeng_learncompose_native_fmod_MODE_NORMAL
#define top_zcwfeng_learncompose_native_fmod_MODE_NORMAL 0L
#undef top_zcwfeng_learncompose_native_fmod_MODE_LUOLI
#define top_zcwfeng_learncompose_native_fmod_MODE_LUOLI 1L
#undef top_zcwfeng_learncompose_native_fmod_MODE_DASHU
#define top_zcwfeng_learncompose_native_fmod_MODE_DASHU 2L
#undef top_zcwfeng_learncompose_native_fmod_MODE_JINGSONG
#define top_zcwfeng_learncompose_native_fmod_MODE_JINGSONG 3L
#undef top_zcwfeng_learncompose_native_fmod_MODE_GAOGUAI
#define top_zcwfeng_learncompose_native_fmod_MODE_GAOGUAI 4L
#undef top_zcwfeng_learncompose_native_fmod_MODE_KONGLING
#define top_zcwfeng_learncompose_native_fmod_MODE_KONGLING 5L



// 音效系统
FMOD::System * system = 0;
// 声音
FMOD::Sound * sound = 0;
// 音轨,声音放在上面
FMOD::Channel * channel = 0;
// DSP 声音处理
FMOD::DSP *dsp = 0;
char * _content = "默认 播放完毕";
const char * _path;

void* player_run(void * args){
//    jint mode = reinterpret_cast<jint>(args);

    // 监听是否channel 结束，一直等待（应该用pthread）
    bool isPlayer = 9;
    while (isPlayer) {
        channel->isPlaying(&isPlayer);
//        usleep(1000 * 1000);
    }
    LOGD("Thread C++ FMOD mode")
    return nullptr;
};

extern "C"
JNIEXPORT void JNICALL
Java_top_zcwfeng_learncompose_native_fmod_FmodDemo_voiceChangeNative(JNIEnv *env, jobject thiz,
                                                                     jint mode, jstring path) {
    LOGD("%s","voice begin....")

    _path = env->GetStringUTFChars(path,NULL);

    FMOD::System_Create(&system);

    system->init(32,FMOD_INIT_NORMAL,0);

    system->createSound(_path,FMOD_DEFAULT,0,&sound);

    system->playSound(sound,0,false,&channel);

    switch (mode) {
        case top_zcwfeng_learncompose_native_fmod_MODE_NORMAL:
            _content = "原声 播放完毕";
            break;
        case top_zcwfeng_learncompose_native_fmod_MODE_LUOLI:
            _content = "萝莉 播放完毕";
            // 创建DSP 的Pitch音调
            system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT,&dsp);
            // 设置Pitch
            dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH,2.0f);
            // 添加到音轨
            channel->addDSP(0,dsp);
            break;
        case top_zcwfeng_learncompose_native_fmod_MODE_DASHU:
            _content = "大叔 播放完毕";
            // 创建DSP 的Pitch音调
            system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT,&dsp);
            // 设置Pitch
            dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH,0.7f);
            // 添加到音轨
            channel->addDSP(0,dsp);
            break;
        case top_zcwfeng_learncompose_native_fmod_MODE_GAOGUAI:
            _content = "搞怪 播放完毕";

            // 小黄人，音频块
            float Frequency;
            channel->getFrequency(&Frequency);
            channel->setFrequency(Frequency * 1.5f);
            break;
        case top_zcwfeng_learncompose_native_fmod_MODE_JINGSONG:
            _content = "惊悚 播放完毕";
            system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT,&dsp);
            // 设置Pitch
            dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH,0.7f);
            // 添加到音轨
            channel->addDSP(0,dsp);

            system->createDSPByType(FMOD_DSP_TYPE_ECHO,&dsp);
            // 设置DSP
            dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY,200);
            dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK,10);
            // 添加到音轨
            channel->addDSP(1,dsp);

            system->createDSPByType(FMOD_DSP_TYPE_TREMOLO,&dsp);
            // 设置DSP
            dsp->setParameterFloat(FMOD_DSP_TREMOLO_FREQUENCY,20);
            dsp->setParameterFloat(FMOD_DSP_TREMOLO_SKEW,0.8f);
            // 添加到音轨
            channel->addDSP(2,dsp);

            break;
        case top_zcwfeng_learncompose_native_fmod_MODE_KONGLING:
            _content = "空灵 播放完毕";
            system->createDSPByType(FMOD_DSP_TYPE_ECHO,&dsp);
            // 设置DSP
            dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY,200);
            dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK,10);
            // 添加到音轨
            channel->addDSP(0,dsp);
            break;
    }

    pthread_t playerThread;
    pthread_create(&playerThread, nullptr, player_run, &mode);
    pthread_join(playerThread, nullptr);

    sound->release();
    system->close();
    system->release();
    env->ReleaseStringUTFChars(path,_path);

    // 告诉Java结束
    jclass clazz  = env->FindClass("top/zcwfeng/learncompose/native/fmod/FmodDemo");
    jmethodID jmethodId = env->GetMethodID(clazz,"playerEnd", "(Ljava/lang/String;)V");
    jstring value = env->NewStringUTF(_content);
    env->CallVoidMethod(thiz,jmethodId,value);
    LOGD("%s","voice end....")


}