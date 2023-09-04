#ifndef  __EXTI_H
#define  __EXTI_H
#include "stm32f0xx.h"

extern void Exti_Gpio_Config(void);

extern void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#endif
