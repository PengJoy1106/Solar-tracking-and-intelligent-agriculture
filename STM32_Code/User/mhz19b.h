#ifndef  __MHZ19B_H
#define  __MHZ19B_H

#include "app.h"

extern unsigned int  value_co2;

extern unsigned char flag_get_co2;

extern unsigned char index_co2;

extern unsigned int cnt_get_co2;

extern unsigned char get_start_co2;//ÆðÊ¼·û


extern unsigned int Get_CO2(unsigned char UARTX);


extern void Get_CO2_Interrupt(void);

extern void CO2_Config(unsigned char UARTX,unsigned int range);

#endif

