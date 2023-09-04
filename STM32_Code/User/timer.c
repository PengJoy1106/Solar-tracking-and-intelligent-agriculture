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
  __HAL_RCC_TIM3_CLK_ENABLE(); //ʹ�ܶ�ʱ��3ʱ��

  Tim3Handle.Instance = TIM3;   //���ö�ʱ��3
	
  Tim3Handle.Init.Period            = 48000-1;//0~47999Ϊһ�����ڣ���48000���������һ��һ������Ϊ1ms
  Tim3Handle.Init.Prescaler         = 0;//Ԥ��Ƶֵ������Ƶ
  Tim3Handle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;                
  Tim3Handle.Init.CounterMode       = TIM_COUNTERMODE_UP;//���ϼ���
  Tim3Handle.Init.RepetitionCounter = 0;          
	
	HAL_TIM_Base_Init(&Tim3Handle);

  HAL_TIM_Base_Start_IT(&Tim3Handle);              //��ʱ��3�ж�����
  HAL_NVIC_SetPriority(TIM3_IRQn, 3, 0);          //��ʱ��3�жϷ�������
  HAL_NVIC_EnableIRQ(TIM3_IRQn);                  //ʹ�ܶ�ʱ��3�ж�	
}


void Timer15_Config( void)
{
  __HAL_RCC_TIM15_CLK_ENABLE(); //ʹ�ܶ�ʱ��6ʱ��
	
  Tim15Handle.Instance = TIM15;   //���ö�ʱ��6

  Tim15Handle.Init.Period            = 100-1;//0~100һ�����ڣ���100���������һ��һ������Ϊ100us
  Tim15Handle.Init.Prescaler         = 48;//Ԥ��Ƶֵ��48,��1us����һ��
  Tim15Handle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;                
  Tim15Handle.Init.CounterMode       = TIM_COUNTERMODE_UP;//���ϼ���
  Tim15Handle.Init.RepetitionCounter = 0;   

	HAL_TIM_Base_Init(&Tim15Handle);

	HAL_TIM_Base_Start_IT(&Tim15Handle);              //��ʱ��6�ж�����
	
	HAL_NVIC_SetPriority(TIM15_IRQn, 3, 1);          //��ʱ��6�жϷ�������

	HAL_NVIC_EnableIRQ(TIM15_IRQn);                  //ʹ�ܶ�ʱ��6�ж�
	
}




void Timer14_Config( void)
{
  __HAL_RCC_TIM14_CLK_ENABLE(); //ʹ�ܶ�ʱ��6ʱ��
	
  Tim14Handle.Instance = TIM14;   //���ö�ʱ��6

  Tim14Handle.Init.Period            = 48000-1;//0~100һ�����ڣ���100���������һ��һ������Ϊ100us
  Tim14Handle.Init.Prescaler         = 0;//Ԥ��Ƶֵ��48
  Tim14Handle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;                
  Tim14Handle.Init.CounterMode       = TIM_COUNTERMODE_UP;//���ϼ���
  Tim14Handle.Init.RepetitionCounter = 0;          
	
	HAL_TIM_Base_Init(&Tim14Handle);

  HAL_TIM_Base_Start_IT(&Tim14Handle);              //��ʱ��6�ж�����
	
  HAL_NVIC_SetPriority(TIM14_IRQn, 3, 1);          //��ʱ��6�жϷ�������
	
  HAL_NVIC_EnableIRQ(TIM14_IRQn);                  //ʹ�ܶ�ʱ��6�ж�
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





