#ifndef  __KEY_H
#define  __KEY_H
#include "system.h"

#define __HAL_RCC_KEY_CLK_ENABLE()    __HAL_RCC_GPIOA_CLK_ENABLE()


#define KEY_PORT          GPIOB
#define KEY_A             GPIO_PIN_11  //S2
#define KEY_B             GPIO_PIN_10  //S3
#define KEY_C             GPIO_PIN_12  //S1


#define READ_A            HAL_GPIO_ReadPin(KEY_PORT,KEY_A)
#define READ_B            HAL_GPIO_ReadPin(KEY_PORT,KEY_B)
#define READ_C            HAL_GPIO_ReadPin(KEY_PORT,KEY_C)


#define VALUE_A        0x01
#define VALUE_B        0x02
#define VALUE_C        0x04

extern unsigned short  keycnt;

extern unsigned char key_status;

extern unsigned char key_flag,key_value;

extern void  Key_Config(void);
extern unsigned char keyscan(void);



#endif

