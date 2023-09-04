  /******************************************************************************
  * @file    STM32F0ÄÚÍâ²¿Ê±ÖÓÅäÖ
  * @author  ·½·½ÍÁÍ¬Ñ§
  * @date    18-April-2021
  ******************************************************************************/
#include "rcc.h"

#define OSC 0x01        //¾§Õñ¾§ÕñÑ¡Ôñ
#define Inside_OSC 0x00  //ÄÚ²¿¾§Õñ
#define External_OSC 0x01//Íâ²¿¾§Õñ




uint32_t timecount;

void delayms( uint32_t ntime)
{
  timecount=ntime;
  
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;
	while(timecount!=0x00);	

}

void SysTick_timing(void)//1msÖÐ¶ÏÒ»´Î
{
  if(timecount!=0x00)
	 timecount--;	  
}  






unsigned char SystemClock_Config(void)
{				
#if (OSC == Inside_OSC)//Ê¹ÓÃÄÚ²¿¾§Õñ
		{ 
			RCC_OscInitTypeDef RCC_OscInitStruct;
			RCC_ClkInitTypeDef RCC_ClkInitStruct;
						
			RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
			RCC_OscInitStruct.HSIState=RCC_HSI_ON;
			
			RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
			RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
			RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
			RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
			if (HAL_RCC_OscConfig(&RCC_OscInitStruct)!= HAL_OK)
			{
			 return 0; // Error_Handler();
			}		
			RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1);/*ÏµÍ³Ê±ÖÓ¡¢×ÜÏßÊ±ÖÓ¡¢ÍâÉèÊ±ÖÓ**/
			RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
			RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
			RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;	
			if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1)!= HAL_OK)
			{
			 return 0;
			}
		   SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;
			return 1;
    }
	
#elif (OSC==External_OSC)
		{
			RCC_OscInitTypeDef RCC_OscInitStruct;
			RCC_ClkInitTypeDef RCC_ClkInitStruct;
			/********************Ê±ÖÓÔ´Ñ¡Ôñ***************/			
			RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
			RCC_OscInitStruct.HSEState=RCC_HSE_ON;		
			
			RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
		  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
		  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
		  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL4;	
			if (HAL_RCC_OscConfig(&RCC_OscInitStruct)!= HAL_OK)			
			{
				
				return 0;
			}		
			
			/* ******************Ê±ÖÓÉèÖÃ***************/			
			
			RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1);	
			RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
			RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
			RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
			if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1)!= HAL_OK)
			{	
				return 0;
			}
      
		 // SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;//¹Ø±ÕSysTick¶¨Ê±Æ÷
			SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;
			return 1;							
		}	
#endif	
}




