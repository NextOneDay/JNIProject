LOCAL_PATH := $(call my-dir)        #指定本地代码路径 my-dir 指当前路径

include $(CLEAR_VARS)               #清除全局编译变量，除了LOCAL_PATH以外

LOCAL_MODULE    := ndkpro            #指定生成动态库名hello,生成动态库文件名libhello.so
LOCAL_SRC_FILES := NDKBuild.cpp          #指定利用哪些源文件生成动态库
LOCAL_C_INCLUDES :=NDKBuild.h
include $(BUILD_SHARED_LIBRARY)     #指定生成动态库