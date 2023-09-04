package com.example.intelligent_agri_pengyk;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.ImageView;

import java.util.Timer;
import java.util.TimerTask;

public class WelcomeActivity extends AppCompatActivity {
    ImageView imageView;
    static WelcomeActivity welcomeActivity;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_welcome);
        welcomeActivity=this;
        imageView=findViewById(R.id.Welcome_img01);
        //获取定时器
        Timer timer=new Timer();
        //创建一个定时器任务栈 默认运行在子线程中
        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                alertIp();
            }
        },3000);
        Animation animation = AnimationUtils.loadAnimation(getApplicationContext(), R.anim.alphaanimation);
        animation.setFillAfter(true);
        imageView.startAnimation(animation);
    }
    private void alertIp(){
        Intent intent=new Intent(getApplicationContext(), LoginIpActivity.class);
        startActivity(intent);
    }
    @Override
    protected void onStop() {
        super.onStop();
//        finish();
    }
}
