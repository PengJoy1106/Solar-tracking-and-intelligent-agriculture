#ifndef  __DS18B20_H
#define  __DS18B20_H

#include "system.h" 

extern unsigned char bad_wendu;
extern double result_18b20;
extern 	unsigned char wendu_shi,wendu_ge;


void delay_18b20(unsigned int z);//��ʱ����

void rest_18b20(void);//��λ

void txd_18b20(unsigned char mingling);//д����

unsigned char rxd_18b20(void);//������

extern unsigned int DS18B20_GetTemp(void);//�¶�ת��
extern void DS18B20_GET(void);






#endif
