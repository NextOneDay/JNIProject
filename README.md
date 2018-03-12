# JNIProject
    要想实现调用c或c++代码，需要知道什么是ndk和jni(一)，
    然后要把支持c/c++的打包编译环境配置好了(二)，
    然后开始动手写调用C/C++的方法声明，方法声明编写完成了(三)，
    需要动手写代码了，需要了解怎么转换数据类型和调用什么方法后(四)，
    就能开始编写jni代码了(五)，
    代码编写好了运行调试(六)，
    后期提高需要了解jni的技巧(七)，
    以及NDK库中提供的API(八)。

### 一、NDK简介
    NDK:(本地开发工具集)是google 提供给开发者用来开发的一套工具，包括编译、集成打包，提供一套完整的库等
    JNI:(Java 本地接口)是用来实现Java和Native层之间相互调用的桥梁
    ndk-build:ndk-build脚本用于在NDK中心启动构建脚本
    共享库(so库):将native代码编译成so库
    ABI:不同的cpu有不同的架构，所编译出来的so库也要对应不同的CPU架构指令集
    Android.mk: 用来定义引导ndk-build来编译的步骤、模块、名称等
    Application.mk:描述应用需要的模块，如对应的ABI,工具链等
    Cmake文件:在使用cmake工具来编译时使用到的编译文件
    
### 二、构建项目
    ** 三种集成构建jni的方式 ** 
        ndk自动编译:通过在build.gradle文件中加入一些配置来调用android.mk文件进行编译so库
        ndk手动编译：通过命令行进入存放android.mk文件目录下，使用ndk-build命令进行手动编译，生成so库
        cmake自动编译：在android studio创建新项目的时候进行勾选c++依赖 ，能够自动配置好环境。
### 三、native方法声明创建
    ** 三种方法签名生成方式 **
        javah生成方法签名：对带有native方法的类，进行编译获取class文件，使用javah命令对class文件进行获取对应的头文件，头文件中就是对应的native方法名
        采用android studio 自动创建方法签名:必须使用自动编译方式才能够有使用android studio 的自动提示功能进行创建native方法名
        采用JNI_Load 方式创建方法签名:通过jni提供的方法对native方法进行动态的注册，
##### JNI_OnLoad方式实现native方法声明。     
   
### 四、JNI接口学习
    通过jni.h文件，了解jni的对java的基本数据类型、对象数据类型 ，以及数据类型的签名的规则了解，以及提供了
    进行相互调用、相互转化的方法学习。

### 五、Java层与native层数据类型转换以及互调方法
        基本数据类型、String类型
        一维数组、二维数组、对象数组等数据类型
        复杂对象数据
        集合对象类型
        集合嵌套数据类型
##### native层直接调用java层获取Env 
   
### 六、调试与排错：
        通过android studio能够很方便的对jni、native层代码进行断点调试，日志输出等，以及进行常见错误的排查
   
### 七、JNI技巧
        如果要深入了解，编写更好的jni代码，就需要对jni有更深入的了解
### 八、NDK学习
        想要更深入学习，还可以学习NDK中为我们提供的一些对底层操作的API
        NDK中的重要组成部分就是APIS ,它由四个部分组成，分别是神经网络系统、语音、视频和图像、绘图软件组成。
        在有支持的设备上NN API 为TensorFlow Lite 和其他机器学习框架，提供了硬件加速功能。NN API 提供了大概三十个神经网络的运算单元，可以满足大多数机器学习系统的需求，
        语音方面是Oboe ,Oboe是谷歌开源软件，封装了NDK中的AAudio 和OpenSL ES
        在视频方面的是Camera2 API ,它可以使C/C++ 的程序直接控制摄像头，借助于NDK中HardwareBuffer ,从摄像头中进来的图像，可以直接与图形软件共享。省去了中间复制的环节。
        在图形处理方面，主要有两个新的功能，一个是Vulkan ，一个是宽色域。Vulkan是新一代跨平台的图形API ,在能支持的设备上，vulkan应用软件直接控制GPU。能够并行处理。8.0引进了宽色域运行模式。 
        NDK编译工具提供了编译器比如Clang/LLVM ,no more GCC Unified headers ,还提供了可独立使用工具，如Simpleperf、ndk-build、 shader compilers.
    