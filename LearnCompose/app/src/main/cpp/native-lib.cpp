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
extern "C"
JNIEXPORT void JNICALL
Java_top_zcwfeng_learncompose_native_JNIDemo_testArrayAction(JNIEnv *env, jobject thiz, jint count,
                                                             jstring text_info, jintArray ints,
                                                             jobjectArray strs) {
    int _count = count;
    LOGD("count:%d\n",_count)
    const char * _text_info = env->GetStringUTFChars(text_info,NULL);
    LOGD("textInfo:%s\n",_text_info);
    env->ReleaseStringUTFChars(text_info,_text_info);
    int * _int_arr = env->GetIntArrayElements(ints,NULL);
    //jarray 子类 jintarray
    int intlens = env->GetArrayLength(ints);
    for (int i = 0; i < intlens; ++i) {
        LOGD("C++ ints item:%d\n",*(_int_arr + i))
    }
    env->ReleaseIntArrayElements(ints,_int_arr,JNI_OK);

    int strlens = env->GetArrayLength(strs);
    for (int i = 0; i < strlens; ++i) {
        jstring strItem  = static_cast<jstring>(env->GetObjectArrayElement(strs, i));
        const char * strItemC = env->GetStringUTFChars(strItem,NULL);
        LOGD("C++ string item:%s\n",strItemC);

        //release 1
        env->ReleaseStringUTFChars(strItem,strItemC);

        jstring updateValue = env->NewStringUTF("David");
        env->SetObjectArrayElement(strs,i,updateValue);

        jstring strItem2  = static_cast<jstring>(env->GetObjectArrayElement(strs, i));
        const char * strItemC2 = env->GetStringUTFChars(strItem2,NULL);
        LOGD("C++ string 修改后 item:%s\n",strItemC2)
        //release 2
        env->ReleaseStringUTFChars(strItem2,strItemC2);
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_top_zcwfeng_learncompose_native_JNIDemo_putObject(JNIEnv *env, jobject thiz, jobject student,
                                                       jstring str) {
    const char * _str = env->GetStringUTFChars(str,NULL);
    LOGD("_str:%s\n",_str);
    env->ReleaseStringUTFChars(str,_str);

    jclass  student_class =  env->FindClass("top/zcwfeng/learncompose/ui/compose/data/Student");
    //toString
    jmethodID toStringMethodId = env->GetMethodID(student_class,"toString","()Ljava/lang/String;");
    jstring toStringValueS = static_cast<jstring>(env->CallObjectMethod(student, toStringMethodId));
    const char * toStringValueC = env->GetStringUTFChars(toStringValueS,NULL);
    LOGD("toStirngValueC:%s\n",toStringValueC)
    env->ReleaseStringUTFChars(toStringValueS,toStringValueC);

    // setName
    jmethodID setNameMethodId = env->GetMethodID(student_class,"setName","(Ljava/lang/String;)V");
    env->CallVoidMethod(student,setNameMethodId,env->NewStringUTF("zhangsan"));

    // getName
    jmethodID getNameMethodId = env->GetMethodID(student_class,"getName","()Ljava/lang/String;");
    jstring getNameS = static_cast<jstring>(env->CallObjectMethod(student, getNameMethodId));
    const char * getNameC = env->GetStringUTFChars(getNameS,NULL);
    LOGD("getName:%s",getNameC);
    env->ReleaseStringUTFChars(getNameS,getNameC);

    // setAge
    jmethodID setAgeMethodId = env->GetMethodID(student_class,"setAge","(I)V");
    env->CallVoidMethod(student,setAgeMethodId,35);

    // getAge
    jmethodID getAgeMethodId = env->GetMethodID(student_class,"getAge","()I");
    int age = env->CallIntMethod(student,getAgeMethodId);
    LOGD("getAge:%d",age);

    // showInfo
    jmethodID showInfoId = env->GetStaticMethodID(student_class,"showInfo", "(Ljava/lang/String;)V");
    env->CallStaticVoidMethod(student_class,showInfoId,env->NewStringUTF("静态函数showStringInfo David"));

    env->DeleteLocalRef(student_class);
}
extern "C"
JNIEXPORT void JNICALL
Java_top_zcwfeng_learncompose_native_JNIDemo_insertObject(JNIEnv *env, jobject thiz) {
    jclass personClass = env->FindClass("top/zcwfeng/learncompose/ui/compose/data/Person");
    jobject personObj = env->AllocObject(personClass);
    jclass studentClass = env->FindClass("top/zcwfeng/learncompose/ui/compose/data/Student");
    jobject studentObj = env->AllocObject(studentClass);

    // setName
    jmethodID setNameMethodId = env->GetMethodID(studentClass,"setName","(Ljava/lang/String;)V");
    jstring nameS = env->NewStringUTF("DavidNew");
    env->CallVoidMethod(studentObj,setNameMethodId,nameS);

    // setAge
    jmethodID setAgeMethodId = env->GetMethodID(studentClass,"setAge","(I)V");
    env->CallVoidMethod(studentObj,setAgeMethodId,99);

    // static void putStudent(Student student)
    jmethodID putStudent = env->GetStaticMethodID(personClass,"putStudent",
                                                  "(Ltop/zcwfeng/learncompose/ui/compose/data/Student;)V");
    env->CallStaticVoidMethod(personClass,putStudent,studentObj);

    //Person: public void setStudent(Student student)
    jmethodID jmethodId = env->GetMethodID(personClass,"setStudent", "(Ltop/zcwfeng/learncompose/ui/compose/data/Student;)V");
    env->CallVoidMethod(personObj,jmethodId,studentObj);

    //release
    env->DeleteLocalRef(personClass);
    env->DeleteLocalRef(studentClass);
    env->DeleteLocalRef(personObj);
    env->DeleteLocalRef(studentObj);
    env->DeleteLocalRef(nameS);

}

jclass dogClass = nullptr;
extern "C"
JNIEXPORT void JNICALL
Java_top_zcwfeng_learncompose_native_JNIDemo_testQuote(JNIEnv *env, jobject thiz) {
    //局部成员
//    if(!dogClass) {
//        dogClass = env->FindClass("top/zcwfeng/learncompose/ui/compose/data/Dog");
//    }

    if(!dogClass) {
        jclass temp = env->FindClass("top/zcwfeng/learncompose/ui/compose/data/Dog");
        dogClass = static_cast<jclass>(env->NewGlobalRef(temp));
        env->DeleteLocalRef(temp);
    }

    // new Dog()
    jmethodID dogInit = env->GetMethodID(dogClass,"<init>","()V");
    jobject dog = env->NewObject(dogClass,dogInit);

    jmethodID dogInit2 = env->GetMethodID(dogClass,"<init>","(I)V");
    jobject dog2 = env->NewObject(dogClass,dogInit2,1);

    jmethodID dogInit3 = env->GetMethodID(dogClass,"<init>","(II)V");
    jobject dog3 = env->NewObject(dogClass,dogInit3,1,2);

    env->DeleteLocalRef(dog);
    env->DeleteLocalRef(dog2);
    env->DeleteLocalRef(dog3);


}
extern "C"
JNIEXPORT void JNICALL
Java_top_zcwfeng_learncompose_native_JNIDemo_delQuote(JNIEnv *env, jobject thiz) {
    if(dogClass) {
        env->DeleteGlobalRef(dogClass);
        dogClass = nullptr;
        LOGD("C++,del gloable ref 被调用")
    }

}