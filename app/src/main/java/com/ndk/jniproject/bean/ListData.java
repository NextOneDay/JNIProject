package com.ndk.jniproject.bean;

import java.util.ArrayList;

/**
 * Created by nextonedaygg on 2018/3/7.
 */

public class ListData {

    String name;
    int num;
    ArrayList<Student> list;

    public ListData(String name, int num, ArrayList<Student> list) {
        this.name = name;
        this.num = num;
        this.list = list;
    }

    public ListData() {
    }

    @Override
    public String toString() {
        return "ListData{" +
                "name='" + name + '\'' +
                ", num=" + num +
                ", list=" + list +
                '}';
    }
}
