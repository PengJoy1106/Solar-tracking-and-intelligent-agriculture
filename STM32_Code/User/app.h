#ifndef __APP_H
#define __APP_H
#include "system.h"


#define TYPE_MASTER  0x30
#define TYPE_POINT1  0x31
#define TYPE_POINT2  0x32
#define TYPE         TYPE_POINT1  //�ڵ����

extern unsigned char bad_wendu1,bad_wendu2,bad_qiti1,bad_qiti2;
extern unsigned char gas_bi;
extern unsigned int  adc;
extern unsigned char max_wendu,max_qiti;
extern unsigned char temperature,gas;
extern unsigned int  cnt_beep;//��������ʱ
extern unsigned int  cnt_syn; //ͬ����ʱ
extern unsigned int  cnt_check_point;//��ѯ�ڵ����ֵ
extern unsigned int  cnt_check; //��ѯ����ʱ

extern unsigned char flag_check;//��ѯ��־λ
extern unsigned char point_beep[3];//�ڵ�������澯��־
extern unsigned char flag_beep;//������������־λ
extern unsigned char flag_alarm[3];//�˸и澯����

extern unsigned int  cnt_display;   //��ʾ���¼���ֵ
extern unsigned char shift_display; //��ʾ��ת��־λ
extern unsigned char mode_display;  //��ʾģʽ
extern unsigned char mode_set;//��������

extern unsigned char min_wendu,max_wendu;
extern unsigned char min_shidu,max_shidu;
extern unsigned char min_light,max_light;
extern unsigned char min_soil,max_soil;

extern unsigned char max_qiti;
extern unsigned char max_mq7;
extern unsigned char flag_net_fan;
extern unsigned char flag_alarm_on;//�ƶ˿���
extern unsigned char alarm_temperature;//�¶ȱ���
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


