#include <jni.h>
#include <string>
#include "native-lib.h"


/**
 *  这里的方法只是用来表示一些方法的使用和数据的操作，但这些操作并没有实际的应用意义。
 */
void setCStudentData(CStudent *pStudent);

extern "C"
JNIEXPORT jstring JNICALL
Java_com_ndk_jniproject_MainActivity_callBaseData(JNIEnv *env, jobject instance,
                                                  jstring str_,
                                                  jint num) {

    //传入的基本数据类型可以直接使用，因为jint 是在jni.h文件中定义好了的
    //而string类型在native层使用的时候需要转换车char* ，然后返回的时候要转成jstring类型
    const char *str = env->GetStringUTFChars(str_, NULL);

    env->ReleaseStringUTFChars(str_, str);

    return env->NewStringUTF("string");
}



extern "C"
JNIEXPORT jintArray JNICALL
Java_com_ndk_jniproject_MainActivity_callInteger(JNIEnv *env, jobject instance,
                                                 jintArray arr_) {
    //传入基本数据类型数组，获取设置传入数组中的数据，创建新数组返回

    // 获取到指针后通过循环能够获取里面的值
    jint *arr = env->GetIntArrayElements(arr_, NULL);
    jint size = env->GetArrayLength(arr_);
    int sum;
    for (int i = 0; i < size; i++) {
        sum += arr[i];// 获取值
        arr[i] = sum; // 将值赋给数组，这种方式能够直接修改这个数组
    }
    //使用完后最后释放掉引用。
    env->ReleaseIntArrayElements(arr_, arr, 0);

    //第二种方式直接复制整个数组
    int array[size];
    env->GetIntArrayRegion(arr_, 0, size, array);
    //将数据都复制到了array中
    for (int x = 0; x < size; x++) {
        sum += array[x];
        array[x] = sum; //因为复制了一份数据在native中，只会修改本地的数据，java层中的不会修改
    }

    //创建一个新的数组，设置数据，返回给java层
    jintArray newarr = env->NewIntArray(size);
    env->SetIntArrayRegion(newarr, 0, size, array);
//    return newarr;  数据设置完后就能直接返回给java层

//    第三种方式数据传递 创建一块共享内存,注意传过来的是一个object对象
//   java层代码： ByteBuffer byteBuffer = ByteBuffer.allocateDirect(100);
    int *pbuf = (int *) env->GetDirectBufferAddress(instance);
    if (pbuf == NULL) {
        printf("GetDirectBufferAddress failed");
        return 0;
    }
    for (int i = 0; i < size; i++) {
        sum += pbuf[i];
        pbuf[i] = sum;
    }

    return newarr;
}

//传入对象数组数据，获取设置传入数组中的数据，创建新数组返回
//二维数组，string数组，对象数组都是类似的
extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_ndk_jniproject_MainActivity_callStudent(JNIEnv *env, jobject instance,
                                                 jobjectArray students) {

    //先获取到数组中的对象
    jclass clzz = env->FindClass("project/ndk/com/jniproject/Student");
    jmethodID init = env->GetMethodID(clzz, "<init>", "()V"); // 获取构造方法
    jfieldID name = env->GetFieldID(clzz, "name", "Ljava/lang/String;");
    jfieldID age = env->GetFieldID(clzz, "age", "I");

    //获取数组中的数据
    jint size = env->GetArrayLength(students);
    for (int i = 0; i < size; ++i) {
        //获取数组中的元素，是一个student对象
        jobject student = env->GetObjectArrayElement(students, i);
        if (student == NULL) {
            printf("获取对象失败");
            return 0;
        }
        // 取出对象中的值，并重新赋值
        jstring pname = (jstring) env->GetObjectField(student, name);
        jint page = env->GetIntField(student, age);
        env->SetObjectField(student, name, pname);
        env->SetIntField(student, age, page);
    }


    //设置数据， 并返回数组，
    // 需要在native层中也有一个数据，
    CStudent *cstu = (CStudent *) malloc(10 * sizeof(CStudent));
    //设置native数据
    setCStudentData(cstu);

    //创建对象数组
    jobjectArray newarray = env->NewObjectArray(size, clzz, NULL);
    for (int i = 0; i < 10; ++i) {
        jobject student = env->NewObject(clzz, init);//创建对象
        //获取i所对应的对象
        CStudent *unit = (CStudent *) (&cstu[i]);
        jstring jname = env->NewStringUTF(unit->name);
        env->SetObjectField(student, name, jname);
        env->SetIntField(student, age, cstu[i].age);

        env->SetObjectArrayElement(students, i, student); //用传进来的数组设置数据
        env->SetObjectArrayElement(newarray, i, student);// 重新创建了一个新的数组并设置数据。
        (env)->DeleteLocalRef(student);//设置完数据后进行删除引用
    }
    //垃圾回收
    free(cstu);
    (env)->DeleteLocalRef(clzz);
    cstu = NULL;
    return students;

}

/**
 * 二维数组的传递与返回，数据的获取与设置
 * 二维数组就是数组对象里面存放个数组
 */
extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_ndk_jniproject_MainActivity_calldoubleArray(JNIEnv *env, jobject instance,
                                                     jobjectArray arr) {

    //获取二维数组中数据,也可以设置数据
    for (int i = 0; i < 10; ++i) {
        jintArray array = (jintArray) env->GetObjectArrayElement(arr, i);
        jint *pint = env->GetIntArrayElements(array, false);
        for (int x = 0; x < 10; ++x) {
            pint[x] = 12;
            int num = pint[x];
        }
    }

    //创建一个新的二维数组，然后并返回
    jclass clzz = env->FindClass("[I");
    jobjectArray result = env->NewObjectArray(10, clzz, NULL);
    for (int i = 0; i < 10; ++i) {
        jintArray iarr = env->NewIntArray(10);
        int tmp[10];
        for (int x = 0; x < 10; ++x) {
            tmp[i] = i + x;
        }
        env->SetIntArrayRegion(iarr, 0, 10, tmp);
        env->SetObjectArrayElement(result, i, iarr);
        env->DeleteLocalRef(iarr);
    }
    return result;
}

/**
 * 传递一个字符串数组，获取里面的数据并设置数据
 * 返回一个字符串数组
 */
extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_ndk_jniproject_MainActivity_callStringArray(JNIEnv *env, jobject instance,
                                                     jobjectArray stu) {

    jclass clzz = env->FindClass("Ljava/lang/String;");
    jint size = env->GetArrayLength(stu);
    for (int i = 0; i < size; ++i) {
        jstring str = (jstring) env->GetObjectArrayElement(stu, i);

        //获取数据
        const char *pcha = env->GetStringUTFChars(str, false);
        //设置数据
        env->SetObjectArrayElement(stu, i, env->NewStringUTF("abc"));
    }

    jobjectArray array = env->NewObjectArray(size, clzz, NULL);

    for (int x = 0; x < size; ++x) {
        jstring s = env->NewStringUTF("abc" + x);
        env->SetObjectArrayElement(array, x, s);
    }

    env->DeleteLocalRef(clzz);
    return array;

}

void setCStudentData(CStudent *pStudent) {
    for (int i = 0; i < 10; ++i) {
        pStudent[i].name = "ksd";
        pStudent[i].age = 12;
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ndk_jniproject_MainActivity_test(JNIEnv *env, jobject instance) {

    // TODO

}