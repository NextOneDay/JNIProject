//
// Created by Administrator on 2018/3/1.
//

#ifndef JNIPROJECT_NATIVE_LIB_H
#define JNIPROJECT_NATIVE_LIB_H


typedef struct _Student{
    const char* name;
    int age;

}CStudent;

void setCStudentData(CStudent *pStudent) ;
void callJavaMethod();
#endif //JNIPROJECT_NATIVE_LIB_H
