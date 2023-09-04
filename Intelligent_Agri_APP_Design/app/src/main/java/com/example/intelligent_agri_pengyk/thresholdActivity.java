package com.example.intelligent_agri_pengyk;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.KeyEvent;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import com.example.intelligent_agri_pengyk.entity.myentity;
import com.example.intelligent_agri_pengyk.utill.okhttputils;

import java.util.ArrayList;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;

public class thresholdActivity extends AppCompatActivity implements KeyEvent.Callback {
    TextView tv1,tv2,tv3,tv4,tv5,tv6,tv7,tv8,tv9,tv10,tv11,tv12,tv_back;
    EditText et1,et2,et3,et4;
    Button btnl;
    LinearLayout line1,line2;
    myentity myentity;
    okhttputils okhttputils1;
    Handler handler=new Handler(){
        @Override
        public void handleMessage(@NonNull Message msg) {
            super.handleMessage(msg);
            switch (msg.what){
                case 1:
                    tv2.setText(myentity.getCo2concentration()+"");
                    if (myentity.getCo2concentration()<=myentity.getCo2max()&&myentity.getCo2concentration()>=myentity.getCo2min()){
                        tv5.setBackgroundResource(R.mipmap.p1);
                    }else if (myentity.getCo2concentration()>myentity.getCo2max()){
                        tv5.setBackgroundResource(R.mipmap.p3);
                    } else if (myentity.getCo2concentration() < myentity.getCo2min()) {
                        tv5.setBackgroundResource(R.mipmap.p1);
                    }
                    handler.sendEmptyMessageDelayed(1,3000);
                    break;
                case 2:
                    if (myentity.getBeam()<=myentity.getBeammax()&&myentity.getBeam()>=myentity.getBeammin()){
                        tv5.setBackgroundResource(R.mipmap.p1);
                    }else if (myentity.getBeam()>myentity.getBeammax()){
                        tv5.setBackgroundResource(R.mipmap.p3);
                    } else if (myentity.getBeam() < myentity.getBeammin()) {
                        tv5.setBackgroundResource(R.mipmap.p1);
                    }
                    tv2.setText(myentity.getBeam()+"");
                    handler.sendEmptyMessageDelayed(2,3000);
                    break;
                case 3:
                    if (myentity.getAirtemperature()<=myentity.getAirtemperaturemax()&&myentity.getAirtemperature()>=myentity.getAirtemperaturemin()){
                        tv5.setBackgroundResource(R.mipmap.p1);
                    }else if (myentity.getAirtemperature()>myentity.getAirtemperaturemax()){
                        tv5.setBackgroundResource(R.mipmap.p3);
                    } else if (myentity.getAirtemperature() < myentity.getAirtemperaturemin()) {
                        tv5.setBackgroundResource(R.mipmap.p1);
                    }
                    if (myentity.getAirmoisture()<=myentity.getAirmoisturemax()&&myentity.getAirmoisture()>=myentity.getAirmoisturemin()){
                        tv11.setBackgroundResource(R.mipmap.p1);
                    }else if (myentity.getAirmoisture()>myentity.getAirmoisturemax()){
                        tv11.setBackgroundResource(R.mipmap.p3);
                    } else if (myentity.getAirmoisture() < myentity.getAirmoisturemin()) {
                        tv11.setBackgroundResource(R.mipmap.p1);
                    }
                    tv2.setText(myentity.getAirtemperature()+"");
                    tv8.setText(myentity.getAirmoisture()+"");
                    handler.sendEmptyMessageDelayed(3,3000);
                    break;
                case 4:
                    if (myentity.getSoiltemperature()<=myentity.getSoiltemperaturemax()&&myentity.getSoiltemperature()>=myentity.getSoiltemperaturemin()){
                        tv5.setBackgroundResource(R.mipmap.p1);
                    }else if (myentity.getSoiltemperature()>myentity.getSoiltemperaturemax()){
                        tv5.setBackgroundResource(R.mipmap.p3);
                    } else if (myentity.getSoiltemperature() < myentity.getSoiltemperaturemin()) {
                        tv5.setBackgroundResource(R.mipmap.p1);
                    }
                    if (myentity.getSoilmoisture()<=myentity.getSoilmoisturemax()&&myentity.getSoilmoisture()>=myentity.getSoilmoisturemin()){
                        tv11.setBackgroundResource(R.mipmap.p1);
                    }else if (myentity.getSoilmoisture()>myentity.getSoilmoisturemax()){
                        tv11.setBackgroundResource(R.mipmap.p3);
                    } else if (myentity.getSoilmoisture() < myentity.getSoilmoisturemin()) {
                        tv11.setBackgroundResource(R.mipmap.p1);
                    }
                    tv2.setText(myentity.getSoiltemperature()+"");
                    tv8.setText(myentity.getSoilmoisture()+"");
                    handler.sendEmptyMessageDelayed(4,3000);
                    break;
                case 1000:
                    List<Object> obj = (List<Object>) msg.obj;
                    String[] data= (String[])obj.get(0);
                    myentity.setAirmoisture(Integer.parseInt(data[0]));
                    myentity.setAirtemperature(Integer.parseInt(data[1]));
                    myentity.setSoiltemperature(Integer.parseInt(data[2]));
                    myentity.setCo2concentration(Integer.parseInt(data[3]));
                    myentity.setSoilmoisture(Integer.parseInt(data[4]));
                    myentity.setBeam(Integer.parseInt(data[5]));
                    int[] datamaxmin= (int[]) obj.get(1);
                    myentity.setCo2min(datamaxmin[0]);
                    myentity.setCo2max(datamaxmin[1]);
                    myentity.setBeammin(datamaxmin[2]);
                    myentity.setBeammax(datamaxmin[3]);
                    myentity.setSoiltemperaturemin(datamaxmin[4]);
                    myentity.setSoiltemperaturemax(datamaxmin[5]);
                    myentity.setSoilmoisturemin(datamaxmin[6]);
                    myentity.setSoilmoisturemax(datamaxmin[7]);
                    myentity.setAirtemperaturemin(datamaxmin[8]);
                    myentity.setAirtemperaturemax(datamaxmin[9]);
                    myentity.setAirmoisturemin(datamaxmin[10]);
                    myentity.setAirmoisturemax(datamaxmin[11]);

                    break;
            }
        }
    };
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_threshold);
        init();
        getjson();
    }
    void getjson(){
        Timer timer=new Timer();
        okhttputils1=new okhttputils();
        TimerTask timerTask=new TimerTask() {
            @Override
            public void run() {
                try {
                    String[] sensor = okhttputils1.getSensor(myentity);
                    int[] getmaxmin = okhttputils1.getmaxmin(myentity);
                    List<Object> obj=new ArrayList<>();
                    obj.add(sensor);
                    obj.add(getmaxmin);
                    Message msg=new Message();
                    msg.obj=obj;
                    msg.what=1000;
                    handler.sendMessage(msg);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        };
        timer.schedule(timerTask,0,3000);
    }
    void init(){
        myentity=(myentity)getApplication();
        tv_back=findViewById(R.id.threshold_tv_back);
        line1=findViewById(R.id.threshold_line1);
        line2=findViewById(R.id.threshold_line2);
        tv1=findViewById(R.id.threshold_tv_1);
        tv2=findViewById(R.id.threshold_tv_2);
        tv3=findViewById(R.id.threshold_tv_3);
        tv4=findViewById(R.id.threshold_tv_4);
        tv5=findViewById(R.id.threshold_tv_5);
        tv6=findViewById(R.id.threshold_tv_6);
        tv7=findViewById(R.id.threshold_tv_7);
        tv8=findViewById(R.id.threshold_tv_8);
        tv9=findViewById(R.id.threshold_tv_9);
        tv10=findViewById(R.id.threshold_tv_10);
        tv11=findViewById(R.id.threshold_tv_11);
        tv12=findViewById(R.id.threshold_tv_12);
        et1=findViewById(R.id.threshold_et_1);
        et2=findViewById(R.id.threshold_et_2);
        et3=findViewById(R.id.threshold_et_3);
        et4=findViewById(R.id.threshold_et_4);
        btnl=findViewById(R.id.threshold_btn);
        back();
        confirm();
        layout();
    }
    void back(){
        tv_back.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                finish();
            }
        });
    }
    void confirm(){
        btnl.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                finish();
            }
        });
    }
    void layout(){
        int position = getIntent().getIntExtra("position", 999);
        final okhttputils okhttputils1=new okhttputils();
        switch (position){
            case 0:
                et1.setText(myentity.getCo2min()+"");
                et2.setText(myentity.getCo2max()+"");
                line2.setVisibility(View.GONE);
                tv1.setText("CO2浓度值：");
                tv4.setText("CO2浓度当前状态：");
                btnl.setOnClickListener(new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        new Thread(new Runnable() {
                            @Override
                            public void run() {
                                try {
                                    okhttputils1.setConfig(myentity,Integer.parseInt(et1.getText().toString()),"minCo2");
                                    okhttputils1.setConfig(myentity,Integer.parseInt(et2.getText().toString()),"maxCo2");
                                } catch (Exception e) {
                                    e.printStackTrace();
                                }
                            }
                        }).start();
                        finish();
                    }
                });
                handler.sendEmptyMessage(1);
                break;
            case 1:
                et1.setText(""+myentity.getBeammin());
                et2.setText(""+myentity.getBeammax());
                line2.setVisibility(View.GONE);
                tv1.setText("光照强度值：");
                tv4.setText("光照强度当前状态：");
                btnl.setOnClickListener(new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        new Thread(new Runnable() {
                            @Override
                            public void run() {
                                try {
                                    okhttputils1.setConfig(myentity,Integer.parseInt(et1.getText().toString()),"minLight");
                                    okhttputils1.setConfig(myentity,Integer.parseInt(et2.getText().toString()),"maxLight");
                                } catch (Exception e) {
                                    e.printStackTrace();
                                }
                            }
                        }).start();
                        finish();
                    }
                });
                handler.sendEmptyMessage(2);
                break;
            case 2:
                et1.setText(myentity.getAirtemperaturemin()+"");
                et2.setText(myentity.getAirtemperaturemax()+"");
                et3.setText(myentity.getAirmoisturemin()+"");
                et4.setText(myentity.getAirmoisturemax()+"");
                tv1.setText("空气温度值：");
                tv4.setText("空气温度当前状态：");
                tv7.setText("空气湿度值：");
                tv10.setText("空气湿度当前状态：");
                btnl.setOnClickListener(new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        new Thread(new Runnable() {
                            @Override
                            public void run() {
                                try {
                                    okhttputils1.setConfig(myentity,Integer.parseInt(et1.getText().toString().trim()),"minAirTemperature");
                                    okhttputils1.setConfig(myentity,Integer.parseInt(et2.getText().toString().trim()),"maxAirTemperature");
                                    okhttputils1.setConfig(myentity,Integer.parseInt(et3.getText().toString().trim()),"minAirHumidity");
                                    okhttputils1.setConfig(myentity,Integer.parseInt(et4.getText().toString().trim()),"maxAirHumidity");
                                } catch (Exception e) {
                                    e.printStackTrace();
                                }
                            }
                        }).start();
                        finish();
                    }
                });
                handler.sendEmptyMessage(3);
                break;
            case 3:
                et1.setText(myentity.getSoiltemperaturemin()+"");
                et2.setText(myentity.getSoiltemperaturemax()+"");
                et3.setText(myentity.getSoilmoisturemin()+"");
                et4.setText(myentity.getSoilmoisturemax()+"");
                btnl.setOnClickListener(new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        new Thread(new Runnable() {
                            @Override
                            public void run() {
                                try {
                                    okhttputils1.setConfig(myentity,Integer.parseInt(et1.getText().toString().trim()),"minSoilTemperature");
                                    okhttputils1.setConfig(myentity,Integer.parseInt(et2.getText().toString().trim()),"maxSoilTemperature");
                                    okhttputils1.setConfig(myentity,Integer.parseInt(et3.getText().toString().trim()),"minSoilHumidity");
                                    okhttputils1.setConfig(myentity,Integer.parseInt(et4.getText().toString().trim()),"maxSoilHumidity");
                                } catch (Exception e) {
                                    e.printStackTrace();
                                }

                            }
                        }).start();
                        finish();
                    }
                });
                handler.sendEmptyMessage(4);
                break;
        }
    }
    @Override
    public boolean dispatchKeyEvent(KeyEvent event) {
        if (event.getKeyCode() == KeyEvent.KEYCODE_BACK) {
            return true;
        }else {
            return super.dispatchKeyEvent(event);
        }
    }
}
