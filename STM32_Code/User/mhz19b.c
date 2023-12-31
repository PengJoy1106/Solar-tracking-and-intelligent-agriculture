/*********************
*
*驱动名称：MH-Z19B二氧化碳传感器驱动
*
*更新日期：2018.10.29
*
*作者：方方土同学
*
*
*QQ：110644319
**********************/

#include "mhz19b.h"

unsigned int  value_co2=0; //co2浓度值

unsigned char flag_get_co2;//co2浓度获取成功标志位

unsigned char index_co2;   //起始符指针

unsigned char get_start_co2=0;//起始符


/********************************
*
*函数：CO2传感器配置
*
*UARTX：选择串口
*
*range:2000ppm、5000ppm、10000ppm三挡可选
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
*函数：CO2传感器浓度获取
*
*UARTX：选择串口
*
*return:浓度值ppm
*
*注意，使用ADC方式获取浓度，误差特别大，时常有数据波动，不建议使用
*
*******************************/
unsigned int Get_CO2(unsigned char UARTX)
{
	
/***************ADC方式获取浓度*****************/	
//	float vo;
//	double c;
//	float avg_vo=0;
//	unsigned char i;
//	float max=0,min=5;
//				
//	for(i=0;i<5;i++){
//				
//		adc=ADC_Read(10); //节点1、2可燃气浓度值
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
*函数：CO2传感器串口中断处理函数
*
*调用对象：供串口中断调用
*
*******************************/
void Get_CO2_Interrupt(void)
{
		
	if(get_start_co2==0){ //未收到起始符0XFF 0X86
			
			if(rx_index2>0){
				
				if( rx_temp2[rx_index2]==0x86 && rx_temp2[rx_index2-1]==0xFF){
					
					 get_start_co2=1;//标志收到起始符
					
					if(rx_index2<90)
					    index_co2 = rx_index2; //记录起始符指针
					else
           	get_start_co2=0;//即将溢出缓存，清除起始符						
				}
			}
			
		}else{
		    
			 if(rx_index2>index_co2+1){//获得传感器数据 
				 
				 get_start_co2=0;
				 
				 flag_get_co2=1;//标志获得数据成功				 
			 }
		}
}


