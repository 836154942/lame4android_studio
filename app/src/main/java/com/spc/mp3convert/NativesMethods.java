package com.spc.mp3convert;

/**
 * Created by spc on 16-8-3.
 */
public class NativesMethods {


    static {
        System.loadLibrary("convert");

    }

    //传递源文件和目标文件路径
    public static native void read(String sourcePath, String CoventPath);

    //获取版本号
    public static native String getLameVersion();




}
