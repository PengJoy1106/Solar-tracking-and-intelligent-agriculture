#include "exti.h"
#include "led.h"

//按键IO:PA0接上拉
void delay(uint32_t z)
{
 uint32_t x,y;
	for(x=z;x>0;x--)
	for(y=1000;y>0;y--);

}
void Exti_Gpio_Config(void)
{
 GPIO_InitTypeDef GPIO_InitStructure;

  __HAL_RCC_GPIOA_CLK_ENABLE(); 
	
 GPIO_InitStructure.Pin=GPIO_PIN_0;
 GPIO_InitStructure.Mode=GPIO_MODE_IT_RISING;
 GPIO_InitStructure.Pull=GPIO_PULLDOWN;		
 HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
	
  
 HAL_NVIC_SetPriority(EXTI0_1_IRQn, 0, 0);
 
 HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);

}

	
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_0)
	{
		LED_ON;
		delay(1000);
		LED_OFF;
		delay(1000);
		LED_ON;
		delay(1000);
		LED_OFF;
		delay(1000);
	}

}






