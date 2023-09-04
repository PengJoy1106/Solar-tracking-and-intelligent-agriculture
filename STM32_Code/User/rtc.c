#include "rtc.h"
#include "usart.h"

RTC_HandleTypeDef RTC_Handle;

#define RTC_CLOCK_SOURCE_LSE

#ifdef RTC_CLOCK_SOURCE_LSI //ʹ���ڲ�����
#define RTC_ASYNCH_PREDIV    0x7F
#define RTC_SYNCH_PREDIV     0x0130
#endif

#ifdef RTC_CLOCK_SOURCE_LSE //ʹ���ⲿ����
#define RTC_ASYNCH_PREDIV  0x7F
#define RTC_SYNCH_PREDIV   0x00FF
#endif

/***********RTC����************/
void RTC_Config(void)
	{
		RCC_OscInitTypeDef        RCC_OscInitStruct;
		RCC_PeriphCLKInitTypeDef  PeriphClkInitStruct;

		 __HAL_RCC_PWR_CLK_ENABLE();//�л�RTCʱ��Դ��Ҫ����PWR
		 HAL_PWR_EnableBkUpAccess();//������ʱ�����

		RCC_OscInitStruct.OscillatorType =  RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_LSE;//32K��������ѡ��
		RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;//��ʹ�����໷
		RCC_OscInitStruct.LSEState = RCC_LSE_ON;//���ⲿ32K����
		RCC_OscInitStruct.LSIState = RCC_LSI_OFF;//���ڲ�32K����
		HAL_RCC_OscConfig(&RCC_OscInitStruct);//�������
	 
		PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;//����ʱ��Դѡ��
		PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;//RTCѡ���ⲿ32K ����
		HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);//�������
	
		/* Configure RTC prescaler and RTC data registers */
		/* RTC configured as follows:
				- Hour Format    = Format 24                      
				- Asynch Prediv  = Value according to source clock   
				- Synch Prediv   = Value according to source clock
				- OutPut         = Output Disable
				- OutPutPolarity = High Polarity
				- OutPutType     = Open Drain */
		__HAL_RCC_RTC_ENABLE();            //ʱ��������ɺ󣬿�RTCʱ��
		RTC_Handle.Instance = RTC;		
		RTC_Handle.Init.HourFormat     = RTC_HOURFORMAT_24;         //24Сʱ��
		RTC_Handle.Init.AsynchPrediv   = RTC_ASYNCH_PREDIV;         //�첽Ԥ��Ƶֵ
		RTC_Handle.Init.SynchPrediv    = RTC_SYNCH_PREDIV;          //ͬ��Ԥ��Ƶֵ
		RTC_Handle.Init.OutPut         = RTC_OUTPUT_DISABLE;        //�ر�ʱ�����
		RTC_Handle.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
		RTC_Handle.Init.OutPutType     = RTC_OUTPUT_TYPE_OPENDRAIN;  
		HAL_RTC_Init(&RTC_Handle);
			
		HAL_NVIC_SetPriority(RTC_IRQn, 0x0F, 0);//����RTC�ж�
		HAL_NVIC_EnableIRQ(RTC_IRQn);
	 
	  RTC_AlarmConfig();//����ʱ��������	
	}

	
	/****************���塢ʱ������*******************/
void RTC_AlarmConfig(void)
	{
		RTC_DateTypeDef  RTC_Date;//���ڽṹ��
		RTC_TimeTypeDef  RTC_Time;//ʱ��ṹ��
		RTC_AlarmTypeDef RTC_Alarm1;//���ӽṹ��

		if(RTC_Time.StoreOperation  != RTC_STOREOPERATION_SET)//���û�����ù�ʱ��	
			{	 
				/***********-1- Configure the Date ********/
				RTC_Date.Year = 0x16;                   //      16��
				RTC_Date.Month = 0x11;                     //     11��
				RTC_Date.Date = 0x11;                   //      11��
				RTC_Date.WeekDay = 0x05;                  //     ����5
				HAL_RTC_SetDate(&RTC_Handle,&RTC_Date,RTC_FORMAT_BCD);//BCD��ʽ����			
				
				/************-2- Configure the Time *******/
				/* Set Time: 13:00:00 */
				RTC_Time.Hours = 0x13;                              //   02Сʱ
				RTC_Time.Minutes = 0x00;                            //   20����
				RTC_Time.Seconds = 0x00;                            //   00��
				RTC_Time.TimeFormat = RTC_HOURFORMAT12_AM;          //   ����12��
				RTC_Time.DayLightSaving = RTC_DAYLIGHTSAVING_NONE ; //Сʱ����ֵ
				RTC_Time.StoreOperation = RTC_STOREOPERATION_SET;   //ʱ�临λ��־
				HAL_RTC_SetTime(&RTC_Handle,&RTC_Time,RTC_FORMAT_BCD);  
			}
			
		/****-3- Configure the RTC Alarm peripheral****/
		/* Set Alarm to 02:20:30 
			 RTC Alarm Generation: Alarm on Hours, Minutes and Seconds */
		RTC_Alarm1.Alarm = RTC_ALARM_A;
		RTC_Alarm1.AlarmDateWeekDay = RTC_WEEKDAY_MONDAY;
		RTC_Alarm1.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;//���ӻ������������������
		RTC_Alarm1.AlarmMask = RTC_ALARMMASK_DATEWEEKDAY;             //�����������ɾ������
		RTC_Alarm1.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_NONE;   
		RTC_Alarm1.AlarmTime.TimeFormat = RTC_HOURFORMAT12_AM;        //12Сʱ��
		RTC_Alarm1.AlarmTime.Hours = 0x13;
		RTC_Alarm1.AlarmTime.Minutes = 0x00;
		RTC_Alarm1.AlarmTime.Seconds = 0x30;
		RTC_Alarm1.AlarmTime.SubSeconds = 0x56;		
		HAL_RTC_SetAlarm_IT(&RTC_Handle,&RTC_Alarm1,RTC_FORMAT_BCD);		
	}

void RTC_TimeShow()//������ʾ����ʱ��
{
  RTC_DateTypeDef RTC_Date;
  RTC_TimeTypeDef RTC_Time;
  
  /* Get the RTC current Time */
  HAL_RTC_GetTime(&RTC_Handle, &RTC_Time, RTC_FORMAT_BIN);
  /* Get the RTC current Date */
  HAL_RTC_GetDate(&RTC_Handle, &RTC_Date, RTC_FORMAT_BIN);
  /* Display time Format : hh:mm:ss */
  printf("20%02d-%02d-%02d ����%d\r\n",RTC_Date.Year, RTC_Date.Month, RTC_Date.Date,RTC_Date.WeekDay);
	printf("%02d:%02d:%02d\r\n",RTC_Time.Hours, RTC_Time.Minutes, RTC_Time.Seconds);
} 

/***********RTC���ӻص�����*************/
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *RTC_Handle)
	{		
    usart_sentstring("������\r\n");
	}

