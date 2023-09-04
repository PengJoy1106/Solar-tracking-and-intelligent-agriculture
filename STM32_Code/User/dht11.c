/*
�������ƣ�DHT11��ʪ�ȴ���������

����汾��V20170108
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
  unsigned char i;//ÿ��һ�ֽ�8λ
 
   volatile unsigned char temp;//volatile���������ñ�������ȥ�Ż���Ӧ����ֵ
    unsigned int timeout;
	
  for(i=0;i<8;i++)
	  { 
	    temp=0;//��������
	  	
		  timeout=50000;

	    while((READ_DHT11_PIN==0)&&(timeout>0))timeout--; //a�����俪ʼ��Data_Pin������50us������  
	  
	    delayus(80);    
	    
			if(READ_DHT11_PIN==1)//Data_Pin��DHT11����50us�����ߣ����ߵ�ʱ�����28us��Ϊ1���������70us�����ߵ�ʱ��С��28usΪ0��   
	       
			temp=1;
	    
		 timeout=50000; 
	    while((READ_DHT11_PIN==1)&&(timeout>0))timeout--;//���������һ����ʱ�䣬������aλ����ʱ����̫��
	    
	    datatemp<<=1;
	    datatemp|=temp;//��������λ����뻺��ֵ��
	  }       
  return datatemp;//�õ�һ���ֽں󽫺���ֵ����������
}



void DHT11_Read(void)
{           						

	  unsigned int timeout;
	
	  char temp_wendushi,temp_wenduge,temp_shidushi,temp_shiduge;

		

   	DHT11_PIN_OUT();DHT11_PIN_0;
			
			delayms(25);   //��������18��������         
				
			DHT11_PIN_1;
	
			DHT11_PIN_IN();	
			delayus(100);   //��������20us~40us
					 
			if(READ_DHT11_PIN==0)//����ӻ���Ӧ�󣬻�����Data_Pin���š�������Ӧ����ת��else�趨��Ĭ��ֵ��
					{	 			
						timeout=50000;
						while((READ_DHT11_PIN==0)&&(timeout>0))timeout--;//��Ӧ��ӻ�������80us������
							
						timeout=50000;
						while((READ_DHT11_PIN==1)&&(timeout>0))timeout--;//�ӻ�����80us������
													
						temp_hh=DHT11_ReadDataBit();//������һ�ֽ�Ϊʪ��8λ����������,�����Ӧ�Ļ�������
									
						temp_hl=DHT11_ReadDataBit();//�����ڶ��ֽ�Ϊʪ��8λ��С������,�����Ӧ�Ļ�������
							
						temp_th=DHT11_ReadDataBit();//���������ֽ�Ϊ�¶�8λ����������,�����Ӧ�Ļ�������
							
						temp_tl=DHT11_ReadDataBit();//���������ֽ�Ϊ�¶�8λ��С������,�����Ӧ�Ļ�������
							 
						Cheak_Data=DHT11_ReadDataBit();//���������ֽ�ΪУ��ͣ���ͨ������ʱ��У��͵�ֵ����ǰ���ĸ��ֽڵĺ͡�
											
						 /*У����ȷ�󣬽���������ֵ�����Ӧ�ı����С�*/
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
				else   /*��ȡʧ��Ĭ��ֵ*/   
					{
						//usart_sentstring(UART1,">>>READ_ERROR\r\n"); 				
					} 
}



void Show_DHT11(void)
{    
	 DHT11_Read();        //��ȡ��ʪ��ֵ

		 
	 printf(">>>��ǰ�����¶�=%d��\r\n",dht11_temperature);
   printf(">>>��ǰ����ʪ��=%d%RH\r\n",dht11_humidity);
	 
	 printf(">>>ͨ��RS485ͨ�Žӿڷ�����Ϣ���\r\n");
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





