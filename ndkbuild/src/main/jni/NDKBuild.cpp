//
// Created by Administrator on 2018/3/13.
//

#include "NDKBuild.h"
#include "jni.h"
#include <string>

//通过定义一个包名的宏，通过指定name可以很方便的缩短和替换方法名
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

// 现在只要使用这个宏然后传入方法名就能够调用，效果相当于原先的一长串
//这个写法比使用JNI_OnLoad 更方便，但是如果有比较复杂的需求，使用JNI_OnLoad 会比较好
extern "C" JNIEXPORT jstring  FunctionName(callName)(JNIEnv *env, jclass obj,jstring jstr){

jstring str = env->NewStringUTF("hello 水货");
    return str;
}
