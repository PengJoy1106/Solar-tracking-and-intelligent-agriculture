package com.example.intelligent_agri_pengyk.fragment;


import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.RadioButton;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.viewpager.widget.PagerAdapter;
import androidx.viewpager.widget.ViewPager;

import com.example.intelligent_agri_pengyk.R;
import com.example.intelligent_agri_pengyk.controlActivity;
import com.example.intelligent_agri_pengyk.entity.myentity;
import com.example.intelligent_agri_pengyk.utill.okhttputils;

import java.util.ArrayList;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;


/**
 * A simple {@link Fragment} subclass.
 */
public class firstFragment extends Fragment {
    List<View> mDate;
    ListView lv;
    List<View> Date;
    ViewPager viewPager;
    List<RadioButton> rbs;
    View vp;
    myentity myentity;
    okhttputils okhttputils1;

    private Handler handler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
            if (msg.what == 0) {
                viewPager.setCurrentItem(viewPager.getCurrentItem()+1);
                handler.sendEmptyMessageDelayed(0,2500);
            } else if (msg.what ==100) {
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
                int[] contr= (int[]) obj.get(2);
                myentity.setBaojing(contr[3]);
            } else if (msg.what == -1) {
                handler.removeCallbacksAndMessages(null);
            }
        }
    };

//                    if (myentity.getBeam()>=myentity.getBeammin()&&myentity.getBeam()<=myentity.getBeammax()
//                            &&myentity.getCo2concentration()>=myentity.getCo2min()&&myentity.getCo2concentration()<=myentity.getCo2max()
//                            &&myentity.getSoiltemperature() <= myentity.getSoiltemperaturemax() && myentity.getSoiltemperature() >= myentity.getSoiltemperaturemin()
//                            &&myentity.getSoilmoisture()<=myentity.getSoilmoisturemax()&&myentity.getSoilmoisture()>=myentity.getSoilmoisturemin()
//                            &&myentity.getAirtemperature() <= myentity.getAirtemperaturemax() && myentity.getAirtemperature() >= myentity.getAirtemperaturemin()
//                            &&myentity.getAirmoisture()<=myentity.getAirmoisturemax()&&myentity.getAirmoisture()>=myentity.getAirmoisturemin()){
//                        try {
//                            okhttputils1.control(myentity, 0,"Buzzer");
//                        } catch (IOException e) {
//                            e.printStackTrace();
//                        } catch (JSONException e) {
//                            e.printStackTrace();
//                        }
//                        Log.e("-5", "handleMessage: 1" );
//                    }else {
//                        try {
//                            okhttputils1.control(myentity, 1,"Buzzer");
//                        } catch (IOException e) {
//                            e.printStackTrace();
//                        } catch (JSONException e) {
//                            e.printStackTrace();
//                        }
//                        Log.e("-5", "handleMessage: 2" );
//                    }
    public firstFragment() {

    }


    @Override
    public View onCreateView(final LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        final View view=inflater.inflate(R.layout.fragment_first, container, false);
        /**
         * ListView
         */
        myentity= (com.example.intelligent_agri_pengyk.entity.myentity) getActivity().getApplication();
        lv=view.findViewById(R.id.first_lv01);
        LayoutInflater layoutInflater=getLayoutInflater();
        View lv_item01=layoutInflater.inflate(R.layout.shouye_lv_item_01,null);
        View lv_item02=layoutInflater.inflate(R.layout.shouye_lv_item_02,null);
        vp=layoutInflater.inflate(R.layout.viewpage_item01,null);
        mDate=new ArrayList<>();
        mDate.add(lv_item01);
        mDate.add(lv_item01);
        mDate.add(lv_item02);
        mDate.add(lv_item02);
        Date=new ArrayList<>();
        Date.add(layoutInflater.inflate(R.layout.viewpager01, null));
        Date.add(layoutInflater.inflate(R.layout.viewpager02, null));
        Date.add(layoutInflater.inflate(R.layout.viewpager03, null));
        viewPager=vp.findViewById(R.id.first_vp01);
        viewPager.setCurrentItem(0);
        handler.sendEmptyMessage(0);
        rbs=new ArrayList<>();
        RadioButton radioButton1=vp.findViewById(R.id.first_rb01);
        RadioButton radioButton2=vp.findViewById(R.id.first_rb02);
        RadioButton radioButton3=vp.findViewById(R.id.first_rb03);
        rbs.add(radioButton1);
        rbs.add(radioButton2);
        rbs.add(radioButton3);
        viewPager.addOnPageChangeListener(new ViewPager.OnPageChangeListener() {
            @Override
            public void onPageScrolled(int position, float positionOffset, int positionOffsetPixels) {
                if (String.valueOf(position) !=null) {
                    rbs.get(position%rbs.size()).setChecked(true);
                }
            }

            @Override
            public void onPageSelected(int position) {

            }

            @Override
            public void onPageScrollStateChanged(int state) {

            }
        });
        viewPager.setAdapter(new PagerAdapter() {
            @Override
            public int getCount() {
                return Integer.MAX_VALUE;
            }

            @Override
            public boolean isViewFromObject(@NonNull View view, @NonNull Object object) {
                return view==object;
            }

            @NonNull
            @Override
            public Object instantiateItem(@NonNull ViewGroup container, int position) {
                ViewGroup parentViewGroup = (ViewGroup)Date.get(position%Date.size()).getParent();
                if (parentViewGroup != null) {
                    parentViewGroup.removeAllViews();
                }
                Date=new ArrayList<>();
                Date.add(getLayoutInflater().inflate(R.layout.viewpager01, null));
                Date.add(getLayoutInflater().inflate(R.layout.viewpager02, null));
                Date.add(getLayoutInflater().inflate(R.layout.viewpager03, null));
                container.addView(Date.get(position%Date.size()));
                return Date.get(position%Date.size());
            }

            @Override
            public void destroyItem(@NonNull ViewGroup container, int position, @NonNull Object object) {
                int index=position%Date.size();
                View view = Date.get(index);
                container.removeView(view);
            }
        });
        lv.setAdapter(new MyAdapter(mDate,getContext()));
        lv.addHeaderView(vp);
        lv.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                Intent intent=new Intent(getContext(), controlActivity.class);
                switch (position){
                    case 1:
                        handler.sendEmptyMessage(-1);
                        handler.removeCallbacksAndMessages(null);
                        intent.putExtra("position",1);
                        startActivity(intent);
                        getActivity().finish();
                        break;
                    case 2:
                        intent.putExtra("position",2);
                        startActivity(intent);
                        getActivity().finish();
                        break;
                    case 3:
                        intent.putExtra("position",3);
                        startActivity(intent);
                        getActivity().finish();
                        break;
                    case 4:
                        intent.putExtra("position",4);
                        startActivity(intent);
                        getActivity().finish();
                        break;
                }
            }
        });
        Timer timer=new Timer();
        okhttputils1=new okhttputils();
        TimerTask timerTask=new TimerTask() {
            @Override
            public void run() {
                try {
                    String[] sensor = okhttputils1.getSensor(myentity);
                    int[] getmaxmin = okhttputils1.getmaxmin(myentity);
                    int[] contorllerStatus = okhttputils1.getContorllerStatus(myentity);
                    List<Object> obj=new ArrayList<>();
                    obj.add(sensor);
                    obj.add(getmaxmin);
                    obj.add(contorllerStatus);
                    Message msg=new Message();
                    msg.obj=obj;
                    msg.what=100;
                    handler.sendMessage(msg);
                    if (myentity.getBeam()>=myentity.getBeammin()&&myentity.getBeam()<=myentity.getBeammax()
                            &&myentity.getCo2concentration()>=myentity.getCo2min()&&myentity.getCo2concentration()<=myentity.getCo2max()
                            &&myentity.getSoiltemperature() <= myentity.getSoiltemperaturemax() && myentity.getSoiltemperature() >= myentity.getSoiltemperaturemin()
                            &&myentity.getSoilmoisture()<=myentity.getSoilmoisturemax()&&myentity.getSoilmoisture()>=myentity.getSoilmoisturemin()
                            &&myentity.getAirtemperature() <= myentity.getAirtemperaturemax() && myentity.getAirtemperature() >= myentity.getAirtemperaturemin()
                            &&myentity.getAirmoisture()<=myentity.getAirmoisturemax()&&myentity.getAirmoisture()>=myentity.getAirmoisturemin()){
                            if (myentity.getBaojing()==1){
                                okhttputils1.control(myentity, 0,"Buzzer");
                                Log.e("eee", "run: 1" );
                            }
                    }else {
                        if (myentity.getBaojing()==0){
                            okhttputils1.control(myentity, 1,"Buzzer");
                            Log.e("eee", "run: 2" );
                        }
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        };
        timer.schedule(timerTask,0,3000);
        return view;
    }
    private class MyAdapter extends BaseAdapter{

        public List<View> mDate;
        public Context context;
        Integer[] imgs={R.mipmap.p1,R.mipmap.p2,R.mipmap.p3};

        public MyAdapter(List<View> mDate, Context context){
            this.mDate=mDate;
            this.context=context;
        }

        @Override
        public int getCount() {
            return mDate.size();
        }

        @Override
        public Object getItem(int position) {
            return mDate.get(position);
        }

        @Override
        public long getItemId(int position) {
            return position;
        }

        @Override
        public View getView(int position, View convertView, final ViewGroup parent) {
            myentity= (com.example.intelligent_agri_pengyk.entity.myentity) getActivity().getApplication();
            if (position == 0||position==1) {
                final ViewHolder viewHolder;
                if (convertView == null) {
                    viewHolder=new ViewHolder();
                    convertView=LayoutInflater.from(getContext()).inflate(R.layout.shouye_lv_item_01,null);
                    viewHolder.roundimg=convertView.findViewById(R.id.shouye_lv01_roundimg);
                    viewHolder.img01=convertView.findViewById(R.id.shouye_lv01_co2_img01);
                    viewHolder.co2_tv01=convertView.findViewById(R.id.shouye_lv01_co2_tv01);
                    viewHolder.co2_tv02=convertView.findViewById(R.id.shouye_lv01_co2_tv02);
                    viewHolder.tv01=convertView.findViewById(R.id.shouye_lv01_tv01);
                    viewHolder.tv02=convertView.findViewById(R.id.shouye_lv01_tv02);
                    viewHolder.tv03=convertView.findViewById(R.id.shouye_lv01_tv03);
                    convertView.setTag(viewHolder);
                }else{
                    viewHolder= (ViewHolder) convertView.getTag();
                }
                if (position == 0) {
                    Timer timer=new Timer();
                    TimerTask task=new TimerTask() {
                        @Override
                        public void run() {
                            if (myentity.getCo2concentration()<=myentity.getCo2max()&&myentity.getCo2concentration()>=myentity.getCo2min()){
                                viewHolder.img01.setImageResource(R.mipmap.p1);
                            }else if (myentity.getCo2concentration()>myentity.getCo2max()){
                                viewHolder.img01.setImageResource(R.mipmap.p3);
                            } else if (myentity.getCo2concentration() < myentity.getCo2min()) {
                                viewHolder.img01.setImageResource(R.mipmap.p2);
                            }
                            viewHolder.co2_tv01.setText(myentity.getCo2concentration()+"");
                            viewHolder.co2_tv02.setText(myentity.getCo2min()+"-"+myentity.getCo2max());
                        }
                    };
                    timer.schedule(task,0,3000);
                } else if (position == 1) {
                    viewHolder.roundimg.setImageResource(R.mipmap.guangzhao);
                    viewHolder.img01.setImageResource(imgs[2]);
                    viewHolder.tv01.setText(R.string.item2);
                    viewHolder.tv02.setText(R.string.item2_a);
                    viewHolder.tv03.setText(R.string.setname);
                    Timer timer=new Timer();
                    TimerTask task=new TimerTask() {
                        @Override
                        public void run() {
                            if (myentity.getBeam()<=myentity.getBeammax()&&myentity.getBeam()>=myentity.getBeammin()){
                                viewHolder.img01.setImageResource(R.mipmap.p1);
                            }else if (myentity.getBeam()>myentity.getBeammax()){
                                viewHolder.img01.setImageResource(R.mipmap.p3);
                            } else if (myentity.getBeam() < myentity.getBeammin()) {
                                viewHolder.img01.setImageResource(R.mipmap.p2);
                            }
                            viewHolder.co2_tv01.setText(""+myentity.getBeam());
                            viewHolder.co2_tv02.setText(myentity.getBeammin()+"-"+myentity.getBeammax());
                        }
                    };
                    timer.schedule(task,0,3000);
                }
            }
            if (position == 2||position==3) {
                final ViewHolder viewHolder;
                if (convertView == null) {
                    viewHolder=new ViewHolder();
                    convertView=LayoutInflater.from(getContext()).inflate(R.layout.shouye_lv_item_02,null);
                    viewHolder.roundimg_1=convertView.findViewById(R.id.shouye_lv02_roundimg);
                    viewHolder.img01_1=convertView.findViewById(R.id.shouye_lv02_co2_img01);
                    viewHolder.tv_title_1=convertView.findViewById(R.id.shouye_lv02_tv01);
                    viewHolder.tv01_1=convertView.findViewById(R.id.shouye_lv02_tv_pm25);
                    viewHolder.tv02_1=convertView.findViewById(R.id.shouye_lv02_co2_tv01);
                    viewHolder.tv03_1=convertView.findViewById(R.id.shouye_lv02_co2_tv03);
                    viewHolder.tv04_1=convertView.findViewById(R.id.shouye_lv02_co2_tv02);
                    viewHolder.tv05_1=convertView.findViewById(R.id.shouye_lv02_co2_tv04);
                    convertView.setTag(viewHolder);
                }else{
                    viewHolder= (ViewHolder) convertView.getTag();
                }
                if (position == 2) {
                    viewHolder.tv01_1.setText("");
                    viewHolder.roundimg_1.setImageResource(R.mipmap.turang);
                    viewHolder.tv_title_1.setText(R.string.item6_0);
                    viewHolder.img01_1.setImageResource(R.mipmap.p1);
                        Timer timer=new Timer();
                        TimerTask task=new TimerTask() {
                            @Override
                            public void run() {
                                if (myentity.getSoiltemperature() <= myentity.getSoiltemperaturemax() && myentity.getSoiltemperature() >= myentity.getSoiltemperaturemin()
                                &&myentity.getSoilmoisture()<=myentity.getSoilmoisturemax()&&myentity.getSoilmoisture()>=myentity.getSoilmoisturemin()) {
                                    viewHolder.img01_1.setImageResource(R.mipmap.p1);
                                }else if (myentity.getSoiltemperature()<myentity.getSoiltemperaturemin()||myentity.getSoilmoisture()<myentity.getSoilmoisturemin()){
                                    viewHolder.img01_1.setImageResource(R.mipmap.p2);
                                }else {
                                    viewHolder.img01_1.setImageResource(R.mipmap.p3);
                                }
                                viewHolder.tv02_1.setText(""+myentity.getSoiltemperature());
                                viewHolder.tv03_1.setText(""+myentity.getSoilmoisture());
                                viewHolder.tv04_1.setText(myentity.getSoiltemperaturemin()+"-"+myentity.getSoiltemperaturemax());
                                viewHolder.tv05_1.setText(myentity.getSoilmoisturemin()+"-"+myentity.getSoilmoisturemax());
                            }
                        };
                        timer.schedule(task,0,3000);
                }else if (position==3){
                        Timer timer=new Timer();
                        TimerTask task=new TimerTask() {
                            @Override
                            public void run() {
                                if (myentity.getAirtemperature() <= myentity.getAirtemperaturemax() && myentity.getAirtemperature() >= myentity.getAirtemperaturemin()
                                        &&myentity.getAirmoisture()<=myentity.getAirmoisturemax()&&myentity.getAirmoisture()>=myentity.getAirmoisturemin()) {
                                    viewHolder.img01_1.setImageResource(R.mipmap.p1);
                                }else if (myentity.getAirtemperature()<myentity.getAirtemperaturemin()||myentity.getAirmoisture()<myentity.getAirmoisturemin()){
                                    viewHolder.img01_1.setImageResource(R.mipmap.p2);
                                }else {
                                    viewHolder.img01_1.setImageResource(R.mipmap.p3);
                                }
                                viewHolder.tv02_1.setText(""+myentity.getAirtemperature());
                                viewHolder.tv03_1.setText(""+myentity.getAirmoisture());
                                viewHolder.tv04_1.setText(myentity.getAirtemperaturemin()+"-"+myentity.getSoiltemperaturemax());
                                viewHolder.tv05_1.setText(myentity.getAirmoisturemin()+"-"+myentity.getSoilmoisturemax());
                            }
                        };
                        timer.schedule(task,0,3000);
                    }
            }

            return convertView;
        }
    }
    private class ViewHolder{
        ImageView roundimg,img01,roundimg_1,img01_1;
        TextView tv01,tv02,tv03,co2_tv01,co2_tv02,tv01_1,tv02_1,tv03_1,tv04_1,tv05_1,tv_title_1;
    }
}
