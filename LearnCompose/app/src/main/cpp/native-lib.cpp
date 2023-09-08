#include <jni.h>
#include <string>
#include <cstring>
#include "common.h"
#include "ZParcel.h"
#include <pthread.h>

class MyContext {
public:
//    JNIEnv *jniEnv;// 无法提升全局成员
    jobject obj = nullptr;// 可以提升
};


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
    LOGD("Test Log %s", "change age")

}
extern "C"
JNIEXPORT void JNICALL
Java_top_zcwfeng_learncompose_native_JNIDemo_callAddMethod(JNIEnv *env, jobject thiz) {
    jclass clazz = env->GetObjectClass(thiz);
    jmethodID addMid = env->GetMethodID(clazz, "addMethod", "(II)I");
    int result = env->CallIntMethod(thiz, addMid, 12, 12);
    LOGD("result is:%d\n", result)

}
extern "C"
JNIEXPORT void JNICALL
Java_top_zcwfeng_learncompose_native_JNIDemo_callShowStringMethod(JNIEnv *env, jobject thiz) {
    jclass clazz = env->GetObjectClass(thiz);
    jmethodID mid = env->GetMethodID(clazz, "showString",
                                     "(Ljava/lang/String;I)Ljava/lang/String;");
    jstring result = static_cast<jstring>(env->CallObjectMethod(thiz, mid,
                                                                env->NewStringUTF("David"), 12));
    const char *value = env->GetStringUTFChars(result, NULL);
    LOGD("result is:%s\n", value)
}
extern "C"
JNIEXPORT void JNICALL
Java_top_zcwfeng_learncompose_native_JNIDemo_testArrayAction(JNIEnv *env, jobject thiz, jint count,
                                                             jstring text_info, jintArray ints,
                                                             jobjectArray strs) {
    int _count = count;
    LOGD("count:%d\n", _count)
    const char *_text_info = env->GetStringUTFChars(text_info, NULL);
    LOGD("textInfo:%s\n", _text_info);
    env->ReleaseStringUTFChars(text_info, _text_info);
    int *_int_arr = env->GetIntArrayElements(ints, NULL);
    //jarray 子类 jintarray
    int intlens = env->GetArrayLength(ints);
    for (int i = 0; i < intlens; ++i) {
        LOGD("C++ ints item:%d\n", *(_int_arr + i))
    }
    env->ReleaseIntArrayElements(ints, _int_arr, JNI_OK);

    int strlens = env->GetArrayLength(strs);
    for (int i = 0; i < strlens; ++i) {
        jstring strItem = static_cast<jstring>(env->GetObjectArrayElement(strs, i));
        const char *strItemC = env->GetStringUTFChars(strItem, NULL);
        LOGD("C++ string item:%s\n", strItemC);

        //release 1
        env->ReleaseStringUTFChars(strItem, strItemC);

        jstring updateValue = env->NewStringUTF("David");
        env->SetObjectArrayElement(strs, i, updateValue);

        jstring strItem2 = static_cast<jstring>(env->GetObjectArrayElement(strs, i));
        const char *strItemC2 = env->GetStringUTFChars(strItem2, NULL);
        LOGD("C++ string 修改后 item:%s\n", strItemC2)
        //release 2
        env->ReleaseStringUTFChars(strItem2, strItemC2);
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_top_zcwfeng_learncompose_native_JNIDemo_putObject(JNIEnv *env, jobject thiz, jobject student,
                                                       jstring str) {
    const char *_str = env->GetStringUTFChars(str, NULL);
    LOGD("_str:%s\n", _str);
    env->ReleaseStringUTFChars(str, _str);

    jclass student_class = env->FindClass("top/zcwfeng/learncompose/ui/compose/data/Student");
    //toString
    jmethodID toStringMethodId = env->GetMethodID(student_class, "toString",
                                                  "()Ljava/lang/String;");
    jstring toStringValueS = static_cast<jstring>(env->CallObjectMethod(student, toStringMethodId));
    const char *toStringValueC = env->GetStringUTFChars(toStringValueS, NULL);
    LOGD("toStirngValueC:%s\n", toStringValueC)
    env->ReleaseStringUTFChars(toStringValueS, toStringValueC);

    // setName
    jmethodID setNameMethodId = env->GetMethodID(student_class, "setName", "(Ljava/lang/String;)V");
    env->CallVoidMethod(student, setNameMethodId, env->NewStringUTF("zhangsan"));

    // getName
    jmethodID getNameMethodId = env->GetMethodID(student_class, "getName", "()Ljava/lang/String;");
    jstring getNameS = static_cast<jstring>(env->CallObjectMethod(student, getNameMethodId));
    const char *getNameC = env->GetStringUTFChars(getNameS, NULL);
    LOGD("getName:%s", getNameC);
    env->ReleaseStringUTFChars(getNameS, getNameC);

    // setAge
    jmethodID setAgeMethodId = env->GetMethodID(student_class, "setAge", "(I)V");
    env->CallVoidMethod(student, setAgeMethodId, 35);

    // getAge
    jmethodID getAgeMethodId = env->GetMethodID(student_class, "getAge", "()I");
    int age = env->CallIntMethod(student, getAgeMethodId);
    LOGD("getAge:%d", age);

    // showInfo
    jmethodID showInfoId = env->GetStaticMethodID(student_class, "showInfo",
                                                  "(Ljava/lang/String;)V");
    env->CallStaticVoidMethod(student_class, showInfoId,
                              env->NewStringUTF("静态函数showStringInfo David"));

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
    jmethodID setNameMethodId = env->GetMethodID(studentClass, "setName", "(Ljava/lang/String;)V");
    jstring nameS = env->NewStringUTF("DavidNew");
    env->CallVoidMethod(studentObj, setNameMethodId, nameS);

    // setAge
    jmethodID setAgeMethodId = env->GetMethodID(studentClass, "setAge", "(I)V");
    env->CallVoidMethod(studentObj, setAgeMethodId, 99);

    // static void putStudent(Student student)
    jmethodID putStudent = env->GetStaticMethodID(personClass, "putStudent",
                                                  "(Ltop/zcwfeng/learncompose/ui/compose/data/Student;)V");
    env->CallStaticVoidMethod(personClass, putStudent, studentObj);

    //Person: public void setStudent(Student student)
    jmethodID jmethodId = env->GetMethodID(personClass, "setStudent",
                                           "(Ltop/zcwfeng/learncompose/ui/compose/data/Student;)V");
    env->CallVoidMethod(personObj, jmethodId, studentObj);

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

    if (!dogClass) {
        jclass temp = env->FindClass("top/zcwfeng/learncompose/ui/compose/data/Dog");
        dogClass = static_cast<jclass>(env->NewGlobalRef(temp));
        env->DeleteLocalRef(temp);
    }

    // new Dog()
    jmethodID dogInit = env->GetMethodID(dogClass, "<init>", "()V");
    jobject dog = env->NewObject(dogClass, dogInit);

    jmethodID dogInit2 = env->GetMethodID(dogClass, "<init>", "(I)V");
    jobject dog2 = env->NewObject(dogClass, dogInit2, 1);

    jmethodID dogInit3 = env->GetMethodID(dogClass, "<init>", "(II)V");
    jobject dog3 = env->NewObject(dogClass, dogInit3, 1, 2);

    env->DeleteLocalRef(dog);
    env->DeleteLocalRef(dog2);
    env->DeleteLocalRef(dog3);


}
extern "C"
JNIEXPORT void JNICALL
Java_top_zcwfeng_learncompose_native_JNIDemo_delQuote(JNIEnv *env, jobject thiz) {
    if (dogClass) {
        env->DeleteGlobalRef(dogClass);
        dogClass = nullptr;
        LOGD("C++,del gloable ref 被调用")
    }

}

JavaVM *vm = nullptr;

void *cpp_thread_run(void *args) {
    LOGD("C++ pthread 的异步线程")
    MyContext *context = static_cast<MyContext *>(args);
    JNIEnv *jniEnv;
    jint r = ::vm->AttachCurrentThread(&jniEnv, nullptr);
    if (r) {
        return nullptr;
    }
//    jclass class1 = jniEnv->GetObjectClass(context->obj);
    jclass clazz = jniEnv->GetObjectClass(context->obj);
    jmethodID updateUI = jniEnv->GetMethodID(clazz, "updateUI", "()V");
    jniEnv->CallVoidMethod(context->obj, updateUI);
    ::vm->DetachCurrentThread();
    return nullptr;
}


extern "C"
JNIEXPORT void JNICALL
Java_top_zcwfeng_learncompose_native_JNIDemo_nativeThread(JNIEnv *env, jobject thiz) {
    // == 如果uiclick 那么是主线程
//    int pthread_create(pthread_t* __pthread_ptr, pthread_attr_t const* __attr, void* (*__start_routine)(void*), void*);
    MyContext *context = new MyContext;
    context->obj = env->NewGlobalRef(thiz);
    pthread_t pid;
    pthread_create(&pid, nullptr, cpp_thread_run, context);
    // 等待子线程结束之后在释放相关资源
    pthread_join(pid, nullptr);

    env->DeleteGlobalRef(context->obj);
    delete context;
    context = nullptr;

}
extern "C"
JNIEXPORT void JNICALL
Java_top_zcwfeng_learncompose_native_JNIDemo_nativeClose(JNIEnv *env, jobject thiz) {
}

// 动态注册

void dynamicAction(JNIEnv *env, jobject thiz) {
    LOGD("C++ 动态注册1")
}

int dynamicActionParam(JNIEnv *env, jobject thiz, jstring value) {
    const char *_value = env->GetStringUTFChars(value, NULL);
    LOGD("C++ 动态注册2---param %s\n", _value);
    env->ReleaseStringUTFChars(value, _value);


    return JNI_OK;
}

static const JNINativeMethod methods[] = {
        {"dynamicJavaMethod",      "()V",                   (void *) (dynamicAction)},
        {"dynamicJavaMethodParam", "(Ljava/lang/String;)I", (int *) (dynamicActionParam)}

};
extern "C"
JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {

    ::vm = vm;
    JNIEnv *env;
    jint r = vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6);
    // evn-> RegisterMethods(一次性注册 n 个动态函数)
    // 框架设计是一级指针传递地址即可 &env，如果是二级指针，需要传递一级指针地址。
    if (r != JNI_OK) {
        LOGE("C++ 动态注册环境异常")
        return -1;
    }

    jclass jniDemoClass = env->FindClass("top/zcwfeng/learncompose/native/JNIDemo");

//    typedef struct {
//        const char* name; 动态注册JNI函数名--java函数注册
//        const char* signature; 函数签名
//        void*       fnPtr; 函数指针--C++函数
//    } JNINativeMethod;
    jint code = env->RegisterNatives(jniDemoClass, methods,
                                     sizeof(methods) / sizeof(JNINativeMethod));
    if (!code) {
        LOGD("C++ 动态注册成功")

    } else {
        LOGE("C++ 动态注册失败")
    }
    return JNI_VERSION_1_6;
}

int compare(const jint *value1, const jint *value2) {
    return *value2 - *value1;
}


extern "C"
JNIEXPORT void JNICALL
Java_top_zcwfeng_learncompose_native_JNIDemo_sort(JNIEnv *env, jobject thiz, jintArray arr) {
    jint *intArray = env->GetIntArrayElements(arr, nullptr);
    int len = env->GetArrayLength(arr);
    // 排序, 工具,void qsort(void* __base, size_t __nmemb, size_t __size, int (*__comparator)(const void* __lhs, const void* __rhs));
    qsort(intArray, len, sizeof(int),
          reinterpret_cast<int (*)(const void *, const void *)>(compare));
    env->ReleaseIntArrayElements(arr, intArray, JNI_COMMIT);

}

extern "C"
JNIEXPORT void JNICALL
Java_top_zcwfeng_learncompose_native_JNIDemo_localCache(JNIEnv *env, jclass clazz, jstring name) {

// static jfieldID f_id = nullptr;
    // if (f_id == nullptr) {
    jfieldID f_id = env->GetStaticFieldID(clazz, "name1", "Ljava/lang/String;");
    /*} else {
        LOGI("fieldID是空的呀");
    }*/

    env->SetStaticObjectField(clazz, f_id, name); // 基本操作

    // f_id = nullptr;

}
static jfieldID f_name1_id = nullptr;
static jfieldID f_name2_id = nullptr;
static jfieldID f_name3_id = nullptr;

extern "C"
JNIEXPORT void JNICALL
Java_top_zcwfeng_learncompose_native_JNIDemo_initialCache(JNIEnv *env, jclass clazz) {
    // 初始化全局静态缓存
    f_name1_id = env->GetStaticFieldID(clazz, "name1", "Ljava/lang/String;");
    f_name2_id = env->GetStaticFieldID(clazz, "name2", "Ljava/lang/String;");
    f_name3_id = env->GetStaticFieldID(clazz, "name3", "Ljava/lang/String;");
}
extern "C"
JNIEXPORT void JNICALL
Java_top_zcwfeng_learncompose_native_JNIDemo_staticCache(JNIEnv *env, jclass clazz, jstring name) {
    // 如果这个方法会反复的被调用，那么不会反复的去获取jfieldID，因为是先初始化静态缓存，然后再执行此函数的
    env->SetStaticObjectField(clazz, f_name1_id, name);
    env->SetStaticObjectField(clazz, f_name2_id, name);
    env->SetStaticObjectField(clazz, f_name3_id, name);
}
extern "C"
JNIEXPORT void JNICALL
Java_top_zcwfeng_learncompose_native_JNIDemo_clearStaticCache(JNIEnv *env, jclass clazz) {
    f_name1_id = nullptr;
    f_name2_id = nullptr;
    f_name3_id = nullptr;
    LOGD("静态缓存清除完毕...");

}

extern "C"
JNIEXPORT void JNICALL
Java_top_zcwfeng_learncompose_native_JNIDemo_exception(JNIEnv *env, jclass clazz) {
    jfieldID f_id = env->GetStaticFieldID(clazz, "name999", "Ljava/lang/String;");

    jthrowable throwable = env->ExceptionOccurred();// 检测本次函数是否有异常

    if (throwable) {
        LOGD("检测到代码异常native层")
        // clear 异常
        env->ExceptionClear();
        f_id = env->GetStaticFieldID(clazz, "name1", "Ljava/lang/String;");
    }

}
extern "C"
JNIEXPORT void JNICALL
Java_top_zcwfeng_learncompose_native_JNIDemo_exception2(JNIEnv *env, jclass clazz) {
    jfieldID f_id = env->GetStaticFieldID(clazz, "name222", "Ljava/lang/String;");

    jthrowable throwable = env->ExceptionOccurred();// 检测本次函数是否有异常

    if (throwable) {
        LOGD("检测到代码异常native层")
        // clear 异常
        env->ExceptionClear();

        jclass no_such_clz = env->FindClass("java/lang/NoSuchFieldException");
        env->ThrowNew(no_such_clz, "native 层NoSuchMethodException，找不到name222，crash！！！");
    }


}

extern "C"
JNIEXPORT jlong JNICALL
Java_top_zcwfeng_learncompose_native_ZParcel_nativeCreate(JNIEnv *env, jobject thiz) {
    ZParcel *parcel = new ZParcel();
    return reinterpret_cast<jlong>(parcel);
}
extern "C"
JNIEXPORT void JNICALL
Java_top_zcwfeng_learncompose_native_ZParcel_nativeWriteInt(JNIEnv *env, jobject thiz,
                                                            jlong native_ptr, jint value) {
    ZParcel *parcel = reinterpret_cast<ZParcel *>(native_ptr);
    parcel->writeInt(value);

}
extern "C"
JNIEXPORT void JNICALL
Java_top_zcwfeng_learncompose_native_ZParcel_nativeSetDataPosition(JNIEnv *env, jobject thiz,
                                                                   jlong native_ptr, jint pos) {
    ZParcel *parcel = reinterpret_cast<ZParcel *>(native_ptr);
    parcel->setDataPosition(pos);
}
extern "C"
JNIEXPORT jint JNICALL
Java_top_zcwfeng_learncompose_native_ZParcel_nativeReadInt(JNIEnv *env, jobject thiz,
                                                           jlong native_ptr) {
    ZParcel *parcel = reinterpret_cast<ZParcel *>(native_ptr);
    return parcel->readInt();

}