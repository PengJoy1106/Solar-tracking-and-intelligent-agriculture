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
	
	  temp=READ_A;        //A键
	  if(temp==0)      key_temp=VALUE_A;
	  else
		 {
	    temp=READ_B;      //B键
	    if(temp==0)    key_temp=VALUE_B;
      else{
			
			  temp=READ_C;      //C键
			  if(temp==0)    key_temp=VALUE_C;
			}			 
		 }

		switch(key_status)                  //按键状态机
		 {
			case key_unpress:                 //按键松开状态
						
					 if(temp==0)                  //按键按下
						{
				
							keycnt=1;                 //计数开始
							key_status=key_press;     //进入按键按下状态
						}  		
			break;

			case key_press:                   //按键按下状态
				 
					 if(keycnt>20)                //20ms后检测按键状态
						{				   
						 if(temp==0)                //还是按下状态
							 {					   						    					   
								 key_flag=1;            //置位按下标志										 
								 key_status=key_release;//进入按键释放状态			
								 keycnt=1;			       	//计数回1				
     							 
							 }
						else	                      //已经松开
							{
							
								keycnt=0;               //关闭计数
								key_status=key_unpress;	//回到按键松开状态	
         							
							}					   			 			 
						}
			break;

			case key_release:                 //按键释放状态
															
					 if(temp)                     //松手
							 {
					     
								 keycnt=0;              //关闭计数器					 
								 key_status=key_unpress;//回到按键松开状态
								 key_flag=0;            //复位按下标志
								 return key_temp;						//返回键值		
							 }	
					 
			break;

			default:
				
			break;	  	  
			}
  return 0;	 
}




















