#ifndef  __DHT11_H
#define  __DHT11_H

#include "app.h"


#define DHT11_PORT  GPIOA
#define DHT11_PIN   GPIO_PIN_1

#define DHT11_PIN_1      HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_SET)
#define DHT11_PIN_0      HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_RESET)
#define READ_DHT11_PIN   HAL_GPIO_ReadPin(DHT11_PORT,DHT11_PIN)


extern volatile unsigned int dht11_temperature,dht11_humidity;

extern unsigned int datatemp;

extern char temp_hl,temp_hh, temp_th, temp_tl,Cheak_Data;

static void delayus(uint16_t time);

static int DHT11_ReadDataBit(void);

extern void DHT11_Read(void);

extern void Show_DHT11(void);

void DHT11_OLED_display(void);

void DHT11_PIN_IN(void);
void DHT11_PIN_OUT(void);

#endif
