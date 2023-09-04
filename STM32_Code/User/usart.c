#include "usart.h"



uint8_t rx_temp[100],uart_temp[10];

uint8_t rx_update,rx_flag=1;

uint16_t rx_index,rx_cnt;

uint16_t rx_index2;

unsigned char rx_temp2[100];





UART_HandleTypeDef UART1_Handle;
UART_HandleTypeDef UART2_Handle;


void Usart1_Config(void)
{ 	
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_PeriphCLKInitTypeDef PeriphClkInit;	
	
	__HAL_RCC_USART1_CLK_ENABLE();
	
	__HAL_RCC_GPIOA_CLK_ENABLE();//开PA口时钟
	
	/*GPIO配置*/
	GPIO_InitStruct.Pin = RXD1|TXD1;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF1_USART1;
	HAL_GPIO_Init(UART1_PORT, &GPIO_InitStruct);
	
	/*时钟配置*/
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;	
	PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
	HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);
	
	/*UART结构体配置*/
 // UART_Handle.gState=HAL_UART_STATE_RESET;
	UART1_Handle.Instance = USART1;
  UART1_Handle.Init.BaudRate = 9600;
  UART1_Handle.Init.WordLength = UART_WORDLENGTH_8B;
  UART1_Handle.Init.StopBits = UART_STOPBITS_1;
  UART1_Handle.Init.Parity = UART_PARITY_NONE;
  UART1_Handle.Init.Mode = UART_MODE_TX_RX;
  UART1_Handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  UART1_Handle.Init.OverSampling = UART_OVERSAMPLING_16;
  UART1_Handle.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  UART1_Handle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;  
	HAL_UART_Init(&UART1_Handle);
	
	/*DMA收发初始化*/
	UART_DMA_Config(&UART1_Handle);//DMA初始化配置	
	HAL_UART_Receive_DMA(&UART1_Handle,uart_temp,1);    //DMA中断接收初始化，接收到一个字节中断一次
	//HAL_UART_Transmit_DMA(&UART1_Handle,uart_temp,1);   //DMA中断发送初始化，发送一个字节中断一次	
	
	/*UART中断优先级*/
  HAL_NVIC_SetPriority(USART1_IRQn, 0, 1);//UART中断优先级设置
	HAL_NVIC_EnableIRQ(USART1_IRQn);//启用UART2中断	
	
	usart_sentstring(UART1,"USART1 Config is ok\r\n");	

}


static void UART_DMA_Config(UART_HandleTypeDef *huart)
{
  static DMA_HandleTypeDef hdma_tx;
  static DMA_HandleTypeDef hdma_rx;

  /* Enable DMA clock */
  __HAL_RCC_DMA1_CLK_ENABLE();
  
  hdma_tx.Instance                 = DMA1_Channel2;
  hdma_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
  hdma_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
  hdma_tx.Init.MemInc              = DMA_MINC_ENABLE;
  hdma_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdma_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
  hdma_tx.Init.Mode                = DMA_NORMAL;
  hdma_tx.Init.Priority            = DMA_PRIORITY_LOW;
  HAL_DMA_Init(&hdma_tx);
  __HAL_LINKDMA(huart, hdmatx, hdma_tx);

  hdma_rx.Instance                 = DMA1_Channel3;
  hdma_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
  hdma_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
  hdma_rx.Init.MemInc              = DMA_MINC_ENABLE;
  hdma_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdma_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
  hdma_rx.Init.Mode                = DMA_NORMAL;
  hdma_rx.Init.Priority            = DMA_PRIORITY_HIGH;
  HAL_DMA_Init(&hdma_rx);
  __HAL_LINKDMA(huart, hdmarx, hdma_rx);
       
  HAL_NVIC_SetPriority(DMA1_Channel2_3_IRQn, 0, 1);
  HAL_NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);
}


void Usart2_Config(void)
{ 	
	GPIO_InitTypeDef GPIO_InitStruct;


	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();//开PA口时钟
	
	
	
	/*GPIO配置*/
	GPIO_InitStruct.Pin = RXD2|TXD2;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF1_USART2;
	HAL_GPIO_Init(UART2_PORT, &GPIO_InitStruct);	

	
	UART2_Handle.Instance = USART2;
  UART2_Handle.Init.BaudRate = 115200;
  UART2_Handle.Init.WordLength = UART_WORDLENGTH_8B;
  UART2_Handle.Init.StopBits = UART_STOPBITS_1;
  UART2_Handle.Init.Parity = UART_PARITY_NONE;
  UART2_Handle.Init.Mode = UART_MODE_TX_RX;
  UART2_Handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  UART2_Handle.Init.OverSampling = UART_OVERSAMPLING_16;
  UART2_Handle.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  UART2_Handle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;  
	HAL_UART_Init(&UART2_Handle);

	/*UART中断收发初始化*/
  HAL_UART_Receive_IT(&UART2_Handle,uart_temp,1);   //中断接收初始化，接收到一个字节中断一次			
  HAL_UART_Transmit_IT(&UART2_Handle,uart_temp,1);  //中断发送初始化，发送一个字节中断一次	 
		
  HAL_NVIC_SetPriority(USART2_IRQn, 0, 2);//UART中断优先级设置
	HAL_NVIC_EnableIRQ(USART2_IRQn);//启用UART2中断			
	
	usart_sentstring(UART2,"USART2 Config is ok\r\n");		
}

void Usart_Config(void)
{
	Usart1_Config();
	Usart2_Config();
}




/**********************串口中断回调函数******************************/
//TX发送完成中断回调函数
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{

}	

//RX接收中断回调函数
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{			
		
	
	   if(huart==&UART1_Handle){
				 	 
			 rx_temp2[rx_index2]=(uint8_t)(UART1_Handle.Instance->RDR);

	 

			 rx_index2++;if(rx_index2>99) rx_index2=0;
		 }
		 
		 
		if(huart==&UART2_Handle){
				 
			 
			 rx_temp[rx_index]=(uint8_t)(UART2_Handle.Instance->RDR);					
			
			 esp8266_usart_isr(); 
				 
				 
//			 if(rx_index>0){	
//				 
//				if(rx_temp[rx_index]=='\n'&&rx_temp[rx_index-1]=='\r')//收到结束符
//					 {  
//						 
//						 rx_update=1;
//						 rx_flag=0;	
//						 
//					 }
//			 }
			 
			 if(rx_update==0){rx_index++;if(rx_index>99) rx_index=0;	}
			
		 }
			 

	 HAL_UART_Receive_IT(&UART2_Handle,uart_temp,1); 
   HAL_UART_Receive_DMA(&UART1_Handle,uart_temp,1); //DMA接收初始化	
}

/**************************串口打印重定向函数***************************/
int fputc(int ch, FILE *f)
{

	
	while(__HAL_UART_GET_FLAG(&UART2_Handle, UART_FLAG_TC) == RESET);//TI=0;

	UART2_Handle.Instance->TDR = (uint8_t)ch;
	
	
//	while(__HAL_UART_GET_FLAG(&UART1_Handle, UART_FLAG_TC) == RESET);//TI=0;

//	UART1_Handle.Instance->TDR = (uint8_t)ch;	
  	
	return ch;
}


void usart_sentdata(unsigned char uart,unsigned char ch)
{
	
	switch(uart)
	{
		case UART1:
	
			while(__HAL_UART_GET_FLAG(&UART1_Handle, UART_FLAG_TC) == RESET);//TI=0;

			UART1_Handle.Instance->TDR = (int8_t)ch;
		
	  break;
		
		case UART2:
	
			while(__HAL_UART_GET_FLAG(&UART2_Handle, UART_FLAG_TC) == RESET);//TI=0;

			UART2_Handle.Instance->TDR = (int8_t)ch;
		
	  break;		
		
	}
	
}


void usart_sentstring(unsigned char uart,uint8_t *s)
{
		while(*s)
		{
			usart_sentdata(uart,*s++);
		}
}




/***************************
* @brief   字符串包含比较，包含返回指针数，否则返回0
* @paramtx_str1:     字符串1
* @param   str2：    字符串2
****************************/
 unsigned char *str2str(const unsigned char *str1, const unsigned char *str2)
{
    unsigned char *cp = (unsigned char*)str1;
    unsigned char *s1, *s2;
 
    if (!*str2)
        return((unsigned char *)str1);
 
    while (*cp)
      {
        s1 = cp;
        s2 = (unsigned char *)str2;
 
        while (*s1 && *s2 && !(*s1 - *s2))
            s1++, s2++;
 
        if (!*s2)
            return(cp);
 
        cp++;
      }
    return(NULL);
}
/************************************************/




/***************************
* @brief   指定数组长度并清空缓存
* @paramtx_buffer:     缓存所在数组
* @param   len：       指定清空长度
****************************/
void wipe_buffer(unsigned char* buffer,unsigned short len)
{
unsigned short i;
	
	for(i=0;i<len;i++)
	{
	 *buffer=0;	
		buffer++;
	}
}
/************************************************/









