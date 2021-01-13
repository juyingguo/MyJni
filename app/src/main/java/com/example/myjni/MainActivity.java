package com.example.myjni;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    private String TAG = "com.example.myjni.MainActivity";
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());

        /** 1. Java 数据传递给 native */
        test1(true,
                (byte) 1,
                ',',/*,
                (short) 3,
                4,
                3.3f,
                2.2d,*/
                "DevYK",/*,
                28,*/
                new int[]{1, 2, 3, 4, 5},
                new String[]{"1", "test", "4"}/*,
                new Person("阳坤"),
                new boolean[]{false, true}*/
        );
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    /**
     * Java 将数据传递到 native 中
     */
    public native void test1(
            boolean b,
            byte b1,
            char c,/*,
            short s,
            long l,
            float f,
            double d,*/
            String name,/*,
            int age,*/
            int[] i,
            String[] strs/*,
            Person person,
            boolean[] bArray*/
    );

    int count = 0;
    public void clickNotSyncThreadTest(View view) {
        for (int i = 0; i < 10; i++) {
            new Thread(new Runnable() {
                @Override
                public void run() {
                    count();
                    nativeCount();
                }
            }).start();
        }
    }
    private void count() {
        synchronized (this) {
            count++;
            Log.d("count() from Java,", "count=" + count);
        }
    }

    public native void nativeCount();
    public native void syncNativeCount();

    public void clickSyncThreadTest(View view) {
        for (int i = 0; i < 10; i++) {
            new Thread(new Runnable() {
                @Override
                public void run() {
                    count();
                    syncNativeCount();
                }
            }).start();
        }
    }

    public void clickStaticLibraryTest(View view) {
        testCmake();
    }
    /**
     * 测试 cmake 构建程序
     */
    public native static void testCmake();
}
