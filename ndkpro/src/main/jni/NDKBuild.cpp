//
// Created by Administrator on 2018/3/13.
//

#include "NDKBuild.h"
#include "jni.h"
#include <string>


/*
 * Class:     com_ndk_ndkpro_JNIManager
 * Method:    callNativeMethod
 * Signature: ()Ljava/lang/String;
 */
extern "C"
JNIEXPORT jstring JNICALL Java_com_ndk_ndkpro_JNIManager_callNativeMethod(JNIEnv *env, jclass obj) {

    jstring str = env->NewStringUTF("string");
    return str;
}

