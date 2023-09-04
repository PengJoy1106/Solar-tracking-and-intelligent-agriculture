#ifndef  __GPIO_H
#define  __GPIO_H
#include "system.h"



#define __HAL_RCC_LED_CLK_ENABLE    __HAL_RCC_GPIOB_CLK_ENABLE
#define LED_PORT GPIOB
#define LED1_PIN GPIO_PIN_1
#define LED2_PIN GPIO_PIN_0


#define LED1_ON  HAL_GPIO_WritePin(LED_PORT, LED1_PIN, GPIO_PIN_RESET)
#define LED1_OFF HAL_GPIO_WritePin(LED_PORT, LED1_PIN, GPIO_PIN_SET)
#define LED2_ON  HAL_GPIO_WritePin(LED_PORT, LED2_PIN, GPIO_PIN_RESET)
#define LED2_OFF HAL_GPIO_WritePin(LED_PORT, LED2_PIN, GPIO_PIN_SET)




#define __HAL_RCC_SENSOR_PORT_CLK_ENABLE   __HAL_RCC_GPIOA_CLK_ENABLE
#define SENSOR_PORT GPIOA

#define MQ4_DO_PIN  GPIO_PIN_2
#define READ_MQ4_DO  HAL_GPIO_ReadPin(SENSOR_PORT, MQ4_DO_PIN)


#define IR_PIN      GPIO_PIN_6
#define READ_IR     HAL_GPIO_ReadPin(SENSOR_PORT, IR_PIN)



#define DS18B20_PIN   GPIO_PIN_1

#define READ_DS18B20  HAL_GPIO_ReadPin(SENSOR_PORT, DS18B20_PIN)

#define DS18B20_0  HAL_GPIO_WritePin(SENSOR_PORT, DS18B20_PIN, GPIO_PIN_RESET)
#define DS18B20_1  HAL_GPIO_WritePin(SENSOR_PORT, DS18B20_PIN, GPIO_PIN_SET)


#define BEEP2_PIN   GPIO_PIN_8
#define BEEP2_ON    HAL_GPIO_WritePin(SENSOR_PORT, BEEP2_PIN, GPIO_PIN_SET)
#define BEEP2_OFF   HAL_GPIO_WritePin(SENSOR_PORT, BEEP2_PIN, GPIO_PIN_RESET)

#define BEEP_PIN   GPIO_PIN_8
#define BEEP_ON    HAL_GPIO_WritePin(SENSOR_PORT, BEEP_PIN, GPIO_PIN_SET)
#define BEEP_OFF   HAL_GPIO_WritePin(SENSOR_PORT, BEEP_PIN, GPIO_PIN_RESET)




#define __HAL_RCC_DEV_CLK_ENABLE   __HAL_RCC_GPIOC_CLK_ENABLE

#define DEV_PORT   GPIOC


#define FAN_PIN    GPIO_PIN_13
#define MOTOR_PIN  GPIO_PIN_14



#define FAN_ON  HAL_GPIO_WritePin(DEV_PORT, FAN_PIN, GPIO_PIN_SET)
#define FAN_OFF HAL_GPIO_WritePin(DEV_PORT, FAN_PIN, GPIO_PIN_RESET)

#define MOTOR_ON  HAL_GPIO_WritePin(DEV_PORT, MOTOR_PIN, GPIO_PIN_SET)
#define MOTOR_OFF HAL_GPIO_WritePin(DEV_PORT, MOTOR_PIN, GPIO_PIN_RESET)





extern void GPIO_Config(void);


#endif
