package com.ndk.jniproject;


import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.widget.TextView;

import com.ndk.jniproject.bean.ComplexObject;
import com.ndk.jniproject.bean.Student;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);


    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */


    /**
     * 传入基本数据类型，与string类型，并返回string类型
     * @param str
     * @param num
     * @return
     */
    public native String callBaseData(String str ,int num);

    /**
     * 传入基本数据类型数组，并返回一个新的基本数据类型数组
     * @param arr
     * @return
     */
    public native int []  callInteger(int [] arr);

    /**
     * 传入一个对象数组，获取里面的数据，创建一个新的对象数组，设置数据并返回
     * @param students
     * @return
     */
    public native Student[] callStudent(Student [] students);

    /**
     * 传入一个二维数组，获取二维数组中的数据，并创建一个新的二维数组设置数据，并返回。
     * @param arr
     * @return
     */
    public native int [][] calldoubleArray(int [][] arr);

    /**
     * 传入一个字符串数组，获取数组中的字符串，并创建一个新的字符串数组并设置数据，然后返回。
     * @param stu
     * @return
     */
    public native String[] callStringArray(String [] stu);


    /**
     * 传入一个复杂的对象，并获取对象中的数据，然后再创建一个新的复杂对象，并返回
     */
    public native ComplexObject callComplex(ComplexObject com);
}
