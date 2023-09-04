#ifndef  __DS18B20_H
#define  __DS18B20_H

#include "system.h" 

extern unsigned char bad_wendu;
extern double result_18b20;
extern 	unsigned char wendu_shi,wendu_ge;


void delay_18b20(unsigned int z);//延时函数

void rest_18b20(void);//复位

void txd_18b20(unsigned char mingling);//写数据

unsigned char rxd_18b20(void);//读数据

extern unsigned int DS18B20_GetTemp(void);//温度转换
extern void DS18B20_GET(void);






#endif
