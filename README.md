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
    
### 二、构建项目
    ** 三种集成构建jni的方式 ** 
        ndk自动编译
        ndk手动编译
        cmake自动编译
### 三、native方法声明创建
##### 三种方法签名生成方式
   
        javah生成方法签名
        采用android studio 自动创建方法签名
        采用JNI_Load 方式创建方法签名
##### JNI_OnLoad方式实现native方法声明。     
   
### 四、JNI接口学习

### 五、Java层与native层数据类型转换以及互调方法
        基本数据类型、String类型
        一维数组、二维数组、对象数组等数据类型
        复杂对象数据
        集合对象类型
        集合嵌套数据类型
##### native层直接调用java层获取Env 
   
### 六、调试与排错
   
### 七、JNI技巧学习
   
### 八、NDK学习
        
  
    