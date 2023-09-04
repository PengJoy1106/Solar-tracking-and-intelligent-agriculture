#include "rtc.h"
#include "usart.h"

RTC_HandleTypeDef RTC_Handle;

#define RTC_CLOCK_SOURCE_LSE

#ifdef RTC_CLOCK_SOURCE_LSI //使用内部晶振
#define RTC_ASYNCH_PREDIV    0x7F
#define RTC_SYNCH_PREDIV     0x0130
#endif

#ifdef RTC_CLOCK_SOURCE_LSE //使用外部晶振
#define RTC_ASYNCH_PREDIV  0x7F
#define RTC_SYNCH_PREDIV   0x00FF
#endif

/***********RTC配置************/
void RTC_Config(void)
	{
		RCC_OscInitTypeDef        RCC_OscInitStruct;
		RCC_PeriphCLKInitTypeDef  PeriphClkInitStruct;

		 __HAL_RCC_PWR_CLK_ENABLE();//切换RTC时钟源需要开启PWR
		 HAL_PWR_EnableBkUpAccess();//允许访问备用域

		RCC_OscInitStruct.OscillatorType =  RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_LSE;//32K晶振类型选择
		RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;//不使用锁相环
		RCC_OscInitStruct.LSEState = RCC_LSE_ON;//开外部32K晶振
		RCC_OscInitStruct.LSIState = RCC_LSI_OFF;//关内部32K晶振
		HAL_RCC_OscConfig(&RCC_OscInitStruct);//载入参数
	 
		PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;//外设时钟源选择
		PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;//RTC选择外部32K 晶振
		HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);//载入参数
	
		/* Configure RTC prescaler and RTC data registers */
		/* RTC configured as follows:
				- Hour Format    = Format 24                      
				- Asynch Prediv  = Value according to source clock   
				- Synch Prediv   = Value according to source clock
				- OutPut         = Output Disable
				- OutPutPolarity = High Polarity
				- OutPutType     = Open Drain */
		__HAL_RCC_RTC_ENABLE();            //时钟配置完成后，开RTC时钟
		RTC_Handle.Instance = RTC;		
		RTC_Handle.Init.HourFormat     = RTC_HOURFORMAT_24;         //24小时制
		RTC_Handle.Init.AsynchPrediv   = RTC_ASYNCH_PREDIV;         //异步预分频值
		RTC_Handle.Init.SynchPrediv    = RTC_SYNCH_PREDIV;          //同步预分频值
		RTC_Handle.Init.OutPut         = RTC_OUTPUT_DISABLE;        //关闭时钟输出
		RTC_Handle.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
		RTC_Handle.Init.OutPutType     = RTC_OUTPUT_TYPE_OPENDRAIN;  
		HAL_RTC_Init(&RTC_Handle);
			
		HAL_NVIC_SetPriority(RTC_IRQn, 0x0F, 0);//开启RTC中断
		HAL_NVIC_EnableIRQ(RTC_IRQn);
	 
	  RTC_AlarmConfig();//设置时间与闹钟	
	}

	
	/****************闹铃、时间设置*******************/
void RTC_AlarmConfig(void)
	{
		RTC_DateTypeDef  RTC_Date;//日期结构体
		RTC_TimeTypeDef  RTC_Time;//时间结构体
		RTC_AlarmTypeDef RTC_Alarm1;//闹钟结构体

		if(RTC_Time.StoreOperation  != RTC_STOREOPERATION_SET)//如果没有设置过时间	
			{	 
				/***********-1- Configure the Date ********/
				RTC_Date.Year = 0x16;                   //      16年
				RTC_Date.Month = 0x11;                     //     11月
				RTC_Date.Date = 0x11;                   //      11日
				RTC_Date.WeekDay = 0x05;                  //     星期5
				HAL_RTC_SetDate(&RTC_Handle,&RTC_Date,RTC_FORMAT_BCD);//BCD格式载入			
				
				/************-2- Configure the Time *******/
				/* Set Time: 13:00:00 */
				RTC_Time.Hours = 0x13;                              //   02小时
				RTC_Time.Minutes = 0x00;                            //   20分钟
				RTC_Time.Seconds = 0x00;                            //   00秒
				RTC_Time.TimeFormat = RTC_HOURFORMAT12_AM;          //   上午12点
				RTC_Time.DayLightSaving = RTC_DAYLIGHTSAVING_NONE ; //小时调整值
				RTC_Time.StoreOperation = RTC_STOREOPERATION_SET;   //时间复位标志
				HAL_RTC_SetTime(&RTC_Handle,&RTC_Time,RTC_FORMAT_BCD);  
			}
			
		/****-3- Configure the RTC Alarm peripheral****/
		/* Set Alarm to 02:20:30 
			 RTC Alarm Generation: Alarm on Hours, Minutes and Seconds */
		RTC_Alarm1.Alarm = RTC_ALARM_A;
		RTC_Alarm1.AlarmDateWeekDay = RTC_WEEKDAY_MONDAY;
		RTC_Alarm1.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;//闹钟基于日期响铃而非星期
		RTC_Alarm1.AlarmMask = RTC_ALARMMASK_DATEWEEKDAY;             //闹钟响铃后则删除闹钟
		RTC_Alarm1.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_NONE;   
		RTC_Alarm1.AlarmTime.TimeFormat = RTC_HOURFORMAT12_AM;        //12小时制
		RTC_Alarm1.AlarmTime.Hours = 0x13;
		RTC_Alarm1.AlarmTime.Minutes = 0x00;
		RTC_Alarm1.AlarmTime.Seconds = 0x30;
		RTC_Alarm1.AlarmTime.SubSeconds = 0x56;		
		HAL_RTC_SetAlarm_IT(&RTC_Handle,&RTC_Alarm1,RTC_FORMAT_BCD);		
	}

void RTC_TimeShow()//串口显示日期时间
{
  RTC_DateTypeDef RTC_Date;
  RTC_TimeTypeDef RTC_Time;
  
  /* Get the RTC current Time */
  HAL_RTC_GetTime(&RTC_Handle, &RTC_Time, RTC_FORMAT_BIN);
  /* Get the RTC current Date */
  HAL_RTC_GetDate(&RTC_Handle, &RTC_Date, RTC_FORMAT_BIN);
  /* Display time Format : hh:mm:ss */
  printf("20%02d-%02d-%02d 星期%d\r\n",RTC_Date.Year, RTC_Date.Month, RTC_Date.Date,RTC_Date.WeekDay);
	printf("%02d:%02d:%02d\r\n",RTC_Time.Hours, RTC_Time.Minutes, RTC_Time.Seconds);
} 

/***********RTC闹钟回调函数*************/
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *RTC_Handle)
	{		
    usart_sentstring("该起床啦\r\n");
	}

