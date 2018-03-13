//
// Created by Administrator on 2018/3/9.
//

#ifndef JNIPROJECT_JNILOADMANAGER_H
#define JNIPROJECT_JNILOADMANAGER_H

static int registerNatives(JNIEnv *pEnv);

JNIEXPORT static int registerNativeMethod(JNIEnv *env, const char *cls, JNINativeMethod *method, int numMethod);
JNIEXPORT void native_callNativeMethod(JNIEnv *env,jobject obj);
static JNINativeMethod methods[]={
        {"callNativeMethod","()V",(void*)native_callNativeMethod},
};


#ifndef _ANDROID_LOG_PRINT_H_
#define _ANDROID_LOG_PRINT_H_

#include <android/log.h>
#define IS_DEBUG

#ifdef IS_DEBUG

#define LOG_TAG ("CUSTOMER_NDK_JNI")
#define LOGV(...) ((void)__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__))
#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG  , LOG_TAG, __VA_ARGS__))

#else

#define LOGV(LOG_TAG, ...) NULL
#endif

#endif

#endif //JNIPROJECT_JNILOADMANAGER_H
