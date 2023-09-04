#ifndef  __RTC_H
#define  __RTC_H
#include "stm32f0xx.h"

extern RTC_HandleTypeDef RTC_Handle;
extern void RTC_Config(void);
extern void RTC_AlarmConfig(void);
extern void RTC_TimeShow(void);
#endif
