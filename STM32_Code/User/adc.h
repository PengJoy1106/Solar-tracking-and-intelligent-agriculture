#ifndef  __ADC_H
#define  __ADC_H
#include "system.h"

extern ADC_HandleTypeDef             ADC_Handle;
extern ADC_ChannelConfTypeDef        ADC_Channel_Config;
extern uint32_t                      ADC_Result;
extern unsigned short                cnt_adc;
extern unsigned char                 bad_adc;
extern void ADC_Config(void);
extern uint16_t ADC_Read(uint32_t timeout);
extern void ADC_Service(void);
extern uint16_t ADC_Read_N(unsigned char timeout);
extern unsigned char light,soil,mq7;

#endif
