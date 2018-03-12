//
// Created by Administrator on 2018/3/9.
//

#include <jni.h>
#include "JNILoadManager.h"


// 当使用JNI_OnLoad的方式来进行调用的时候怎么编写的代码

//1.当在java代码进行调用System.loadLibrary("xxx.so");的时候，会调用JNI_OnLoad方法，
//2. 一个so库应该只有一个JNI_OnLoad，
//3.使用这种方式能够动态的加载native方法， 指定JNI版本


JNIEXPORT jint JNI_OnLoad(JavaVM* vm , void* reserved){


}



