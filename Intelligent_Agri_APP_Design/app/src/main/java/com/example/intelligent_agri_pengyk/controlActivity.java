package com.example.intelligent_agri_pengyk;

import android.content.Intent;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import com.example.intelligent_agri_pengyk.entity.myentity;
import com.example.intelligent_agri_pengyk.utill.okhttputils;

import java.util.ArrayList;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;

public class controlActivity extends AppCompatActivity implements KeyEvent.Callback, View.OnClickListener {
    TextView tv_back,tv1,tv2,tv3,tv4,tv5,tv6,tv7,tv8,tv_title;
    ImageView img_fengshan,img_guangzhao,img_shui,img_baojing;
    LinearLayout line,line1,line2,line3,line4;
    myentity myentity;
    public static final int OPENBLOWER=100,COLSEBLOWER=101,OPENGUANG=201,COLSEGUANG=202,OPENBAOJING=301,COLSEBAOJING=302,OPENSHUI=401,COLSESHUI=402;

    Handler handler=new Handler(){
        @Override
        public void handleMessage( Message msg) {
            switch (msg.what){
                case -1:
                    handler.removeCallbacksAndMessages(null);
                    break;
                case OPENBLOWER:
                    img_fengshan.setImageResource(R.mipmap.dakaifengshan2);
                    break;
                case COLSEBLOWER:
                    img_fengshan.setImageResource(R.mipmap.dakaifengshan);
                    break;
                case OPENGUANG:
                    img_guangzhao.setImageResource(R.mipmap.dakaiguangzhao2);
                    break;
                case COLSEGUANG:
                    img_guangzhao.setImageResource(R.mipmap.dakaiguangzhao);
                    break;
                case OPENBAOJING:
                    img_baojing.setImageResource(R.mipmap.dakaibaojing2);
                    break;
                case COLSEBAOJING:
                    img_baojing.setImageResource(R.mipmap.dakaibaojing);
                    break;
                case OPENSHUI:
                    img_shui.setImageResource(R.mipmap.dakaishui2);
                    break;
                case COLSESHUI:
                    img_shui.setImageResource(R.mipmap.dakaishui);
                case 1:
                    tv2.setText(myentity.getCo2concentration()+"");
                    tv6.setText(myentity.getCo2min()+"~~"+myentity.getCo2max());
                    handler.sendEmptyMessageDelayed(1,3000);
                break;
                case 2:
                    tv2.setText(myentity.getBeam()+"");
                    tv6.setText(myentity.getBeammin()+"~~"+myentity.getBeammax());
                    handler.sendEmptyMessageDelayed(2,3000);
                    break;
                case 3:
                    tv2.setText(myentity.getSoiltemperature()+"");
                    tv4.setText(myentity.getSoilmoisture()+"");
                    tv6.setText(myentity.getSoiltemperaturemin()+"~~"+myentity.getSoiltemperaturemax());
                    tv8.setText(myentity.getSoilmoisturemin()+"~~"+myentity.getSoilmoisturemax());
                    handler.sendEmptyMessageDelayed(3,3000);
                    break;
                case 4:
                    tv2.setText(myentity.getAirtemperature()+"");
                    tv4.setText(myentity.getAirmoisture()+"");
                    tv6.setText(myentity.getAirtemperaturemin()+"~~"+myentity.getAirtemperaturemax());
                    tv8.setText(myentity.getAirmoisturemin()+"~~"+myentity.getAirmoisturemax());
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
        setContentView(R.layout.activity_control);
        init();
        layout();
    }
    private void init(){
        myentity= (com.example.intelligent_agri_pengyk.entity.myentity) getApplication();
        tv_back=findViewById(R.id.control_tv_back);
        tv_title=findViewById(R.id.control_tv_title);
        tv1=findViewById(R.id.control_tv_line1_tv1);
        tv2=findViewById(R.id.control_tv_line1_tv2);
        tv3=findViewById(R.id.control_tv_line2_tv3);
        tv4=findViewById(R.id.control_tv_line2_tv4);
        tv5=findViewById(R.id.control_tv_line3_tv5);
        tv6=findViewById(R.id.control_tv_line3_tv6);
        tv7=findViewById(R.id.control_tv_line4_tv7);
        tv8=findViewById(R.id.control_tv_line4_tv8);
        img_fengshan=findViewById(R.id.btn_fengshan);
        img_guangzhao=findViewById(R.id.btn_guangzhao);
        img_shui=findViewById(R.id.btn_shuibeng);
        img_baojing=findViewById(R.id.btn_baojing);
        line=findViewById(R.id.control_line);
        line1=findViewById(R.id.control_tv_line1);
        line2=findViewById(R.id.control_tv_line2);
        line3=findViewById(R.id.control_tv_line3);
        line4=findViewById(R.id.control_tv_line4);
        img_fengshan.setOnClickListener(this);
        img_baojing.setOnClickListener(this);
        img_shui.setOnClickListener(this);
        img_guangzhao.setOnClickListener(this);
        tv_back.setOnClickListener(this);
        Timer timer=new Timer();
        final okhttputils okhttputils1=new okhttputils();
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
    private void layout(){
        int positon = getIntent().getIntExtra("position", 999);
        Drawable drawable;
        switch (positon){
            case 1:
                tv_title.setText(R.string.item1_a);
                drawable=getApplicationContext().getResources().getDrawable(R.mipmap.co2beijng);
                line.setBackground(drawable);
                line1.setVisibility(View.VISIBLE);
                line3.setVisibility(View.VISIBLE);
                tv1.setText(R.string.item1_1);
                tv5.setText(R.string.item1_5);
//                tv2.setText(myentity.getCo2concentration()+"");
//                tv6.setText(myentity.getCo2min()+"~~"+myentity.getCo2max());
                handler.sendEmptyMessage(1);
                img_fengshan.setVisibility(View.VISIBLE);
                img_baojing.setVisibility(View.VISIBLE);
                break;
            case  2:
                tv_title.setText("光照详情");
                drawable=getApplicationContext().getResources().getDrawable(R.mipmap.guangzhaobeijing);
                line.setBackground(drawable);
                line1.setVisibility(View.VISIBLE);
                line3.setVisibility(View.VISIBLE);
                tv1.setText(R.string.item2_0);
                tv5.setText(R.string.item2_1);
//                tv2.setText(myentity.getBeam()+"");
//                tv6.setText(myentity.getBeammin()+"~~"+myentity.getBeammax());
                handler.sendEmptyMessage(2);
                img_guangzhao.setVisibility(View.VISIBLE);
                img_baojing.setVisibility(View.VISIBLE);
                break;
            case 3:
                tv_title.setText("土壤详情");
                drawable=getApplicationContext().getResources().getDrawable(R.mipmap.turangbeijing);
                line.setBackground(drawable);
                line1.setVisibility(View.VISIBLE);
                line2.setVisibility(View.VISIBLE);
                line3.setVisibility(View.VISIBLE);
                line4.setVisibility(View.VISIBLE);
                tv1.setText(R.string.item8_a0);
                tv3.setText(R.string.item8_b0);
                tv5.setText(R.string.item3_2);
                tv7.setText(R.string.item4_2);
//                tv2.setText(myentity.getSoiltemperature()+"");
//                tv4.setText(myentity.getSoilmoisture()+"");
//                tv6.setText(myentity.getSoiltemperaturemin()+"~~"+myentity.getSoiltemperaturemax());
//                tv8.setText(myentity.getSoilmoisturemin()+"~~"+myentity.getSoilmoisturemax());
                handler.sendEmptyMessage(3);
                img_guangzhao.setVisibility(View.VISIBLE);
                img_shui.setVisibility(View.VISIBLE);
                img_baojing.setVisibility(View.VISIBLE);
                break;
            case 4:
                drawable=getApplicationContext().getResources().getDrawable(R.mipmap.kongqibeijing);
                line.setBackground(drawable);
                line1.setVisibility(View.VISIBLE);
                line2.setVisibility(View.VISIBLE);
                line3.setVisibility(View.VISIBLE);
                line4.setVisibility(View.VISIBLE);
                img_fengshan.setVisibility(View.VISIBLE);
                img_guangzhao.setVisibility(View.VISIBLE);
                img_shui.setVisibility(View.VISIBLE);
                img_baojing.setVisibility(View.VISIBLE);
//                tv2.setText(myentity.getAirtemperature()+"");
//                tv4.setText(myentity.getAirmoisture()+"");
//                tv6.setText(myentity.getAirtemperaturemin()+"~~"+myentity.getAirtemperaturemax());
//                tv8.setText(myentity.getAirmoisturemin()+"~~"+myentity.getAirmoisturemax());
                handler.sendEmptyMessage(4);
                break;
        }
    }
    @Override
    public boolean dispatchKeyEvent(KeyEvent event) {
        if(event.getKeyCode() == KeyEvent.KEYCODE_BACK ) {
            return true;
        }else {
            return super.dispatchKeyEvent(event);
        }
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.control_tv_back:
                handler.sendEmptyMessage(-1);
                handler.removeCallbacksAndMessages(null);
                Intent intent=new Intent(getApplicationContext(),HomeActivity.class);
                startActivity(intent);
                finish();
                break;
            case R.id.btn_baojing:
                getCtrlStatus("baojing");
                break;
            case R.id.btn_fengshan:
                getCtrlStatus("fengshan");
                break;
            case R.id.btn_guangzhao:
                getCtrlStatus("guangzhao");
                break;
            case R.id.btn_shuibeng:
                getCtrlStatus("shuibeng");
                break;
        }
    }

    private void getCtrlStatus(final String type){
        final okhttputils okhttputils = new okhttputils();
        Thread thread=new Thread() {
            @Override
            public void run() {
                Message msg = new Message();
                try{
                    int[] contorllerStatus = okhttputils.getContorllerStatus(myentity);
                    switch (type){
                        case "fengshan":
                            if (contorllerStatus[1] == 0) {
                                okhttputils.control(myentity, 1,"Blower");
                                msg.what=OPENBLOWER;
                                handler.sendMessage(msg);
                            } else {
                                okhttputils.control(myentity, 0,"Blower");
                                msg.what=COLSEBLOWER;
                                handler.sendMessage(msg);
                            }
                            break;
                        case "guangzhao":
                            Log.e("TAGa", "run: "+type );
                            if (contorllerStatus[2] == 0) {
                                okhttputils.control(myentity, 1,"Roadlamp");
                                msg.what=OPENGUANG;
                                handler.sendMessage(msg);
                            } else {
                                okhttputils.control(myentity, 0,"Roadlamp");
                                msg.what=COLSEGUANG;
                                handler.sendMessage(msg);
                            }
                            break;
                        case "baojing":
                            if (contorllerStatus[3] == 0) {
                                okhttputils.control(myentity, 1,"Buzzer");
                                msg.what=OPENBAOJING;
                                handler.sendMessage(msg);
                            } else {
                                okhttputils.control(myentity, 0,"Buzzer");
                                msg.what=COLSEBAOJING;
                                handler.sendMessage(msg);
                            }
                            break;
                        case "shuibeng":
                            if (contorllerStatus[0] == 0) {
                                okhttputils.control(myentity, 1,"WaterPump");
                                msg.what=OPENSHUI;
                                handler.sendMessage(msg);
                            } else {
                                okhttputils.control(myentity, 0,"WaterPump");
                                msg.what=COLSESHUI;
                                handler.sendMessage(msg);
                            }
                            break;
                    }
                }catch (Exception e) {
                    e.printStackTrace();
                    Log.e("错误", "run: 错误"+e.toString());
                }
            }
        };
        thread.start();
    }
}
