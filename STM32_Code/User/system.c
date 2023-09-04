#include "system.h"         //ͷ�ļ�����



unsigned int system_1ms;
unsigned char system_point=0;//ϵͳָ��




/********************************
*������interrupt_1ms(void)
*
*���ܣ�1ms�¼����£���ʡ��ʱ���ж���Դ
*********************************/
void interrupt_1ms(void)
{
	  if(system_1ms>0){//1ms�ж�
			
		 	  cnt_app_wifi++;
			
			  system_point++;//ϵͳ����ָ��

         
			   cnt_display++;
				 timer3cnt++;//��ʱ���жϻص�����			
				 cnt_led++;

				 cnt_beep++;
         if(cnt_esp8266>0)cnt_esp8266++;
			   if(keycnt)keycnt++;
				 if(cnt_syn>0) cnt_syn--;
			   system_1ms=0;	
		}
}


/********************************
*������system_config(void)
*
*���ܣ���ʼ��ϵͳ����
*********************************/
void system_config(void)
{
    unsigned char i;
	
		SystemClock_Config();  //RCCʱ������  				
		
		Usart_Config();        //USART���� 

		Timer_Config();        //TIMER����	
		
		GPIO_Config();         //GPIO����  

	  Key_Config();          //������ʼ��
		
    esp8266_exit_cipsend();//ESP8266�˳�͸��ģʽ

		

				
			SPI_Config();//SPI��ʼ��
			
			OLED_Config();//��Ļ��ʼ��
			
			App_Display_Sensor_Config();//������ʾ��ʼ��			
		 
     ADC_Config();       //ADC��ʼ��

		 cnt_syn=5000;//ͬ����������ֵ��λ
}



/********************************
*������system_start(void)
*
*����a:system_point����ָ��
*
*����b:system_cnt�����л���ʱ
*********************************/
void system_start(void)
{ 
	
	for(;;){//����ѭ��
	      
		      interrupt_1ms();//1������������¼�
		
					switch(system_point)
					{	
						
						case 1:
                    App_GetSensor_Point();//�ڵ��ȡ����������
						        
						        App_Alarm();
						break;

						case 2:
                    esp8266_sta_connect();   //�ڵ������յ��������				
						break;

						case 3:
						        uart_set_net_info();

						break;

						case 4:	
					           App_Syn_Led();
						       App_Key_Master(); 
									 system_point=0;
						break;
						
						default:
									 system_point=0;
						break;

					}
	}

}


/********************************
*������main(void)
*
*���ܣ����������
*********************************/
int main(void)
{
	
  system_config();//��ʼ��ϵͳ
	
	system_start(); //����ϵͳ
	
	return 0;
}










