/*
程序名称：DHT11温湿度传感器驱动

软件版本：V20170108
*/


#include "dht11.h"

volatile unsigned int dht11_temperature,dht11_humidity;

unsigned int datatemp;

static unsigned char shidu_shi,shidu_ge,wendu_shi,wendu_ge;

char temp_hl,temp_hh, temp_th, temp_tl,Cheak_Data;




static void delayus(uint16_t time)
{    
   uint16_t i;  
   uint8_t j;
	
	for(i=0;i<time;i++)
	 {
		 for(j=12;i<time;i++)
		 {	  
			 __NOP();	__NOP();__NOP();__NOP();	 
		 }	 
	 }
}


static int DHT11_ReadDataBit(void)
{
  unsigned char i;//每读一字节8位
 
   volatile unsigned char temp;//volatile声明可以让编译器不去优化对应变量值
    unsigned int timeout;
	
  for(i=0;i<8;i++)
	  { 
	    temp=0;//缓存清零
	  	
		  timeout=50000;

	    while((READ_DHT11_PIN==0)&&(timeout>0))timeout--; //a：传输开始，Data_Pin被拉低50us后拉高  
	  
	    delayus(80);    
	    
			if(READ_DHT11_PIN==1)//Data_Pin被DHT11拉低50us后拉高，拉高的时间大于28us即为1并会持续到70us，拉高的时间小于28us为0。   
	       
			temp=1;
	    
		 timeout=50000; 
	    while((READ_DHT11_PIN==1)&&(timeout>0))timeout--;//这里会消耗一部分时间，决定了a位置延时不能太大。
	    
	    datatemp<<=1;
	    datatemp|=temp;//将变量移位后存入缓存值。
	  }       
  return datatemp;//得到一个字节后将函数值赋给函数。
}



void DHT11_Read(void)
{           						

	  unsigned int timeout;
	
	  char temp_wendushi,temp_wenduge,temp_shidushi,temp_shiduge;

		

   	DHT11_PIN_OUT();DHT11_PIN_0;
			
			delayms(25);   //主机拉低18毫秒以上         
				
			DHT11_PIN_1;
	
			DHT11_PIN_IN();	
			delayus(100);   //主机拉高20us~40us
					 
			if(READ_DHT11_PIN==0)//如果从机响应后，会拉低Data_Pin引脚。若不响应则跳转到else设定的默认值。
					{	 			
						timeout=50000;
						while((READ_DHT11_PIN==0)&&(timeout>0))timeout--;//响应后从机将拉低80us后拉高
							
						timeout=50000;
						while((READ_DHT11_PIN==1)&&(timeout>0))timeout--;//从机拉高80us将拉低
													
						temp_hh=DHT11_ReadDataBit();//读到第一字节为湿度8位的整数部分,存入对应的缓存区。
									
						temp_hl=DHT11_ReadDataBit();//读到第二字节为湿度8位的小数部分,存入对应的缓存区。
							
						temp_th=DHT11_ReadDataBit();//读到第三字节为温度8位的整数部分,存入对应的缓存区。
							
						temp_tl=DHT11_ReadDataBit();//读到第四字节为温度8位的小数部分,存入对应的缓存区。
							 
						Cheak_Data=DHT11_ReadDataBit();//读到第五字节为校验和，当通信无误时，校验和的值等于前面四个字节的和。
											
						 /*校验正确后，将缓存区的值载入对应的变量中。*/
						 if(temp_hh+temp_hl+temp_th+temp_tl==Cheak_Data)
							 {               
									temp_wendushi=temp_th/10; 
									temp_wenduge=temp_th%10;	              				  				 				  				      
									temp_shidushi=temp_hh/10; 
									temp_shiduge=temp_hh%10;

								  dht11_temperature=(10*temp_wendushi+temp_wenduge);
								  dht11_humidity=(10*temp_shidushi+temp_shiduge);		 
							 }
              else
							{
							 // usart_sentstring(UART1,">>>TRANS_ERROR\r\n");
						
							}								
					}    
				else   /*读取失败默认值*/   
					{
						//usart_sentstring(UART1,">>>READ_ERROR\r\n"); 				
					} 
}



void Show_DHT11(void)
{    
	 DHT11_Read();        //读取温湿度值

		 
	 printf(">>>当前环境温度=%d℃\r\n",dht11_temperature);
   printf(">>>当前环境湿度=%d%RH\r\n",dht11_humidity);
	 
	 printf(">>>通过RS485通信接口发送信息完成\r\n");
}



void DHT11_OLED_display(void)
{		   	 	   	
	OLED_P8x16(48,2,&num[wendu_shi]);
	OLED_P8x16(56,2,&num[wendu_ge]);
	
	OLED_P8x16(48,6,&num[shidu_shi]);
	OLED_P8x16(56,6,&num[shidu_ge]);				
}




void DHT11_PIN_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.Pin=DHT11_PIN;
	GPIO_InitStructure.Mode=GPIO_MODE_INPUT;
	GPIO_InitStructure.Pull=GPIO_NOPULL;
	GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_HIGH;	
	HAL_GPIO_Init(DHT11_PORT, &GPIO_InitStructure);	

}

void DHT11_PIN_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.Pin=DHT11_PIN;
	GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Pull=GPIO_PULLUP;
	GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_HIGH;	
	HAL_GPIO_Init(DHT11_PORT, &GPIO_InitStructure);	

}





