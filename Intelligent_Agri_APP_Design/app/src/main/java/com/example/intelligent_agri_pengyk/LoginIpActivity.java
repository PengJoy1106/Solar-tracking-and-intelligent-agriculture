package com.example.intelligent_agri_pengyk;

import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import androidx.annotation.Nullable;

import com.example.intelligent_agri_pengyk.entity.myentity;
import com.example.intelligent_agri_pengyk.utill.okhttputils;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;


public class LoginIpActivity extends Activity implements View.OnClickListener {
    EditText editText;
    Button btn;
    okhttputils okhttputils1=new okhttputils();
    String s1;
    SharedPreferences sharedPreferences;
    myentity myentity;
    int airHumidity,airTemperature,soilHumidity,light,co2,soilTemperature;
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.activity_loginip);
        setFinishOnTouchOutside(false);//点击窗口外部 窗口不消失
        editText=findViewById(R.id.login_et01);
        btn=findViewById(R.id.login_btn01);
        btn.setOnClickListener(this);
        sharedPreferences=getSharedPreferences("Ip",MODE_PRIVATE);
        String ip = sharedPreferences.getString("ip", "");
        if (!ip.isEmpty())
        editText.setText(ip+"");
    }

    @Override
    public void onClick(View v) {
        String s = editText.getText().toString();
        if (TextUtils.isEmpty(s)) {
            Toast.makeText(this, "请不要为空！", Toast.LENGTH_SHORT).show();
        }else {
            boolean b = isIp(s);
            if (b) {
                myentity= (com.example.intelligent_agri_pengyk.entity.myentity) getApplication();
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        try {
                            myentity.setIp(editText.getText().toString().trim());
                            s1 = okhttputils1.connectServer("admin",myentity,"getSensor");
                            Log.i("TAG", "onClick: "+s1);
                            JSONObject jsonObject=new JSONObject(s1);
                            airHumidity = jsonObject.getInt("airHumidity");
                            Log.i("TAG", "onClick: "+airHumidity);
                            airTemperature = jsonObject.getInt("airTemperature");
                            Log.i("TAG", "onClick: "+airTemperature);
                            soilTemperature = jsonObject.getInt("soilTemperature");
                            Log.i("TAG", "onClick: "+soilTemperature);
                            co2 = jsonObject.getInt("co2");
                            Log.i("TAG", "onClick: "+co2);
                            soilHumidity = jsonObject.getInt("soilHumidity");
                            Log.i("TAG", "onClick: "+soilHumidity);
                            light = jsonObject.getInt("light");
                            Log.i("TAG", "onClick: "+light);
                            myentity.setAirmoisture(airHumidity);
                            myentity.setAirtemperature(airTemperature);
                            myentity.setSoiltemperature(soilTemperature);
                            myentity.setSoilmoisture(soilHumidity);
                            myentity.setCo2concentration(co2);
                            myentity.setBeam(light);
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                        catch (JSONException e) {
                            e.printStackTrace();
                        }
                    }
                }).start();
                Toast.makeText(this, "欢迎登入！", Toast.LENGTH_SHORT).show();
                startActivity(new Intent(getApplicationContext(),HomeActivity.class));
                SharedPreferences.Editor edit = sharedPreferences.edit();
                edit.putString("ip",s);
                edit.commit();
                finish();
            }else {
                Toast.makeText(this, "请输入正确的IP！", Toast.LENGTH_SHORT).show();
                editText.setText("");
            }
        }
    }
    private boolean isIp(String ip){
        /**
         * 正则表达式  /d表示一个数字字符（0-9）
         *              /d{1，3} 表示1-3位任意数字 （0-999）
         *              matches()匹配正则表达式
         *              ip=hello  ----》  \d{0，3} false
         *                 ip=777   ----->   \d{0,3} true
         */
        boolean matches = ip.matches("\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}");
        String[] split = ip.split("\\.");
        if (matches) {
            if (Integer.parseInt(split[0]) < 256&&Integer.parseInt(split[1])
                    < 256&&Integer.parseInt(split[2]) < 256&&Integer.parseInt(split[3])
                    < 256&&split.length==4) {
                matches=true;
            }else {
                matches=false;
            }
        }

        return matches;
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        WelcomeActivity.welcomeActivity.finish();
    }
}
