//
// Created by Administrator on 2018/3/13.
//

#include "NDKBuild.h"
#include "jni.h"
JNIEXPORT void JNICALL Java_com_ndk_ndkpro_JNIManager_callNativeMethod
(JNIEnv *env, jclass jobj){

    //传入的基本数据类型可以直接使用，因为jint 是在jni.h文件中定义好了的
    //而string类型在native层使用的时候需要转换车char* ，然后返回的时候要转成jstring类型
    const char *str = env->GetStringUTFChars(str_, NULL);

    env->ReleaseStringUTFChars(str_, str);

    jstring str = env->NewStringUTF("string");
}