package com.example.intelligent_agri_pengyk.fragment;


import android.animation.Animator;
import android.animation.AnimatorListenerAdapter;
import android.animation.ValueAnimator;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.graphics.drawable.Drawable;
import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import com.example.intelligent_agri_pengyk.R;
import com.example.intelligent_agri_pengyk.manualActivity;
import com.example.intelligent_agri_pengyk.utill.DataCleanManager;


/**
 * A simple {@link Fragment} subclass.
 */
public class setFragment extends Fragment{

    int hiddenHeight;
    ListView listView;
    Button btn_exit,btn_gywm;
    LinearLayout linearLayout;
    public setFragment() {
    }


    @Override
    public View onCreateView(final LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View view=inflater.inflate(R.layout.fragment_set, container, false);
        listView=view.findViewById(R.id.set_lv);
        btn_exit=view.findViewById(R.id.set_btn);
        btn_gywm=view.findViewById(R.id.set_btn_gywm);
        linearLayout=view.findViewById(R.id.set_guanyuwomen);
        float density=getResources().getDisplayMetrics().density;
        hiddenHeight= (int) (density*160+0.5F);
        btn_exit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                final AlertDialog.Builder builder = new AlertDialog.Builder(getContext());
                builder.setTitle("退出");
                builder.setMessage("确定要退出吗？");
                builder.setPositiveButton("确认退出", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        System.exit(0);
                    }
                }).setNeutralButton("取消", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {

                    }
                }).show();
            }
        });
        btn_gywm.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (linearLayout.getVisibility() == View.GONE) {
                    showView(linearLayout);
                }else {
                    hideView(linearLayout);
                }
            }
        });

        listView.setAdapter(new MyAdapter());
        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                if (position == 0) {
                    Intent intent=new Intent(getContext(), manualActivity.class);
                    startActivity(intent);
                }else if (position==1){
                    Toast.makeText(getContext(), "清除成功!", Toast.LENGTH_SHORT).show();
                } else if (position == 2) {
                    Toast.makeText(getContext(), "已经是最新版本!", Toast.LENGTH_SHORT).show();
                }
            }
        });
        return view;
    }


    private class MyAdapter extends BaseAdapter{
        Integer[] imgs={R.mipmap.zidongkongzhi,R.mipmap.qinchuhuancun,R.mipmap.banbengengx};
        String[] titles={"自动控制","清除缓存","版本更新"};

        public MyAdapter() {
        }

        @Override
        public int getCount() {
            return titles.length;
        }

        @Override
        public Object getItem(int position) {
            return null;
        }

        @Override
        public long getItemId(int position) {
            return position;
        }

        @Override
        public View getView(int position, View convertView, ViewGroup parent) {
            final ViewHolder viewHolder;
            if (convertView == null) {
                convertView=getLayoutInflater().inflate(R.layout.lv_set_item,null);
                viewHolder=new ViewHolder();
                viewHolder.imageView=convertView.findViewById(R.id.lv_set_img);
                viewHolder.tv_title=convertView.findViewById(R.id.lv_set_tv1);
                viewHolder.tv_right=convertView.findViewById(R.id.lv_set_tv2);
                convertView.setTag(viewHolder);
            }else {
                viewHolder= (ViewHolder) convertView.getTag();
            }
            viewHolder.imageView.setImageResource(imgs[position]);
            viewHolder.tv_title.setText(titles[position]);
            if (position==0|position==3){
            Drawable drawableLeft = getResources().getDrawable(R.mipmap.gengduo);
            viewHolder.tv_right.setCompoundDrawablesWithIntrinsicBounds(null,null,drawableLeft,null);
                viewHolder.tv_right.setText("");
            }
            if (position==1){
                String totalCacheSize=null;
                DataCleanManager dataCleanManager=new DataCleanManager();
                try {
                    totalCacheSize = dataCleanManager.getCacheSize(getContext().getCacheDir());
                } catch (Exception e) {
                    e.printStackTrace();
                }
                viewHolder.tv_right.setText("缓存:"+totalCacheSize);
            }else if (position == 2) {
                String versionName=null;
                try {
                    PackageManager packageManager=getContext().getPackageManager();
                    PackageInfo packageInfo = packageManager.getPackageInfo(getContext().getPackageName(), 0);
                    versionName = packageInfo.versionName;
                } catch (PackageManager.NameNotFoundException e) {
                    e.printStackTrace();
                }
                viewHolder.tv_right.setText("当前版本:"+versionName);
            }
            return convertView;
        }

    }
    private class ViewHolder{
        TextView tv_title,tv_right;
        ImageView imageView;
    }
    private void showView(View view){
        view.setVisibility(View.VISIBLE);
        ValueAnimator animator=myAnimation(0,hiddenHeight,view);
        animator.start();
    }
    private void hideView(final View view){
        ValueAnimator animator=myAnimation(hiddenHeight,0,view);
        animator.addListener(new AnimatorListenerAdapter() {
            @Override
            public void onAnimationEnd(Animator animation) {
                super.onAnimationEnd(animation);
                view.setVisibility(View.GONE);
            }
        });
        animator.start();
    }
    private ValueAnimator myAnimation(int start,int end,final View view){
        final ValueAnimator animator=ValueAnimator.ofInt(start,end);
        animator.addUpdateListener(new ValueAnimator.AnimatorUpdateListener() {
            @Override
            public void onAnimationUpdate(ValueAnimator animation) {
                int value= (int) animator.getAnimatedValue();
                ViewGroup.LayoutParams layoutParams=view.getLayoutParams();
                layoutParams.height=value;
                view.setLayoutParams(layoutParams);
            }
        });
        return animator;
    }
}
