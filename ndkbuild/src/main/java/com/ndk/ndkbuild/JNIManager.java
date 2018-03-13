package com.ndk.ndkbuild;

/**
 * Created by nextonedaygg on 2018/3/13.
 */

public class JNIManager {
    //这个是通过ndk-build自动编译调用的
    public static native String callNativeString(String str);


}
