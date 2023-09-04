#include "app.h"         //ͷ�ļ�����


unsigned char temperature;
unsigned char gas_bi;
unsigned int  adc;


unsigned char min_wendu=10,max_wendu=50;
unsigned char min_shidu=20,max_shidu=99;
unsigned char min_light=20,max_light=99;
unsigned char min_soil=5,max_soil=50;
unsigned char flag_alarm_on=1;//�ƶ˿���

unsigned int  cnt_beep;//��������ʱ
unsigned int  cnt_syn; //ͬ����ʱ

unsigned int  cnt_display=0;   //��ʾ���¼���ֵ

unsigned char flag_check;//��ѯ��־λ
unsigned char flag_beep;//������������־λ
unsigned char flag_net_fan=0;

unsigned char mode_set=0;//��������

unsigned char mode_display=0;  //��ʾģʽ

unsigned char alarm_temperature;//�¶ȱ���
unsigned char alarm_humidity;//
unsigned char alarm_light;//
unsigned char alarm_soil;//


/********************************
*������App_GetSensor_Point(void)
*
*���ܣ��ڵ㴫�������ݲɼ���Ƶ��1s/��
*********************************/
void App_GetSensor_Point(void)
{
	 if(timer3cnt>1000) //1��ʱ�䵽�������ɼ�������䵽��������
			{ 															
				
				DHT11_Read();        //��ȡ��ʪ��ֵ
		  
				ADC_Read_N(10);	

				App_Display_Sensor();

			  timer3cnt=0;																			//������������ֹ1ms���ظ������if��	 
		 }
}




/********************************
*������App_Alarm(void)
*
*���ܣ��澯����
*********************************/
void App_Alarm(void)
{	
	
		if(flag_alarm_on==1){
		  	
			 LED1_ON;
			
					if(flag_beep==1)//�и澯
							{
								
								 if(cnt_beep>500){
											
									 BEEP_ON;
										LED2_ON;		 
									 cnt_beep=0;
								 }else{	 		 
																 
												 if(cnt_beep>100){									 
													 BEEP_OFF;LED2_OFF;	

												 }
											}
							}
						else
						{
							BEEP_OFF;	
						}
			
    }else {
			LED1_OFF;
		
		  BEEP_OFF;		
		}
		
			
			

			
	
}



/********************************
*������App_Key_Master(void)
*
*���ܣ������������̣��������ø澯����
*********************************/
void App_Key_Master(void)
{	
	unsigned char i;
	key_value=keyscan();//����ɨ��

   switch(key_value)
   {
     case VALUE_C:
                  mode_set++;
                  
                  switch(mode_set)
                  {
                    case 1:
                          LCD_CLS();//���������ʾ   
                          LCD_P8x16(36,0,&num[min_wendu/10]);
                          LCD_P8x16(44,0,&num[min_wendu%10]);
                          LCD_P8x16Str(52,0,"C-  C");

                           for(i=0;i<2;i++)
                           {								 
                              LCD_P16x16Ch(i*16,0,18+i);//�¶�
                              LCD_P16x16Ch(i*16,2,20+i);//ʪ��
                              LCD_P16x16Ch(i*16,4,26+i);//����
                              LCD_P16x16Ch(i*16,6,28+i);//��ʪ
                           }
                    break;
                    
                    case 2:
                      LCD_P8x16(68,0,&num[max_wendu/10]);
                      LCD_P8x16(76,0,&num[max_wendu%10]);
       
                    break;                  
                    case 3:
                      LCD_P8x16(36,2,&num[min_shidu/10]);
                      LCD_P8x16(44,2,&num[min_shidu%10]);
                      LCD_P8x16Str(52,2,"%-  %");
       
                    break;                  
                    
                     case 4:
                      LCD_P8x16(68,2,&num[max_shidu/10]);
                      LCD_P8x16(76,2,&num[max_shidu%10]);                               
       
                    break;  
                    
                    case 5:
                        
                       LCD_P8x16(36,4,&num[min_light/10]);
                      LCD_P8x16(44,4,&num[min_light%10]);
                      LCD_P8x16Str(52,4,"%-  %");     
                    break; 

                      case 6:
                          
                        LCD_P8x16(68,4,&num[max_light/10]);
                        LCD_P8x16(76,4,&num[max_light%10]);                         
                             
                    break; 
                    case 7:
                        
                       LCD_P8x16(36,6,&num[min_soil/10]);
                      LCD_P8x16(44,6,&num[min_soil%10]);
                      LCD_P8x16Str(52,6,"%-  %");     
                    break; 

                      case 8:
                          
                        LCD_P8x16(68,6,&num[max_soil/10]);
                        LCD_P8x16(76,6,&num[max_soil%10]);                         
                             
                    break; 
											
                     case 9:
														mode_set=0;

														FlashIn_Erase_Page(FLASH_USER_ADDRESS,1);
													
														 HAL_FLASH_Unlock();
													
															HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,FLASH_USER_ADDRESS,(max_wendu<<8)|min_wendu);//
															HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,FLASH_USER_ADDRESS+2,(max_shidu<<8)|min_shidu);//
											        HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,FLASH_USER_ADDRESS+4,(max_light<<8)|min_light);//
										          HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,FLASH_USER_ADDRESS+6,(max_soil<<8)|min_soil);//
					                    HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,FLASH_USER_ADDRESS+8,(flag_alarm_on<<8)|flag_alarm_on);//
														HAL_FLASH_Lock();																		 
																		 
														FlashIn_Read_NByte(FLASH_USER_ADDRESS,10);	
							 
                            min_wendu=Flash_Buf[0];
                            max_wendu=Flash_Buf[1];
                            min_shidu=Flash_Buf[2];
                            max_shidu=Flash_Buf[3];
                            min_light=Flash_Buf[4];
                            max_light=Flash_Buf[5];
                            min_soil=Flash_Buf[6];
                            max_soil=Flash_Buf[7];
                            flag_alarm_on=Flash_Buf[8];
														App_Display_Sensor_Config();  
														
															break;                 

                  }
     break;
     
     case VALUE_A://��

       switch(mode_set)
       {
         case 0:
           
           
         break;
         
        case 1:
                min_wendu++;if(min_wendu>99)min_wendu=0;                    
                LCD_P8x16(36,0,&num[min_wendu/10]);
                LCD_P8x16(44,0,&num[min_wendu%10]);     
         break;
       
        case 2:
                 max_wendu++;if(max_wendu>99)max_wendu=0;
								LCD_P8x16(68,0,&num[max_wendu/10]);
								LCD_P8x16(76,0,&num[max_wendu%10]);          
          
         break;              
        case 3:
                min_shidu++;if(min_shidu>99)min_shidu=0;
								LCD_P8x16(36,2,&num[min_shidu/10]);
								LCD_P8x16(44,2,&num[min_shidu%10]);              
          
         break;
       
        case 4:
                max_shidu++;if(max_shidu>99)max_shidu=0;
                       LCD_P8x16(68,2,&num[max_shidu/10]);
                      LCD_P8x16(76,2,&num[max_shidu%10]);                  
         break;
         
        case 5:
                    min_light++;if(min_light>99)min_light=0;
								LCD_P8x16(36,4,&num[min_light/10]);
								LCD_P8x16(44,4,&num[min_light%10]);                
         break;     
				
         case 6:
                      max_light++;if(max_light>99)max_light=0;
								LCD_P8x16(68,4,&num[max_light/10]);
								LCD_P8x16(76,4,&num[max_light%10]);                    
         break; 

        case 7:
                    min_soil++;if(min_soil>99)min_soil=0;
								LCD_P8x16(36,6,&num[min_soil/10]);
								LCD_P8x16(44,6,&num[min_soil%10]);                
         break;     
				
         case 8:
                      max_soil++;if(max_soil>99)max_soil=0;
								LCD_P8x16(68,6,&num[max_soil/10]);
								LCD_P8x16(76,6,&num[max_soil%10]);                    
         break; 

       }
       
                
     break;
     
     case VALUE_B://��
       
       switch(mode_set)
       {
         case 0:
		             if(flag_alarm_on)flag_alarm_on=0;
                 else             flag_alarm_on=1;

                  FlashIn_Erase_Page(FLASH_USER_ADDRESS,1);
                
                    HAL_FLASH_Unlock();
                
                    HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,FLASH_USER_ADDRESS,(max_wendu<<8)|min_wendu);//
                    HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,FLASH_USER_ADDRESS+2,(max_shidu<<8)|min_shidu);//
                    HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,FLASH_USER_ADDRESS+4,(max_light<<8)|min_light);//
                    HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,FLASH_USER_ADDRESS+6,(max_soil<<8)|min_soil);//
                    HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,FLASH_USER_ADDRESS+8,(flag_alarm_on<<8)|flag_alarm_on);//
                  HAL_FLASH_Lock();								                
         break;
         
        case 1:

                 min_wendu--;if(min_wendu==255)min_wendu=99;
         
                 LCD_P8x16(36,0,&num[min_wendu/10]);
                 LCD_P8x16(44,0,&num[min_wendu%10]);         
         break;
       
        case 2:
          max_wendu--;if(max_wendu==255)max_wendu=99;
                       LCD_P8x16(68,0,&num[max_wendu/10]);
                      LCD_P8x16(76,0,&num[max_wendu%10]);          
         break;              
       case 3:
                min_shidu--;if(min_shidu==255)min_shidu=99;
                         LCD_P8x16(36,2,&num[min_shidu/10]);
                      LCD_P8x16(44,2,&num[min_shidu%10]);                
         break;
       
        case 4:
                max_shidu--;if(max_shidu==255)max_shidu=99;
                         LCD_P8x16(68,2,&num[max_shidu/10]);
                      LCD_P8x16(76,2,&num[max_shidu%10]);               
         break;  
         
        case 5:
                  min_light--;if(min_light==255)min_light=99;
                         LCD_P8x16(36,4,&num[min_light/10]);
                      LCD_P8x16(44,4,&num[min_light%10]);               
         break;            
         case 6:
                     max_light--;if(max_light==255)max_light=99;
                         LCD_P8x16(68,4,&num[max_light/10]);
                      LCD_P8x16(76,4,&num[max_light%10]);              
         break;

        case 7:
                  min_soil--;if(min_soil==255)min_soil=99;
                     LCD_P8x16(36,6,&num[min_soil/10]);
                      LCD_P8x16(44,6,&num[min_soil%10]);               
         break;            
         case 8:
                     max_soil--;if(max_soil==255)max_soil=99;
                      LCD_P8x16(68,6,&num[max_soil/10]);
                      LCD_P8x16(76,6,&num[max_soil%10]);              
         break;


       }   
       
     break;
     
   }	
	
	
}






/********************************
*������App_Display_Sensor_Config(void)
*
*���ܣ���������ʾ��ʼ��
*********************************/
void App_Display_Sensor_Config(void)
{	
	
 unsigned char i;
 unsigned char offset=1;
	
 LCD_CLS();
 
 for(i=0;i<2;i++)
 {
    LCD_P16x16Ch(i*16,0,18+i);//�¶�
    LCD_P16x16Ch(i*16,2,20+i);//ʪ��
    LCD_P16x16Ch(i*16,4,26+i);//����
	  LCD_P16x16Ch(i*16,6,28+i);//��ʪ
 }
 
 LCD_P8x16Str(32,0,":  C");
 LCD_P8x16Str(32,2,":  %");
 LCD_P8x16Str(32,4,":  %");
 LCD_P8x16Str(32,6,":  %"); 
 

		FlashIn_Read_NByte(FLASH_USER_ADDRESS,10);	

		if(Flash_Buf[0]!=0xff&&Flash_Buf[1]!=0xff)
		{
					 min_wendu=Flash_Buf[0];
					 max_wendu=Flash_Buf[1];
					 min_shidu=Flash_Buf[2];
					 max_shidu=Flash_Buf[3];
           min_light=Flash_Buf[4];
			     max_light=Flash_Buf[5];
			     min_soil=Flash_Buf[6];
           max_soil=Flash_Buf[7];
					 flag_alarm_on=Flash_Buf[8];
		}
 
  LCD_P8x16(72,0,&num[min_wendu/10]);
  LCD_P8x16(80,0,&num[min_wendu%10]);
  LCD_P8x16Str(88,0,"C-  C");
  LCD_P8x16(104,0,&num[max_wendu/10]);
  LCD_P8x16(112,0,&num[max_wendu%10]);
  
  LCD_P8x16(72,2,&num[min_shidu/10]);
  LCD_P8x16(80,2,&num[min_shidu%10]);
  LCD_P8x16Str(88,2,"%-  %");
  LCD_P8x16(104,2,&num[max_shidu/10]);
  LCD_P8x16(112,2,&num[max_shidu%10]); 
 
  LCD_P8x16(72,4,&num[min_light/10]);
  LCD_P8x16(80,4,&num[min_light%10]);
  LCD_P8x16Str(88,4,"%-  %");
  LCD_P8x16(104,4,&num[max_light/10]);
  LCD_P8x16(112,4,&num[max_light%10]); 

  LCD_P8x16(72,6,&num[min_soil/10]);
  LCD_P8x16(80,6,&num[min_soil%10]);
  LCD_P8x16Str(88,6,"%-  %");
  LCD_P8x16(104,6,&num[max_soil/10]);
  LCD_P8x16(112,6,&num[max_soil%10]); 		
   App_Display_Sensor();
}




/********************************
*������App_Display_Sensor(void)
*
*���ܣ���������ʾ
*********************************/
void App_Display_Sensor(void)
{	
   unsigned char i;
	if(mode_set!=0)return;
	
 LCD_P8x16(40,0,&num[dht11_temperature/10]);
 LCD_P8x16(48,0,&num[dht11_temperature%10]);
  
 LCD_P8x16(40,2,&num[dht11_humidity/10]);
 LCD_P8x16(48,2,&num[dht11_humidity%10]);  
 
   LCD_P8x16(40,4,&num[light/10]);
   LCD_P8x16(48,4,&num[light%10]);
	
   LCD_P8x16(40,6,&num[soil/10]);
   LCD_P8x16(48,6,&num[soil%10]);
	
	flag_beep=0;
	
	if(max_wendu!=min_wendu)
	 {
			if(dht11_temperature>max_wendu||dht11_temperature<min_wendu)
			{
				flag_beep=1;LCD_P8x16Str(64,0,"x");alarm_temperature=1; 
			}else       {  LCD_P8x16Str(64,0," ");alarm_temperature=0;} 
   }
	
	if(max_shidu!=min_shidu)
	 {	
		if(dht11_humidity>max_shidu||dht11_humidity<min_shidu)
		{
			flag_beep=1;LCD_P8x16Str(64,2,"x");alarm_humidity=1; 
		}else        { LCD_P8x16Str(64,2," "); alarm_humidity=0;}
   }	
	
	if(max_light!=min_light)
	 {	
		if(light>max_light||light<min_light)
		{
			flag_beep=1;LCD_P8x16Str(64,4,"x");alarm_light=1; 
			
		}else { LCD_P8x16Str(64,4," ");alarm_light=0;}
   }

	if(max_soil!=min_soil)
	 {	
		if(soil>max_soil||soil<min_soil)
		{
			flag_beep=1;LCD_P8x16Str(64,6,"x");alarm_soil=1; 
			
		}else { LCD_P8x16Str(64,6," ");alarm_soil=0;}
   }
  LCD_P8x16(72,0,&num[min_wendu/10]);

  
  LCD_P8x16(72,2,&num[min_shidu/10]);
; 
 
  LCD_P8x16(72,4,&num[min_light/10]);


  LCD_P8x16(72,6,&num[min_soil/10]);

	 
}










	
/********************************
*������App_Syn_Led(void)
*
*���ܣ�δ�յ�ͬ��������Ϩ��
*********************************/
void App_Syn_Led(void)
{
		 
	if(flag_beep==1)return;

	if(cnt_led>point_led){
		 
			 LED2_ON;
			 
			 cnt_led=0;
			 
		 }else{
		 
				 if(cnt_led>100){
				 
					 LED2_OFF;
				 }		 
		 }	

 }	 

			

















