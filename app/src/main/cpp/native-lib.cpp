#include <jni.h>
#include <string>
#include "native-lib.h"


/**
 *  这里的方法只是用来表示一些方法的使用和数据的操作，这些操作并没有实际的应用意义。
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
    jclass clzz = env->FindClass("com/ndk/jniproject/bean/Student");
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

//public String code;
//public byte unit;
//public int[] ids;
//public double changeNum;
//public int open;
//public long totle;
//public boolean isDay;
//传递一个复杂对象，并获取里面的数据，创建一个新的对象设置数据后并返回
extern "C"
JNIEXPORT jobject JNICALL
Java_com_ndk_jniproject_MainActivity_callComplex(JNIEnv *env, jobject instance, jobject com) {

    // 当有object对象传入的时候可以用这个方法来获取，当没有的时候需要通过find查找
    jclass clzz = env->GetObjectClass(com);

    //获取对象中的属性
    jfieldID code = env->GetFieldID(clzz,"code","Ljava/lang/String;");
    jfieldID unit = env->GetFieldID(clzz,"unit","B");
    jfieldID changeNum = env->GetFieldID(clzz,"changeNum","D");
    jfieldID open = env->GetFieldID(clzz,"open","I");
    jfieldID totle = env->GetFieldID(clzz,"totle","J");
    jfieldID isDay = env->GetFieldID(clzz,"isDay","Z");

    jfieldID ids  = env->GetFieldID(clzz,"ids","[I");

    //获取属性中的值,获取后的数据，要转成native层识别的，参考上面
    jstring vcode = (jstring) env->GetObjectField(com, code);
    jint vopen = env->GetIntField(clzz,open);
    jbyte vunit = env->GetByteField(com,unit);
    jdouble vchangeNum = env->GetDoubleField(com,changeNum);
    jlong  vtotle = env->GetLongField(com,totle);
    jboolean visday = env->GetBooleanField(com,isDay);
    jintArray vids= (jintArray) env->GetObjectField(com, ids);


//    创建一个新的对象并返回,构造函数有复杂的参数
//    String code, byte unit, int[] ids, double changeNum, int open, long totle, boolean isDay
    jclass clzzs = env->FindClass("com/ndk/jniproject/bean/ComplexObject");
    jmethodID init = env->GetMethodID(clzzs,"<init>","()V");
    jobject obj = env->NewObject(clzzs,init);
    //给属性设置数据

    env->SetIntField(obj,open,1);
    env->SetByteField(obj,unit,1);
    env->SetBooleanField(obj,isDay, false);
    env->SetLongField(obj,totle,23422);
    env->SetDoubleField(obj,changeNum,23.23);
    env->SetObjectField(obj,code,env->NewStringUTF("code"));

    int parr []={12,1,1,2,2,2,22,22,2,8};
    jintArray newarr =env->NewIntArray(10);
    env->SetIntArrayRegion(newarr,0,10,parr);
    env->SetObjectField(obj,ids,newarr);

    //通过构造参数传值
    jmethodID inits = env->GetMethodID(clzzs,"<init>","(Ljava/langString;B[IDIJZ)V");

    //将7个参数传入构造函数中，进行创建新的对象
    jobject newobj = env->NewObject(clzz,inits,env->NewStringUTF("code"),0,newarr,32.23,12,323423, false);
    return newobj;

}

//调用复杂的对象类型，比如集合
//传递一个集合对象，并获取泛型中的数据，创建一个新的对象设置数据后并返回
/**
 * 大概的思路：
 *      获取集合的class 类型，获取需要get 和size 方法的methodid
 *      获取size 方法的值然后进入for循环，获取集合中的元素对象
 *      获取到元素对象，然后就获取对象中的属性值，
 */

extern "C"
JNIEXPORT jobject JNICALL
Java_com_ndk_jniproject_MainActivity_callList(JNIEnv *env, jobject instance, jobject al) {
    //获取集合中的数据
    jclass  clzz = env->GetObjectClass(al);
    jmethodID size = env->GetMethodID(clzz,"size","()I");
    jint vsize = env->CallIntMethod(al,size);

    //list的get方法需要传入index 然后返回泛型对象
    jmethodID get= env->GetMethodID(clzz,"get","(I)Lcom/ndk/jniproject/beanStudent;");

    //获取studnet中的属性值
    jclass stuclzz = env->FindClass("Lcom/ndk/jniproject/beanStudent");
    jmethodID stuinit= env->GetMethodID(stuclzz,"<init>","()V");
    jfieldID name = env->GetFieldID(stuclzz,"name","Ljava/lang/String");
    jfieldID age = env->GetFieldID(stuclzz,"age","I");
    for (int i = 0; i < vsize; ++i) {
        //进入循环中来获取对应的对象
        jobject student =env->CallObjectMethod(al,get,i);

        //通过对象来获取值
        jint vage = env->GetIntField(student,age);
        jstring vname= (jstring) env->GetObjectField(student, name);
    }

    // 创建一个新的对象并设置数据返回

    //根据class 来创建arraylist集合
//    jclass  arraylist = env->FindClass("Ljava/util/ArrayList;");
    jmethodID init =env->GetMethodID(clzz,"<init>","()V");
    jmethodID add= env->GetMethodID(clzz,"add","(com/ndk/jniproject/bean/Student)Z");
    jobject arrayList= env->NewObject(clzz,init);

    //循环添加数据
    for (int x = 0; x < 10; ++x) {
        jobject student= env->NewObject(stuclzz,stuinit);
        env->SetIntField(student,age,20);
        env->SetObjectField(student,name,env->NewStringUTF("skldf"));
        env->CallObjectMethod(clzz,add,student);
    }

    return arrayList;

}

//传递一个嵌套集合对象，集合中的对象中包含着集合，
extern "C"
JNIEXPORT jobject JNICALL
Java_com_ndk_jniproject_MainActivity_callCompleList(JNIEnv *env, jobject instance, jobject list) {




}