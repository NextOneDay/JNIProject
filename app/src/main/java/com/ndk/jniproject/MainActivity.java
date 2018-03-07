package com.ndk.jniproject;


import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.widget.TextView;

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

    public native Student[] callStudent(Student [] students);
    public native int [][] calldoubleArray(int [][] arr);
    public native String[] callStringArray(String [] stu);
    public native void test();
}
