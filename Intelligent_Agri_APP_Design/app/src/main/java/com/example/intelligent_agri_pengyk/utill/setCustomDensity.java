package com.example.intelligent_agri_pengyk.utill;

import android.app.Activity;
import android.app.Application;
import android.content.ComponentCallbacks;
import android.content.res.Configuration;
import android.util.DisplayMetrics;

import androidx.annotation.NonNull;

public class setCustomDensity {
    private static float sNoncompatDensity;//每平方英寸像素点数
    private static float sNoncompatScaledDensity;//字体缩放因子
    private static Application application;

    public static void setCustomDensity(Activity activity,int width,int height,double size){
        application=activity.getApplication();
        DisplayMetrics appdisplayMetrics=application.getResources().getDisplayMetrics();
        //获取当前手机density  文字scalldensity
        if (sNoncompatDensity == 0) {
            sNoncompatDensity=appdisplayMetrics.density;
            sNoncompatScaledDensity=appdisplayMetrics.scaledDensity;

            application.registerComponentCallbacks(new ComponentCallbacks() {
                @Override
                public void onConfigurationChanged(@NonNull Configuration newConfig) {
                    if (newConfig!=null&&newConfig.fontScale>0){
                        sNoncompatScaledDensity=application.getResources().getDisplayMetrics().scaledDensity;
                    }
                }

                @Override
                public void onLowMemory() {

                }
            });
        }

        double inpn=Math.sqrt(Math.pow(width,2)+Math.pow(height,2))/size/160;
        double bl=width/(Double.parseDouble(String.valueOf(inpn).substring(0,4)));
        double value= appdisplayMetrics.widthPixels/bl;

        float targetScaleDensity=(float)(value*(sNoncompatScaledDensity/sNoncompatDensity));
        int targetDensityDpi=(int)(160*inpn);
        appdisplayMetrics.density= (float) value;
        appdisplayMetrics.scaledDensity=targetScaleDensity;
        appdisplayMetrics.densityDpi=targetDensityDpi;
    }
}
