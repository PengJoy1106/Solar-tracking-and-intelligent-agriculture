#include "key.h"

#define key_unpress 0x00
#define key_press   0x01
#define key_release 0x02

unsigned short  keycnt;

unsigned char key_status=0;

unsigned char key_flag=0,key_value;

unsigned char key_temp;



void  Key_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
 
  __HAL_RCC_KEY_CLK_ENABLE();
	GPIO_InitStructure.Pin=KEY_A|KEY_B|KEY_C;
	GPIO_InitStructure.Mode=GPIO_MODE_INPUT;
	GPIO_InitStructure.Pull=GPIO_PULLUP;
	GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_LOW;	
	HAL_GPIO_Init(KEY_PORT, &GPIO_InitStructure);	
			
}


unsigned char keyscan(void)
{
	
    unsigned char temp;
	
	  temp=READ_A;        //A��
	  if(temp==0)      key_temp=VALUE_A;
	  else
		 {
	    temp=READ_B;      //B��
	    if(temp==0)    key_temp=VALUE_B;
      else{
			
			  temp=READ_C;      //C��
			  if(temp==0)    key_temp=VALUE_C;
			}			 
		 }

		switch(key_status)                  //����״̬��
		 {
			case key_unpress:                 //�����ɿ�״̬
						
					 if(temp==0)                  //��������
						{
				
							keycnt=1;                 //������ʼ
							key_status=key_press;     //���밴������״̬
						}  		
			break;

			case key_press:                   //��������״̬
				 
					 if(keycnt>20)                //20ms���ⰴ��״̬
						{				   
						 if(temp==0)                //���ǰ���״̬
							 {					   						    					   
								 key_flag=1;            //��λ���±�־										 
								 key_status=key_release;//���밴���ͷ�״̬			
								 keycnt=1;			       	//������1				
     							 
							 }
						else	                      //�Ѿ��ɿ�
							{
							
								keycnt=0;               //�رռ���
								key_status=key_unpress;	//�ص������ɿ�״̬	
         							
							}					   			 			 
						}
			break;

			case key_release:                 //�����ͷ�״̬
															
					 if(temp)                     //����
							 {
					     
								 keycnt=0;              //�رռ�����					 
								 key_status=key_unpress;//�ص������ɿ�״̬
								 key_flag=0;            //��λ���±�־
								 return key_temp;						//���ؼ�ֵ		
							 }	
					 
			break;

			default:
				
			break;	  	  
			}
  return 0;	 
}



















