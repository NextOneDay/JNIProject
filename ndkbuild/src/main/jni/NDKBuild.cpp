//
// Created by Administrator on 2018/3/13.
//

#include "NDKBuild.h"
#include "jni.h"
#include <string>

#define FunctionName(name) Java_com_ndk_ndkbuild_JNIManager_##name
/*
 * Class:     com_ndk_ndkpro_JNIManager
 * Method:    callNativeMethod
 * Signature: ()Ljava/lang/String;
 */
extern "C"
JNIEXPORT jstring JNICALL Java_com_ndk_ndkbuild_JNIManager_callNativeString(JNIEnv *env, jclass obj,jstring jstr) {

    jstring str = env->NewStringUTF("hello java");
    return str;
}

extern "C" JNIEXPORT jstring  FunctionName(callName)(JNIEnv *env, jclass obj,jstring jstr){

jstring str = env->NewStringUTF("hello 水货");
    return str;
}
