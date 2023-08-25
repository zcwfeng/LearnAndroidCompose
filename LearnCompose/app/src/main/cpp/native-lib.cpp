#include <jni.h>
#include <string>
#include <cstring>
#include <android/log.h>
#define TAG "zcwfeng.top"
// __VA_ARGS__ 代表...的可变参数
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__);
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__);
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__);

extern "C" JNIEXPORT jstring JNICALL
Java_top_zcwfeng_learncompose_native_JNIDemo_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}



extern "C" JNIEXPORT void JNICALL
Java_top_zcwfeng_learncompose_native_JNIDemo_changeName(
        JNIEnv *env,
        jobject thisJNIDemo/* this */) {
//    jclass clazz = env->FindClass("top/zcwfeng/learncompose/native/JNIDemo");
    jclass clazz = env->GetObjectClass(thisJNIDemo);
//    jfieldID GetFieldID(jclass clazz, const char* name, const char* sig)
//    val name = "David" // 等下 用 C++代码，修改为Beyond
//    external fun changeName() // 改变我们的属性name
    jfieldID nameFild = env->GetFieldID(clazz, "name", "Ljava/lang/String;");
//    void SetObjectField(jobject obj, jfieldID fieldID, jobject value)
    jstring value = env->NewStringUTF("Beyound");
    env->SetObjectField(thisJNIDemo, nameFild, value);
}

extern "C"
JNIEXPORT void JNICALL
Java_top_zcwfeng_learncompose_native_JNIDemo_changeAge(JNIEnv *env, jclass clazz) {

//    jfieldID GetStaticFieldID(jclass clazz, const char* name, const char* sig)
    jfieldID ageFild = env->GetStaticFieldID(clazz, "age", "I");
//    void SetIntField(jobject obj, jfieldID fieldID, jint value)
    env->SetStaticIntField(clazz, ageFild, env->GetStaticIntField(clazz, ageFild) + 1);
    LOGD("Test Log %s","change age")

}
extern "C"
JNIEXPORT void JNICALL
Java_top_zcwfeng_learncompose_native_JNIDemo_callAddMethod(JNIEnv *env, jobject thiz) {
    jclass clazz = env->GetObjectClass(thiz);
    jmethodID addMid = env->GetMethodID(clazz,"addMethod", "(II)I");
    int result = env->CallIntMethod(thiz,addMid,12,12);
    LOGD("result is:%d\n",result)

}
extern "C"
JNIEXPORT void JNICALL
Java_top_zcwfeng_learncompose_native_JNIDemo_callShowStringMethod(JNIEnv *env, jobject thiz) {
    jclass clazz = env->GetObjectClass(thiz);
    jmethodID mid = env->GetMethodID(clazz,"showString", "(Ljava/lang/String;I)Ljava/lang/String;");
    jstring result = static_cast<jstring>(env->CallObjectMethod(thiz, mid,
                                                                env->NewStringUTF("David"), 12));
    const char * value = env->GetStringUTFChars(result,NULL);
    LOGD("result is:%s\n",value)
}