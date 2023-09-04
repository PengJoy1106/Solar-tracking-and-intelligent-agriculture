package com.example.intelligent_agri_pengyk;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class manualActivity extends AppCompatActivity implements KeyEvent.Callback, View.OnClickListener {
    TextView tv_back;
    Button btn1,btn2,btn3,btn4;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_manual);
        init();
    }
    void init(){
        tv_back=findViewById(R.id.manual_tv_back);
        btn1=findViewById(R.id.manual_btn1);
        btn2=findViewById(R.id.manual_btn2);
        btn3=findViewById(R.id.manual_btn3);
        btn4=findViewById(R.id.manual_btn4);
        btn1.setOnClickListener(this);
        btn2.setOnClickListener(this);
        btn3.setOnClickListener(this);
        btn4.setOnClickListener(this);
        tv_back.setOnClickListener(this);
    }
    @Override
    public boolean dispatchKeyEvent(KeyEvent event) {
        if (event.getKeyCode()==KeyEvent.KEYCODE_BACK){
            return true;
        }else {
            return super.dispatchKeyEvent(event);
        }
    }

    @Override
    public void onClick(View v) {
        Intent intent=new Intent();
        intent.setClass(getApplicationContext(),thresholdActivity.class);
        switch (v.getId()){
            case R.id.manual_tv_back:
                finish();
                break;
            case R.id.manual_btn1:
                intent.putExtra("position",0);
                break;
            case R.id.manual_btn2:
                intent.putExtra("position",1);
                break;
            case R.id.manual_btn3:
                intent.putExtra("position",2);
                break;
            case R.id.manual_btn4:
                intent.putExtra("position",3);
                break;
        }
        if (v.getId() != R.id.manual_tv_back) {
            startActivity(intent);
        }

    }
}
