#ifndef __APP_H
#define __APP_H
#include "system.h"


#define TYPE_MASTER  0x30
#define TYPE_POINT1  0x31
#define TYPE_POINT2  0x32
#define TYPE         TYPE_POINT1  //节点编译

extern unsigned char bad_wendu1,bad_wendu2,bad_qiti1,bad_qiti2;
extern unsigned char gas_bi;
extern unsigned int  adc;
extern unsigned char max_wendu,max_qiti;
extern unsigned char temperature,gas;
extern unsigned int  cnt_beep;//蜂鸣器计时
extern unsigned int  cnt_syn; //同步计时
extern unsigned int  cnt_check_point;//查询节点计数值
extern unsigned int  cnt_check; //查询倒计时

extern unsigned char flag_check;//查询标志位
extern unsigned char point_beep[3];//节点蜂鸣器告警标志
extern unsigned char flag_beep;//蜂鸣器报警标志位
extern unsigned char flag_alarm[3];//人感告警开关

extern unsigned int  cnt_display;   //显示更新计数值
extern unsigned char shift_display; //显示翻转标志位
extern unsigned char mode_display;  //显示模式
extern unsigned char mode_set;//按键设置

extern unsigned char min_wendu,max_wendu;
extern unsigned char min_shidu,max_shidu;
extern unsigned char min_light,max_light;
extern unsigned char min_soil,max_soil;

extern unsigned char max_qiti;
extern unsigned char max_mq7;
extern unsigned char flag_net_fan;
extern unsigned char flag_alarm_on;//云端控制
extern unsigned char alarm_temperature;//温度报警
extern unsigned char alarm_humidity;//
extern unsigned char alarm_light;//
extern unsigned char alarm_soil;//
extern unsigned char man;//
extern void App_GetSensor_Point(void);

extern void App_Alarm_Point(void);

extern void App_Alarm(void);

extern void App_NRF_Point(void);

extern void App_NRF_Master(void);

extern void App_Key_Point(void);

extern void App_Key_Master(void);


extern void App_Display_Sensor_Config(void);
extern void App_Display_Sensor(void);
extern void App_Display_Alarm_Config(void);
extern void App_Display_Alarm(void);
extern void App_Display_Update(void);

#endif 


