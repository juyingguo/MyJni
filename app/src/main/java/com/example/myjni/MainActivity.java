package com.example.myjni;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
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
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());

        /** 1. Java 数据传递给 native */
        test1(true,
                (byte) 1/*,
                ',',
                (short) 3,
                4,
                3.3f,
                2.2d,
                "DevYK",
                28,
                new int[]{1, 2, 3, 4, 5, 6, 7},
                new String[]{"1", "2", "4"}*//*,
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
            byte b1/*,
            char c,
            short s,
            long l,
            float f,
            double d,
            String name,
            int age,
            int[] i,
            String[] strs*//*,
            Person person,
            boolean[] bArray*/
    );

}