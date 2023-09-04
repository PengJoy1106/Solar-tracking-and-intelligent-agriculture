/*********************
*
*�������ƣ�MH-Z19B������̼����������
*
*�������ڣ�2018.10.29
*
*���ߣ�������ͬѧ
*
*
*QQ��110644319
**********************/

#include "mhz19b.h"

unsigned int  value_co2=0; //co2Ũ��ֵ

unsigned char flag_get_co2;//co2Ũ�Ȼ�ȡ�ɹ���־λ

unsigned char index_co2;   //��ʼ��ָ��

unsigned char get_start_co2=0;//��ʼ��


/********************************
*
*������CO2����������
*
*UARTX��ѡ�񴮿�
*
*range:2000ppm��5000ppm��10000ppm������ѡ
*
*******************************/
void CO2_Config(unsigned char UARTX,unsigned int range)
{


	
		usart_sentdata(UARTX,0xFF);
		usart_sentdata(UARTX,0x01);
		usart_sentdata(UARTX,0x99);
	  usart_sentdata(UARTX,0x00);

		usart_sentdata(UARTX,0x00);
		usart_sentdata(UARTX,0x00);
	
	
	switch(range)
	{
		case 2000:
			
								usart_sentdata(UARTX,0x07);
								usart_sentdata(UARTX,0xd0);
								usart_sentdata(UARTX,0x8f);
		
		break;
	
		case 5000:
								usart_sentdata(UARTX,0x13);
								usart_sentdata(UARTX,0x88);
								usart_sentdata(UARTX,0xcb);
		break;	
	
		case 10000:
								usart_sentdata(UARTX,0x27);
								usart_sentdata(UARTX,0x10);
								usart_sentdata(UARTX,0x2f);
		break;	
	
		default:
								usart_sentdata(UARTX,0x13);
								usart_sentdata(UARTX,0x88);
								usart_sentdata(UARTX,0xcb);			
		
		break;
	}
	
}




/********************************
*
*������CO2������Ũ�Ȼ�ȡ
*
*UARTX��ѡ�񴮿�
*
*return:Ũ��ֵppm
*
*ע�⣬ʹ��ADC��ʽ��ȡŨ�ȣ�����ر��ʱ�������ݲ�����������ʹ��
*
*******************************/
unsigned int Get_CO2(unsigned char UARTX)
{
	
/***************ADC��ʽ��ȡŨ��*****************/	
//	float vo;
//	double c;
//	float avg_vo=0;
//	unsigned char i;
//	float max=0,min=5;
//				
//	for(i=0;i<5;i++){
//				
//		adc=ADC_Read(10); //�ڵ�1��2��ȼ��Ũ��ֵ
//							
//		vo=adc*3.3/4096;
//		if(max<vo)max=vo;
//		if(min>vo)min=vo;
//		printf("vo[%d]=%01f\r\n",i,vo);

//		
//		avg_vo+=vo;
//    delayms(10);							
//	}
//						
//		vo=(avg_vo-max-min)/3;
//						
//		printf("vo=%0.2f\r\n",vo);
//				
//		if(vo>0.4) c=(vo-0.4)*5000/1.6;
//		else       c=vo*5000/1.7;
//				
//		printf("\r\nco2=%0.2f\r\n",c);

/**********************END********************/

		if(flag_get_co2==1){
		
				 flag_get_co2=0;
				
				// printf("\r\nget co2\r\n");
				
				 value_co2=((rx_temp2[index_co2+1]<<8))+ rx_temp2[index_co2+2];
			
				 rx_index2=0;
				 
				 return value_co2;
	
		}else{
		
					usart_sentdata(UARTX,0xFF);
					usart_sentdata(UARTX,0x01);
					usart_sentdata(UARTX,0x86);
					
					usart_sentdata(UARTX,0x00);
					usart_sentdata(UARTX,0x00);
					usart_sentdata(UARTX,0x00);
					usart_sentdata(UARTX,0x00);
					usart_sentdata(UARTX,0x00);
					
					usart_sentdata(UARTX,0x79);			
		}
		
		return 0;


}




/********************************
*
*������CO2�����������жϴ�������
*
*���ö��󣺹������жϵ���
*
*******************************/
void Get_CO2_Interrupt(void)
{
		
	if(get_start_co2==0){ //δ�յ���ʼ��0XFF 0X86
			
			if(rx_index2>0){
				
				if( rx_temp2[rx_index2]==0x86 && rx_temp2[rx_index2-1]==0xFF){
					
					 get_start_co2=1;//��־�յ���ʼ��
					
					if(rx_index2<90)
					    index_co2 = rx_index2; //��¼��ʼ��ָ��
					else
           	get_start_co2=0;//����������棬�����ʼ��						
				}
			}
			
		}else{
		    
			 if(rx_index2>index_co2+1){//��ô��������� 
				 
				 get_start_co2=0;
				 
				 flag_get_co2=1;//��־������ݳɹ�				 
			 }
		}
}

