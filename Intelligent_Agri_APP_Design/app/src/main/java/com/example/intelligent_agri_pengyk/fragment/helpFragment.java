package com.example.intelligent_agri_pengyk.fragment;


import android.animation.Animator;
import android.animation.AnimatorListenerAdapter;
import android.animation.ValueAnimator;
import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.example.intelligent_agri_pengyk.R;

/**
 * A simple {@link Fragment} subclass.
 */
public class helpFragment extends Fragment  implements View.OnClickListener {

    private TextView zhiyin1, zhiyin2, zhiyin3, zhiyin4,zhiyin5;
    private ImageView zhiyinImg1, zhiyinImg2, zhiyinImg3,zhiyinImg4;
    private LinearLayout content1, content2, content3, content4,content5;
    int hiddenHeight;

    public helpFragment() {
        // Required empty public constructor
    }


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View view=inflater.inflate(R.layout.fragment_help, container, false);
        initView(view);
        return view;
    }
    private void initView(View view){
        zhiyin1 = view.findViewById(R.id.zhiyin1);
        zhiyin2 = view.findViewById(R.id.zhiyin2);
        zhiyin3 = view.findViewById(R.id.zhiyin3);
        zhiyin4 = view.findViewById(R.id.zhiyin4);
        zhiyin5 = view.findViewById(R.id.zhiyin5);
        zhiyinImg1 = view.findViewById(R.id.zhiyinimg1);
        zhiyinImg2 = view.findViewById(R.id.zhiyinimg2);
        zhiyinImg3 = view.findViewById(R.id.zhiyinimg3);
        zhiyinImg4 = view.findViewById(R.id.zhiyinimg4);
        content1 = view.findViewById(R.id.content1);
        content2 = view.findViewById(R.id.content2);
        content3 = view.findViewById(R.id.content3);
        content4 = view.findViewById(R.id.content4);
        content5 = view.findViewById(R.id.content5);

        zhiyin1.setOnClickListener(this);
        zhiyin2.setOnClickListener(this);
        zhiyin3.setOnClickListener(this);
        zhiyin4.setOnClickListener(this);
        zhiyin5.setOnClickListener(this);
        zhiyinImg1.setOnClickListener(this);
        zhiyinImg2.setOnClickListener(this);
        zhiyinImg3.setOnClickListener(this);
        float density = getResources().getDisplayMetrics().density;
        hiddenHeight= (int) (density*160+0.5f);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.zhiyin1:
            case R.id.zhiyinimg1:
                if (content1.getVisibility() == View.GONE) {
                    //打开内容
                    showView(content1);
                } else {
                    //隐藏内容
                    hideView(content1);
                }
                break;
            case R.id.zhiyin2:
            case R.id.zhiyinimg2:
                if (content2.getVisibility() == View.GONE) {
                    //打开内容
                    showView(content2);
                } else {
                    //隐藏内容
                    hideView(content2);
                }

                break;
            case R.id.zhiyin3:
            case R.id.zhiyinimg3:
                if (content3.getVisibility() == View.GONE) {
                    //打开内容
                    showView(content3);
                } else {
                    //隐藏内容
                    hideView(content3);
                }

                break;
            case R.id.zhiyin4:
            case R.id.zhiyinimg4:
                if (content4.getVisibility() == View.GONE) {
                    //打开内容
                    showView(content4);
                } else {
                    //隐藏内容
                    hideView(content4);
                }
                break;

            case R.id.zhiyin5:
                if (content5.getVisibility() == View.GONE) {
                    //打开内容
                    showView(content5);
                } else {
                    //隐藏内容
                    hideView(content5);
                }
                break;
        }
    }
    private void showView(View view){
        view.setVisibility(View.VISIBLE);
        ValueAnimator animator = myAnimator(0,hiddenHeight,view);
        animator.start();
    }
    private void hideView(final View view){
        ValueAnimator animator = myAnimator(hiddenHeight, 0, view);
        animator.addListener(new AnimatorListenerAdapter() {
            @Override
            public void onAnimationEnd(Animator animation) {
                view.setVisibility(View.GONE);
                super.onAnimationEnd(animation);
            }
        });
        animator.start();
    }
    private ValueAnimator myAnimator(int start,int end,final View view){
        final ValueAnimator animator=ValueAnimator.ofInt(start,end);
        animator.addUpdateListener(new ValueAnimator.AnimatorUpdateListener() {
            @Override
            public void onAnimationUpdate(ValueAnimator animation) {
                int value=(int)animation.getAnimatedValue();
                ViewGroup.LayoutParams layoutParams = view.getLayoutParams();
                layoutParams.height=value;
                view.setLayoutParams(layoutParams);
            }
        });
        return animator;
    }
}
