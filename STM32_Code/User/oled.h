#ifndef  __OLED_H_
#define  __OLED_H_
#include "system.h"

#define __OLED_RCC_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOB_CLK_ENABLE()
#define OLED_PORT GPIOB
#define OLED_CMD GPIO_PIN_5
#define OLED_RST GPIO_PIN_6


#define XLevelL        0x00
#define XLevelH        0x10
#define XLevel         ((XLevelH&0x0F)*16+XLevelL)
#define Max_Column     128
#define Max_Row        64
#define Brightness     0xCF 
#define X_WIDTH        128
#define Y_WIDTH        64

extern unsigned char num[];
extern unsigned char  wifi[];
extern unsigned char F8X16[];
extern unsigned char F16x16[];
extern void OLED_Config(void);


#define LCD_CLS OLED_CLS 
#define LCD_P8x16 OLED_P8x16 
#define LCD_P16x16Ch OLED_P16x16Ch 
#define LCD_P8x16Str OLED_P8x16Str 

extern void OLED_CLS(void);
extern void OLED_P8x16Str(unsigned char x, unsigned char y,unsigned char ch[]);
extern void OLED_P8x16(unsigned char x, unsigned char y,unsigned char ch[]);
extern void OLED_P16x16Ch(unsigned char x, unsigned char y, unsigned char N);	


#endif

