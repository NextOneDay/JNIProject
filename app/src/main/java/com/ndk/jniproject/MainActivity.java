package com.ndk.jniproject;


import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.TextView;

import com.ndk.jniproject.bean.ComplexObject;
import com.ndk.jniproject.bean.ListData;
import com.ndk.jniproject.bean.Student;

import java.util.ArrayList;
import java.util.Arrays;

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

        callCompleLIstInJava();
//        callStudentInJava();
//        calldoubleArrayInJava();
//        callStringArrayInJava();

//        callComplexInJava();
//        callListInJava();
        CallJNIMethodManager.callNativeMethod(); // 这个是通过JNI_OnLoad加载调用的，


    }

    private void callListInJava() {
        ArrayList<Student> al = new ArrayList<>();
        Student student = new Student();
        student.age = 23;
        student.name = "Sjd";
        al.add(student);
        ArrayList<Student> students = callList(al);
        Log.d("callListInJava:", students.toString());

    }

    private void callComplexInJava() {
        ComplexObject com = new ComplexObject();
        com.changeNum = 22.33;
        com.code = "code";
        com.ids = new int[]{2, 2, 32, 3, 23};
        com.isDay = true;
        com.open = 23;
        com.totle = 32423423;
        com.unit = 0;
        ComplexObject complexObject = callComplex(com);
        Log.d("callComplexInJava:", complexObject.toString());

    }

    private void callStringArrayInJava() {
        String str[] = {"uj", "cx", "fe", "acd"};
        String[] strings = callStringArray(str);
        Log.d("callStringArrayInJava:", Arrays.toString(strings));
    }

    private void calldoubleArrayInJava() {
        int arr[] = {23, 12, 23, 54, 22, 3};
        int doublearr[][] = {arr};

        int[][] ints = calldoubleArray(doublearr);
        Log.d("calldoubleArrayInJava:", Arrays.toString(ints[0]));
    }

    private void callStudentInJava() {
        Student sts = new Student();
        sts.name = "sts";
        sts.age = 1;
        Student stu[] = {sts};
        Student[] students = callStudent(stu);
        Log.d("callStudentInJava:", Arrays.toString(students));
    }

    private void callCompleLIstInJava() {
        ArrayList<ListData> al = new ArrayList<>();
        for (int x = 0; x < 3; x++) {
            ListData data = new ListData();
            data.code = "code";
            data.num = x;
            ArrayList<Student> students = new ArrayList<>();
            for (int y = 0; y < 3; y++) {
                Student stu = new Student();
                stu.age = y + x;
                stu.name = "name" + y;
                students.add(stu);
            }
            data.list = students;
            al.add(data);
        }

        ArrayList<ListData> listData = callCompleList(al);
        Log.d("callCompleListInJava:", listData.toString());
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */


    /**
     * 传入基本数据类型，与string类型，并返回string类型
     *
     * @param str
     * @param num
     * @return
     */
    public native String callBaseData(String str, int num);

    /**
     * 传入基本数据类型数组，并返回一个新的基本数据类型数组
     *
     * @param arr
     * @return
     */
    public native int[] callInteger(int[] arr);

    /**
     * 传入一个对象数组，获取里面的数据，创建一个新的对象数组，设置数据并返回
     *
     * @param students
     * @return
     */
    public native Student[] callStudent(Student[] students);

    /**
     * 传入一个二维数组，获取二维数组中的数据，并创建一个新的二维数组设置数据，并返回。
     *
     * @param arr
     * @return
     */
    public native int[][] calldoubleArray(int[][] arr);

    /**
     * 传入一个字符串数组，获取数组中的字符串，并创建一个新的字符串数组并设置数据，然后返回。
     *
     * @param stu
     * @return
     */
    public native String[] callStringArray(String[] stu);


    /**
     * 传入一个复杂的对象，并获取对象中的数据，然后再创建一个新的复杂对象，并返回
     */
    public native ComplexObject callComplex(ComplexObject com);

    /**
     * 复杂的数据类型集合类型的数据传递与返回，
     * 其实与之跟对象集合以及复杂对象的相结合
     * 数组就是一个复杂对象，在对象中又存在一个比较复杂的对象，这个对象中可能会也会有集合等数据类型
     */
    public native ArrayList<Student> callList(ArrayList<Student> al);

    /**
     * 复杂的数据传递，多层嵌套集合
     * ArrayList<ListData>:集合中存放的是listdata对象
     * --ListData 对象中有多个属性，其中有个string类型，数组类型，也有一个list类型
     * -- 对象中这个集合中的泛型是一个简单的对象类型，student
     */

    public native ArrayList<ListData> callCompleList(ArrayList<ListData> list);


    /**
     * 单纯的从native层调用的方法
     */
    public void callForNative(Student student) {

        Log.d("callForNative:", student.toString());
    }
}
