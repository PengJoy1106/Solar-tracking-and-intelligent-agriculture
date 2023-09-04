#ifndef  __SPI_H
#define  __SPI_H
#include "system.h"

#define SPI1_PORT GPIOA
#define SPI1_SCLK GPIO_PIN_5
#define SPI1_MISO GPIO_PIN_6
#define SPI1_MOSI GPIO_PIN_7

#define SPI2_PORT GPIOB
#define SPI2_SCLK GPIO_PIN_13
#define SPI2_MISO GPIO_PIN_14
#define SPI2_MOSI GPIO_PIN_15


extern void SPI_Config(void);	

extern SPI_HandleTypeDef   SPI1_Handle; 
extern SPI_HandleTypeDef   SPI2_Handle; 
#endif
