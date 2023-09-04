
#include "18b20.h"





double result_18b20;

unsigned char wendu_shi,wendu_ge;



void DS18B20_PIN_TURN(unsigned char status)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	
  if(status==1){ //out
		
			GPIO_InitStructure.Pin=DS18B20_PIN;             
			GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_PP;
			GPIO_InitStructure.Pull=GPIO_PULLUP;
			GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_HIGH;	
			HAL_GPIO_Init(SENSOR_PORT, &GPIO_InitStructure);			
	
	
	} 
	else{   //in
	
			GPIO_InitStructure.Pin=DS18B20_PIN;             
			GPIO_InitStructure.Mode=GPIO_MODE_INPUT;
			GPIO_InitStructure.Pull=GPIO_PULLUP;
			GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_HIGH;	
			HAL_GPIO_Init(SENSOR_PORT, &GPIO_InitStructure);			
	
	
	}
}



void delay_18b20(unsigned int z)//延时函数
{
	while(z--);
}

void rest_18b20(void)//复位
{	
	unsigned int jd;
	
	DS18B20_PIN_TURN(1);//输出
	
	DS18B20_1;
	delay_18b20(1000);
	DS18B20_0;
	delay_18b20(10000);
	DS18B20_1;
	
  DS18B20_PIN_TURN(0);//输入
	
	
	jd=5000;
	while(READ_DS18B20!=0&&jd!=0)//设置最大等待时间
		jd--;
	DS18B20_PIN_TURN(1);//输出
	delay_18b20(6000);//这里时间不能太短了
	
	DS18B20_1;
	
}

void txd_18b20(unsigned char mingling)//写数据
{
		unsigned char num;
	
	DS18B20_PIN_TURN(1);//输出

	DS18B20_1;delay_18b20(20);

	for(num=0;num<8;num++)
	{
     DS18B20_0;delay_18b20(20);

		if(mingling&0x01) DS18B20_1;
		else              DS18B20_0;

   		mingling>>=1;
		delay_18b20(300);
		DS18B20_1;delay_18b20(20);
	
	
	}		
}

unsigned char rxd_18b20(void)//读数据
{
	unsigned char num,dat;

	
	for(num=0;num<8;num++)
	{
		DS18B20_PIN_TURN(1);//输出
     DS18B20_0;delay_18b20(20);

		dat>>=1;
		
     DS18B20_1;delay_18b20(20);
		
     DS18B20_PIN_TURN(0);//输入
		
		if(READ_DS18B20==1)dat|=0x80;
			
		delay_18b20(2000);
	}
	return dat;
}

unsigned int DS18B20_GetTemp(void)//温度转换
{
	unsigned char jj,dk;
	unsigned int temp_ff=0;

	rest_18b20();//复位18b20
	
	txd_18b20(0xcc);//跳过读ROM
	txd_18b20(0x44);//启动温度转换//前三条指令执行需1.9ms
	
	delay_18b20(20000);//等待500us温度转换
	
	rest_18b20();//重新复位18b20
	txd_18b20(0xcc);//跳过读ROM
	txd_18b20(0xbe);//发送读RAM
	
	jj=rxd_18b20();//读低8位
	dk=rxd_18b20();//读高8位并把温度正副值的标志位清零
	
	temp_ff=dk;
	temp_ff<<=8;
	temp_ff|=jj;//合并高低八位

	return temp_ff;
}
void DS18B20_GET(void)
{
	double temp;
	  
	temp=0.0625*DS18B20_GetTemp(); //读取温度值 
	
	if(temp>150)printf("DS18B20 ERROR\r\n");
	else{
	   if(temp!=result_18b20){
		 
		    if(temp!=85) result_18b20=temp;
			  else{
					
			       if(result_18b20>80)result_18b20=temp;	
			  }
		 
		 }
	 }	
     //printf("result_18b20=%lf\r\n",result_18b20);
 	  // printf("result_18b20=%x\r\n",result_18b20);
}




