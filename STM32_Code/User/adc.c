#include "adc.h"
#include "gpio.h"


ADC_HandleTypeDef             ADC_Handle;
ADC_ChannelConfTypeDef        ADC_Channel_Config;
uint32_t                      ADC_Result;
unsigned short                cnt_adc;
unsigned char bad_adc=0;





//void ADC_Config(void)
//{
//   GPIO_InitTypeDef          GPIO_InitStruct;
//	 static DMA_HandleTypeDef         dmaHandle;
//  
//  __HAL_RCC_GPIOA_CLK_ENABLE();
//  __HAL_RCC_ADC1_CLK_ENABLE();
// 
//	//__HAL_RCC_DMA1_CLK_ENABLE();  
//  /*##- 2- Configure peripheral GPIO #########################################*/
//  /* ADC1 Channel0 GPIO pin configuration */	
//  GPIO_InitStruct.Pin = GPIO_PIN_3;
//  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
////  
////  /*##- 3- Configure DMA #####################################################*/ 

////  /*********************** Configure DMA parameters ***************************/
////  dmaHandle.Instance                 = DMA1_Channel1;
////  dmaHandle.Init.Direction           = DMA_PERIPH_TO_MEMORY;
////  dmaHandle.Init.PeriphInc           = DMA_PINC_DISABLE;
////  dmaHandle.Init.MemInc              = DMA_MINC_ENABLE;
////  dmaHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
////  dmaHandle.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;
////  dmaHandle.Init.Mode                = DMA_CIRCULAR;
////  dmaHandle.Init.Priority            = DMA_PRIORITY_MEDIUM;
////  
////  /* Deinitialize  & Initialize the DMA for new transfer */
////  HAL_DMA_DeInit(&dmaHandle);  
////  HAL_DMA_Init(&dmaHandle);
////  
////  /* Associate the DMA handle */
////	__HAL_LINKDMA(&ADC_Handle, DMA_Handle, dmaHandle);
////  
////  /* NVIC configuration for DMA Input data interrupt */
////  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 3, 0);
////  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn); 
//		
//	ADC_Handle.Instance = ADC1;
//  ADC_Handle.Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV4;
//  ADC_Handle.Init.LowPowerAutoWait      = DISABLE;
//  ADC_Handle.Init.LowPowerAutoPowerOff  = DISABLE;
//  ADC_Handle.Init.Resolution            = ADC_RESOLUTION_12B;
//  ADC_Handle.Init.ScanConvMode          = ADC_SCAN_ENABLE;
//  ADC_Handle.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
//  ADC_Handle.Init.ContinuousConvMode    = ENABLE;
//  ADC_Handle.Init.DiscontinuousConvMode = DISABLE;
//  ADC_Handle.Init.ExternalTrigConv      = ADC_SOFTWARE_START;
//  ADC_Handle.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;
//  ADC_Handle.Init.EOCSelection          = ADC_EOC_SINGLE_CONV;
//  ADC_Handle.Init.DMAContinuousRequests = ENABLE;
//  ADC_Handle.Init.Overrun               = ADC_OVR_DATA_OVERWRITTEN;
// 
//  /* Initialize ADC peripheral according to the passed parameters */
//  HAL_ADC_Init(&ADC_Handle); 
//  /* ### - 2 - Start calibration ############################################ */
//  HAL_ADCEx_Calibration_Start(&ADC_Handle);

//  /* ### - 3 - Channel configuration ######################################## */
//  /* Select Channel 0 to be converted */
//  ADC_Channel_Config.Channel      = ADC_CHANNEL_3;
//  ADC_Channel_Config.Rank         = ADC_RANK_CHANNEL_NUMBER;
//  ADC_Channel_Config.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
//  HAL_ADC_ConfigChannel(&ADC_Handle, &ADC_Channel_Config);

// /* ### - 4 - Start conversion in DMA mode ################################# */
// //  HAL_ADC_Start_DMA(&ADC_Handle, &ADC_Result, 1);
//}

//uint16_t ADC_Read(uint32_t timeout)
//{
//  uint32_t pwr_vol = 0;
//  /* ADC???? */
//  HAL_ADC_Start(&ADC_Handle);
//   //  HAL_ADC_Start_DMA(&ADC_Handle,&ADC_Result,1);
//    // HAL_ADC_Stop_DMA(&ADC_Handle);
//  /* ?????? */
//   HAL_ADC_PollForConversion(&ADC_Handle, timeout);

//  /* ??ADC? */
//  pwr_vol = HAL_ADC_GetValue(&ADC_Handle);

//  /* ADC???? */
//  HAL_ADC_Stop(&ADC_Handle);

//  return (uint16_t)pwr_vol;
//}





unsigned short  cnt_adc;

unsigned char light,soil,mq7;



ADC_HandleTypeDef             ADC_Handle;

ADC_ChannelConfTypeDef        ADC_Channel_Config;

uint32_t                      ADC_Result;


void ADC_Config(void)
{
   GPIO_InitTypeDef          GPIO_InitStruct;
	 static DMA_HandleTypeDef         dmaHandle;
  
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_ADC1_CLK_ENABLE();

  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		
	ADC_Handle.Instance = ADC1;
  ADC_Handle.Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV4;
  ADC_Handle.Init.LowPowerAutoWait      = DISABLE;
  ADC_Handle.Init.LowPowerAutoPowerOff  = DISABLE;
  ADC_Handle.Init.Resolution            = ADC_RESOLUTION_12B;
  ADC_Handle.Init.ScanConvMode          = ADC_SCAN_ENABLE;
  ADC_Handle.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
  ADC_Handle.Init.ContinuousConvMode    = DISABLE;
  ADC_Handle.Init.DiscontinuousConvMode = ENABLE;
  ADC_Handle.Init.ExternalTrigConv      = ADC_SOFTWARE_START;
  ADC_Handle.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;
  ADC_Handle.Init.EOCSelection          = ADC_EOC_SINGLE_CONV;
  ADC_Handle.Init.DMAContinuousRequests = DISABLE;
  ADC_Handle.Init.Overrun               = ADC_OVR_DATA_OVERWRITTEN;
  /* Initialize ADC peripheral according to the passed parameters */
  HAL_ADC_Init(&ADC_Handle); 
	

  HAL_ADCEx_Calibration_Start(&ADC_Handle);


  ADC_Channel_Config.Channel      = ADC_CHANNEL_2;
  ADC_Channel_Config.Rank         = 1;
  ADC_Channel_Config.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  HAL_ADC_ConfigChannel(&ADC_Handle, &ADC_Channel_Config);
	
	
  ADC_Channel_Config.Channel      = ADC_CHANNEL_4;
  ADC_Channel_Config.Rank         = 2;
  ADC_Channel_Config.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  HAL_ADC_ConfigChannel(&ADC_Handle, &ADC_Channel_Config);	
	
//  ADC_Channel_Config.Channel      = ADC_CHANNEL_4;
//  ADC_Channel_Config.Rank         = 3;
//  ADC_Channel_Config.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
//  HAL_ADC_ConfigChannel(&ADC_Handle, &ADC_Channel_Config);		

}

uint16_t ADC_Read(uint32_t timeout)
{
  uint32_t pwr_vol = 0;

  HAL_ADC_Start(&ADC_Handle);

  HAL_ADC_PollForConversion(&ADC_Handle, timeout);

  pwr_vol = HAL_ADC_GetValue(&ADC_Handle);
  
//printf("ADC=%d\r\n",pwr_vol);

  HAL_ADC_Stop(&ADC_Handle);

  return (uint16_t)pwr_vol;
}


uint16_t ADC_Read_N(unsigned char timeout)
{
  uint32_t pwr_vol = 0;

	
	HAL_ADC_Start(&ADC_Handle);	
	HAL_ADC_PollForConversion(&ADC_Handle, timeout);
	pwr_vol = HAL_ADC_GetValue(&ADC_Handle);
	//printf("ADC4=%d\r\n",pwr_vol);
	soil=100-pwr_vol*100/4096;



	HAL_ADC_Start(&ADC_Handle);
	HAL_ADC_PollForConversion(&ADC_Handle, 20);
	pwr_vol = HAL_ADC_GetValue(&ADC_Handle);
	//printf("ADC3=%d\r\n",pwr_vol);	 
	light=100-pwr_vol*100/4096;


	if(light>99)light=99;
	if(soil>99)soil=99;



	HAL_ADC_Stop(&ADC_Handle);

  return (uint16_t)pwr_vol;
}
