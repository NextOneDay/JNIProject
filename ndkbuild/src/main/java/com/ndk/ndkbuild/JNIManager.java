package com.ndk.ndkbuild;

/**
 * Created by nextonedaygg on 2018/3/13.
 */

public class JNIManager {
    //这个是通过ndk-build自动编译调用的
    public static native String callNativeString(String str);


    //通过定义宏来达到修改native函数
    public static native String callName(String name);
}
