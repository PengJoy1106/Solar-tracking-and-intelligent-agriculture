#ifndef  __TIMER_H
#define  __TIMER_H


#include "system.h"        //头文件管理

extern unsigned char cycle_led;
extern unsigned int timer3cnt,cnt_led,point_led;
extern unsigned int cnt_rf;

extern unsigned int timer15cnt;



extern TIM_HandleTypeDef    Tim3Handle;
extern TIM_HandleTypeDef    Tim15Handle;
extern TIM_HandleTypeDef    Tim14Handle;

extern void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

extern void Timer3_Config(void);
extern void Timer6_Config(void);
extern void Timer_Config(void);



extern void led_cycle(void);

#endif
