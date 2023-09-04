package com.example.intelligent_agri_pengyk.utill;

import android.util.Log;

import com.example.intelligent_agri_pengyk.entity.myentity;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;

import okhttp3.Call;
import okhttp3.FormBody;
import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

public class okhttputils extends OkHttpClient {
    public String getUrl(String ip,String action){
        return "http://"+ip+":8890/type/jason/action/"+action;
    }
    public String connectServer(String value,myentity myentity, String action) throws IOException{
        OkHttpClient client=new OkHttpClient();
        RequestBody body=new FormBody.Builder().add("username",value).build();
        Request request=new Request.Builder().url(getUrl(myentity.getIp(),action)).post(body).build();
        Call call=client.newCall(request);
        Response response=call.execute();
        String data=response.body().string();
        return data;
    }
    public String[] getSensor(myentity myentity) throws Exception {
        String data = connectServer("admin",myentity, "getSensor");
        JSONObject jsonObject = new JSONObject(data);
        String airHumidity = String.valueOf(jsonObject.getInt("airHumidity"));
        String airTemperature = String.valueOf(jsonObject.getInt("airTemperature"));
        String soilTemperature = String.valueOf(jsonObject.getInt("soilTemperature"));
        String co2 = String.valueOf(jsonObject.getInt("co2"));
        String soilHumidity = String.valueOf(jsonObject.getInt("soilHumidity"));
        String light = String.valueOf(jsonObject.getInt("light"));
        String[] dataArr={airHumidity,airTemperature,soilTemperature,co2,soilHumidity,light};
        return dataArr;
    }
    public int[] getContorllerStatus(myentity myentity) throws Exception {
        String data=connectServer("",myentity,"getContorllerStatus");
        JSONObject object=new JSONObject(data);
        int waterPump=object.getInt("WaterPump");
        int blower = object.getInt("Blower");
        int roadlamp = object.getInt("Roadlamp");
        int buzzer = object.getInt("Buzzer");
        int[] dataArr={waterPump,blower,roadlamp,buzzer};
        return dataArr;
    }
    public void control(myentity myentity,int status,String controlName) throws IOException, JSONException {
        String url = getUrl(myentity.getIp(), "control");
        OkHttpClient client =new OkHttpClient();
        JSONObject json=new JSONObject();
        json.put(controlName,status);
        //mediaType: 传输协议（数据类型 json）  arg2 数据
        RequestBody body=RequestBody.create(MediaType.parse("application/json"),String.valueOf(json));
        Request request = new Request.Builder().post(body).url(url).build();
        client.newCall(request).execute();
        Log.e("eee", "run: 3" );
    }
    public int[] getmaxmin(myentity myentity) throws Exception {
        String data = connectServer("",myentity, "getConfig");
        JSONObject jsonObject = new JSONObject(data);

        int maxCo2 = jsonObject.getInt("maxCo2");
        int maxLight = jsonObject.getInt("maxLight");
        int minCo2 = jsonObject.getInt("minCo2");
        int minLight = jsonObject.getInt("minLight");
        int maxSoilHumidity = jsonObject.getInt("maxSoilHumidity");
        int minSoilHumidity = jsonObject.getInt("minSoilHumidity");
        int minAirHumidity = jsonObject.getInt("minAirHumidity");
        int minAirTemperature = jsonObject.getInt("minAirTemperature");
        int maxAirHumidity = jsonObject.getInt("maxAirHumidity");
        int maxAirTemperature = jsonObject.getInt("maxAirTemperature");
        int controlAuto =jsonObject.getInt("controlAuto");
        int maxSoilTemperature =jsonObject.getInt("maxSoilTemperature");
        int minSoilTemperature =jsonObject.getInt("minSoilTemperature");
        int[] dataArr={minCo2,maxCo2,minLight,maxLight,minSoilTemperature,maxSoilTemperature,
                minSoilHumidity,maxSoilHumidity,minAirTemperature,maxAirTemperature,
                minAirHumidity,maxAirHumidity,controlAuto};
        return dataArr;
    }

    public void setConfig(myentity myentity,int status,String ConfigName) throws Exception {
        String url = getUrl(myentity.getIp(), "setConfig");
        OkHttpClient client =new OkHttpClient();
        JSONObject json=new JSONObject();
        json.put(ConfigName,status);
        RequestBody body=RequestBody.create(MediaType.parse("application/json"),String.valueOf(json));
        Request request = new Request.Builder().post(body).url(url).build();
        client.newCall(request).execute();
    }
}
