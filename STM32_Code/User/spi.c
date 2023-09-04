#include "spi.h"

SPI_HandleTypeDef   SPI1_Handle;
SPI_HandleTypeDef   SPI2_Handle;

void SPI_Config(void)
	{
		       GPIO_InitTypeDef GPIO_InitStructure;		
		__HAL_RCC_SPI2_CLK_ENABLE();
	    __HAL_RCC_GPIOB_CLK_ENABLE(); //¿ªPB¿ÚÊ±ÖÓ
		
		GPIO_InitStructure.Pin=(SPI2_SCLK | SPI2_MISO | SPI2_MOSI);
        GPIO_InitStructure.Mode=GPIO_MODE_AF_PP;
		GPIO_InitStructure.Pull=GPIO_PULLUP;
		GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStructure.Alternate=GPIO_AF0_SPI2;
		HAL_GPIO_Init(SPI2_PORT, &GPIO_InitStructure);		
				
		SPI2_Handle.Instance               = SPI2;
		SPI2_Handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
		SPI2_Handle.Init.Direction         = SPI_DIRECTION_2LINES;
		SPI2_Handle.Init.CLKPhase          = SPI_PHASE_1EDGE;
		SPI2_Handle.Init.CLKPolarity       = SPI_POLARITY_LOW;
		SPI2_Handle.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
		SPI2_Handle.Init.CRCPolynomial     = 7;
		SPI2_Handle.Init.DataSize          = SPI_DATASIZE_8BIT;
		SPI2_Handle.Init.FirstBit          = SPI_FIRSTBIT_MSB;
		SPI2_Handle.Init.NSS               = SPI_NSS_SOFT;
		SPI2_Handle.Init.TIMode            = SPI_TIMODE_DISABLE;
		SPI2_Handle.Init.NSSPMode          = SPI_NSS_PULSE_DISABLE;
		SPI2_Handle.Init.CRCLength         = SPI_CRC_LENGTH_8BIT;
		SPI2_Handle.Init.Mode = SPI_MODE_MASTER;
	

   HAL_SPI_Init(&SPI2_Handle);
	
		
	}





