//
// Created by Administrator on 2018/3/9.
//

#include <jni.h>
#include <string>
#include "native-lib.h"
#include "JNILoadManager.h"
#include <assert.h>

// 当使用JNI_OnLoad的方式来进行调用的时候怎么编写的代码

//1.当在java代码进行调用System.loadLibrary("xxx.so");的时候，会调用JNI_OnLoad方法，
//2. 一个so库应该只有一个JNI_OnLoad，
//3.使用这种方式能够动态的加载native方法， 指定JNI版本


//最后调到这个方法输出打印
JNIEXPORT void native_callNativeMethod(JNIEnv *env,jobject obj){

    LOGD("native_callNativeMethod");

}




//registerNativeMethods()函数，中进行调用判断这个java类是否为空，不为空调用Env 的注册方法进行注册本地函数。
JNIEXPORT static int registerNativeMethod(JNIEnv *env, const char *cls, JNINativeMethod *method, int numMethod) {

    jclass  clzz;
    clzz=env->FindClass(cls);
    if(clzz==NULL){
        return JNI_FALSE;
    }
    if(env->RegisterNatives(clzz,methods,numMethod )<0){
        return JNI_FALSE;
    }
    return JNI_TRUE;
}


//本地方法注册，查找了声明native方法的java类，并创建了一个native层和java层函数映射关系的数组，最后传入到registerNativeMethod();
JNIEXPORT static int  registerNatives(JNIEnv *env) {

    const char * cls = "com/ndk/jniproject/CallJNIMethodManager";
    registerNativeMethod(env,cls,methods, sizeof(methods)/ sizeof(methods[0]));



    return JNI_TRUE;
}


// 首先通过jvm 来获取env，判断本地方法是否注册成功，最后返回要使用的jni版本

/**
 * 这里有个重要的点就是JNIEnv 和JavaVM 的获取,
 * 在这里能够获取到vm，通过vm来获取env，然后保存为static成员
 * 通过调用crateJavaVM() 来获取jvm，这个一般是不允许的
 * 获取通过在有env的地方来通过env->getJavaVM()获取
 * @param vm
 * @param reserved
 * @return
 */
jint JNI_OnLoad(JavaVM *vm, void *reserved) {

    JNIEnv *env = NULL;
    jint result = -1;

    if(vm->GetEnv((void**)&env,JNI_VERSION_1_6)!=JNI_OK){
        return -1;
    }
    assert(env!=NULL);

    if(!registerNatives(env)){
        return -1;
    }
    result=JNI_VERSION_1_6;
    return result;


}



