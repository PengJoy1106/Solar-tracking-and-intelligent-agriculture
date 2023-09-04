#include "gpio.h"





void GPIO_Config(void)
{
 GPIO_InitTypeDef GPIO_InitStructure;

	__HAL_RCC_LED_CLK_ENABLE();//��PA��ʱ��
	
	__HAL_RCC_DEV_CLK_ENABLE();

	__HAL_RCC_SENSOR_PORT_CLK_ENABLE();
	
	
	GPIO_InitStructure.Pin=LED1_PIN|LED2_PIN;             
	GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Pull=GPIO_PULLUP;
	GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_HIGH;	
	HAL_GPIO_Init(LED_PORT, &GPIO_InitStructure);	

	GPIO_InitStructure.Pin=BEEP_PIN;             
	GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Pull=GPIO_PULLUP;
	GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_HIGH;	
	HAL_GPIO_Init(SENSOR_PORT, &GPIO_InitStructure);		
	
	FAN_OFF;
	GPIO_InitStructure.Pin=FAN_PIN;             
	GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Pull=GPIO_PULLUP;
	GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_HIGH;	
	HAL_GPIO_Init(DEV_PORT, &GPIO_InitStructure);		


	GPIO_InitStructure.Pin=IR_PIN;             
	GPIO_InitStructure.Mode=GPIO_MODE_INPUT;
	GPIO_InitStructure.Pull=GPIO_PULLUP;
	GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_HIGH;	
	HAL_GPIO_Init(SENSOR_PORT, &GPIO_InitStructure);		

	
	
	
	BEEP_OFF;LED1_ON;LED2_OFF;
	

}
	

///********************************
//*������Check_Ir(void)
//*
//*���ܣ���������Ӧ����cnt_ir��0 1�����Լ�
//*
//*return���Ƿ�����״̬
//*********************************/
//unsigned char Check_Ir(void)
//{
//    unsigned char status;

//			status=READ_IR;//��ȡ�˸�״̬

//			 if(status==0){//��⵽�͵�ƽ
//			 
//				  if(cnt_ir!=0){//�˲�����ֵ��Ϊ0��˵��30s��δ��������־λ�������.cnt_ir���ж����Լ�
//							
//					    status=1;	
//					}
//			 
//			 }else{
//				 
//			      cnt_ir=30000; 
//			 }
//			 
//			 return status;
//}

