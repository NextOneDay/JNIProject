APP_STL := stlport_static  # 指定要使用的运行时
APP_CPPFLAGS= -std=gnu++0x         # 在编译时使用的传递到编译器的一个C++编译器标志。

APP_CFLAGS += -Wno-error=format-security \ -DUSE_DUMP        # 在编译时使用的传递到编译器的一个C编译器标志。

APP_ABI := armeabi armeabi-v7a   # 指定的abi