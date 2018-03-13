package com.ndk.ndkpro;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        TextView textView = findViewById(R.id.tv_text);
        String s = JNIManager.callNativeMethod();
        textView.setText(s);
    }

    static {
        System.loadLibrary("ndkpro");
    }


}
