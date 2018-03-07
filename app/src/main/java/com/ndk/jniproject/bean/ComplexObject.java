package com.ndk.jniproject.bean;

import java.util.Arrays;

/**
 * Created by Administrator on 2018/3/7.
 */

public class ComplexObject {

    public String code;
    public byte unit;
    public int[] ids;
    public double changeNum;
    public int open;
    public long totle;
    public boolean isDay;

    public ComplexObject() {
    }

    public ComplexObject(String code, byte unit, int[] ids, double changeNum, int open, long totle, boolean isDay) {
        this.code = code;
        this.unit = unit;
        this.ids = ids;
        this.changeNum = changeNum;
        this.open = open;
        this.totle = totle;
        this.isDay = isDay;
    }

    @Override
    public String toString() {
        return "ComplexObject{" +
                "code='" + code + '\'' +
                ", unit=" + unit +
                ", ids=" + Arrays.toString(ids) +
                ", changeNum=" + changeNum +
                ", open=" + open +
                ", totle=" + totle +
                ", isDay=" + isDay +
                '}';
    }
}
