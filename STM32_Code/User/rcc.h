#ifndef  __RCC_H
#define  __RCC_H
#include "system.h"

extern unsigned char SystemClock_Config(void);


extern uint32_t timecount;
extern void delayms(volatile uint32_t ntime);
extern void SysTick_timing(void);


#endif
