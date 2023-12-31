#include "timer.h"


unsigned int timer3cnt,timer14cnt,timer15cnt;

unsigned int cnt_led,point_led=200;
unsigned char cycle_led;
unsigned int  cnt_rf;



TIM_HandleTypeDef    Tim3Handle;
TIM_HandleTypeDef    Tim14Handle;
TIM_HandleTypeDef    Tim15Handle;


void Timer3_Config( void)
{
  __HAL_RCC_TIM3_CLK_ENABLE(); //使能定时器3时钟

  Tim3Handle.Instance = TIM3;   //配置定时器3
	
  Tim3Handle.Init.Period            = 48000-1;//0~47999为一个周期，即48000个周期溢出一次一个周期为1ms
  Tim3Handle.Init.Prescaler         = 0;//预分频值：不分频
  Tim3Handle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;                
  Tim3Handle.Init.CounterMode       = TIM_COUNTERMODE_UP;//向上计数
  Tim3Handle.Init.RepetitionCounter = 0;          
	
	HAL_TIM_Base_Init(&Tim3Handle);

  HAL_TIM_Base_Start_IT(&Tim3Handle);              //定时器3中断配置
  HAL_NVIC_SetPriority(TIM3_IRQn, 3, 0);          //定时器3中断分组配置
  HAL_NVIC_EnableIRQ(TIM3_IRQn);                  //使能定时器3中断	
}


void Timer15_Config( void)
{
  __HAL_RCC_TIM15_CLK_ENABLE(); //使能定时器6时钟
	
  Tim15Handle.Instance = TIM15;   //配置定时器6

  Tim15Handle.Init.Period            = 100-1;//0~100一个周期，即100个周期溢出一次一个周期为100us
  Tim15Handle.Init.Prescaler         = 48;//预分频值：48,即1us计数一次
  Tim15Handle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;                
  Tim15Handle.Init.CounterMode       = TIM_COUNTERMODE_UP;//向上计数
  Tim15Handle.Init.RepetitionCounter = 0;   

	HAL_TIM_Base_Init(&Tim15Handle);

	HAL_TIM_Base_Start_IT(&Tim15Handle);              //定时器6中断配置
	
	HAL_NVIC_SetPriority(TIM15_IRQn, 3, 1);          //定时器6中断分组配置

	HAL_NVIC_EnableIRQ(TIM15_IRQn);                  //使能定时器6中断
	
}




void Timer14_Config( void)
{
  __HAL_RCC_TIM14_CLK_ENABLE(); //使能定时器6时钟
	
  Tim14Handle.Instance = TIM14;   //配置定时器6

  Tim14Handle.Init.Period            = 48000-1;//0~100一个周期，即100个周期溢出一次一个周期为100us
  Tim14Handle.Init.Prescaler         = 0;//预分频值：48
  Tim14Handle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;                
  Tim14Handle.Init.CounterMode       = TIM_COUNTERMODE_UP;//向上计数
  Tim14Handle.Init.RepetitionCounter = 0;          
	
	HAL_TIM_Base_Init(&Tim14Handle);

  HAL_TIM_Base_Start_IT(&Tim14Handle);              //定时器6中断配置
	
  HAL_NVIC_SetPriority(TIM14_IRQn, 3, 1);          //定时器6中断分组配置
	
  HAL_NVIC_EnableIRQ(TIM14_IRQn);                  //使能定时器6中断
}



void Timer_Config(void)
{
	Timer3_Config();
	
	//Timer14_Config();
	
	//Timer15_Config();
	
		
}





void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{ 

		if(htim==&Tim3Handle){
			
			  system_1ms=1;

		 return;
		}
		
		if(htim==&Tim15Handle){
			
       timer15cnt++;
			
			return;
		}	
		
}






