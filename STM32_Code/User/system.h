#ifndef __SYSTEM_H
#define __SYSTEM_H
#include "stm32f0xx.h"

/***********HardWare********/
#include "rcc.h"
#include "timer.h"
#include "gpio.h"
#include "usart.h"
#include "spi.h"
#include "adc.h"
#include "flashin.h"
#include "key.h"
#include "esp8266.h"

/************STDIO**********/
#include "string.h"

/***********Driver**********/
#include "oled.h"
#include "18b20.h"
#include "SI24R1.h"
#include "mhz19b.h"

#include "dht11.h"
/************APP************/
#include "app.h"

/***************************/




extern unsigned int  system_1ms;
extern unsigned char system_point;//系统指针
extern unsigned char system_cnt;  //系统计时
extern void system_start(void);   //系统启动


#endif
