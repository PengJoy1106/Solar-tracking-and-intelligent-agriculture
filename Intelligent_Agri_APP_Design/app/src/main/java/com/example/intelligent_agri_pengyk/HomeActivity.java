package com.example.intelligent_agri_pengyk;

import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentPagerAdapter;
import androidx.viewpager.widget.ViewPager;

import com.example.intelligent_agri_pengyk.fragment.firstFragment;
import com.example.intelligent_agri_pengyk.fragment.helpFragment;
import com.example.intelligent_agri_pengyk.fragment.setFragment;

import java.util.ArrayList;
import java.util.List;

public class HomeActivity extends AppCompatActivity implements View.OnClickListener, KeyEvent.Callback {
    RadioGroup radioGroup;
    RadioButton radioButton01,radioButton02,radioButton03;
    ViewPager viewPager;
    TextView textView;
    String []titles={"智能农业管理系统","设置","帮助"};
    int []btns={R.id.home_rb01,R.id.home_rb02,R.id.home_rb03};
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_home);
        radioGroup=findViewById(R.id.home_rg01);
        radioButton01=findViewById(R.id.home_rb01);
        radioButton02=findViewById(R.id.home_rb02);
        radioButton03=findViewById(R.id.home_rb03);
        radioButton01.performClick();
        radioButton01.setOnClickListener(this);
        radioButton02.setOnClickListener(this);
        radioButton03.setOnClickListener(this);
        viewPager=findViewById(R.id.home_vp01);
        textView=findViewById(R.id.home_tv_title);
        FragmentManager fragmentManager=getSupportFragmentManager();
        List<Fragment> fragmentList=new ArrayList<>();
        fragmentList.add(new firstFragment());
        fragmentList.add(new setFragment());
        fragmentList.add(new helpFragment());
        viewPager.setAdapter(new MyAdapter(fragmentManager,fragmentList));
        viewPager.setCurrentItem(0);
        viewPager.setOnPageChangeListener(new ViewPager.OnPageChangeListener() {
            @Override
            public void onPageScrolled(final int position, float positionOffset, int positionOffsetPixels) {
                textView.setText(titles[position]);
                radioGroup.check(btns[position]);
            }

            @Override
            public void onPageSelected(int position) {

            }

            @Override
            public void onPageScrollStateChanged(int state) {

            }
        });

    }

    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.home_rb01:
                viewPager.setCurrentItem(0);
                break;
            case R.id.home_rb02:
                viewPager.setCurrentItem(1);
                break;
            case R.id.home_rb03:
                viewPager.setCurrentItem(2);
                break;
        }
    }


    class MyAdapter extends FragmentPagerAdapter{
        List<Fragment> fragments;

        public MyAdapter(FragmentManager fm, List<Fragment> fragments) {
            super(fm);
            this.fragments=fragments;
        }

        @Override
        public Fragment getItem(int position) {
            return fragments.get(position);
        }

        @Override
        public int getCount() {
            return fragments.size();
        }
    }
    long time=0;
    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        if (keyCode == event.KEYCODE_BACK) {
            if (System.currentTimeMillis() - time > 2000) {
                Toast.makeText(getApplicationContext(), "再次点击退出程序!", Toast.LENGTH_SHORT).show();
                time=System.currentTimeMillis();
            }else {
                System.exit(0);
            }
        }
        return true;
    }
}
