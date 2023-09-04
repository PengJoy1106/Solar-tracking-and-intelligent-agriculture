/******************************
�������� ��

����汾:V180206

���ߣ�������ͬѧ

·���������޸����:SSID
·���������޸����:PASSWORD

TCP������IP�޸����:   TCPS_IP
TCP�������˿��޸����: TCPS_PORT
******************************/

#include "esp8266.h"

//#define SSID         "MEEYI-AP"           //·����SSID
//#define PASSWORD     "hyt123456"          //·����PASSWORD

#define TCPS_IP      "183.230.40.40"      //TCP������IP
#define TCPS_PORT    "1811"               //TCP�������˿ں�

#define SSID         "Pengyk"           //·����SSID
#define PASSWORD     "12345678"          //·����PASSWORD

//#define SSID          "Pengyk"
//#define PASSWORD      "51702021004"

//#define TCPS_IP      "192.168.116.26"      //TCP������IP
//#define TCPS_PORT    "5000"               //TCP�������˿ں�


#define AP_TCPS_IP   "192.168.191.2"        //apģʽ�£��ֻ�����TCPS
#define AP_TCPS_PORT "5000"               //�ֻ������Ķ˿ں�

unsigned int  cnt_esp8266=0;
unsigned char status_esp8266=0x00;
unsigned char ok_esp8266=0;        //ͨ�ųɹ���־
unsigned char tx_temp[256]={0};


unsigned char ssid[21]="MiWiFi";
unsigned char password[21]="88888888+";
unsigned char tcps[21]="183.230.40.40";
unsigned char port[21]="1811";

unsigned char save_index;
unsigned char set_update;

unsigned char point_app_wifi=0;
unsigned int  cnt_app_wifi=0;

unsigned char cmd_onenet;
unsigned char value_onenet;
unsigned char update_onenet;
unsigned char flag_message=0;//�ʼ�����
unsigned char limit_message=0;

void App_Onenet_Cmd(void)
{

   if(update_onenet){
   	 
	 update_onenet=0;
   
	 switch(cmd_onenet)
		 {
		 case 'm':
							flag_alarm_on=value_onenet;
		 break;

		 case 'f':
							flag_net_fan=value_onenet;
							flag_alarm_on=0;//��Ϊ�ƶ˿���
		 break;

		 default:

		 break;	 
		 }
        FlashIn_Erase_Page(FLASH_USER_ADDRESS,1);

        HAL_FLASH_Unlock();

        HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,FLASH_USER_ADDRESS,(max_wendu<<8)|min_wendu);//
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,FLASH_USER_ADDRESS+2,(max_shidu<<8)|min_shidu);//
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,FLASH_USER_ADDRESS+4,(max_light<<8)|min_light);//
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,FLASH_USER_ADDRESS+6,(max_soil<<8)|min_soil);//
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,FLASH_USER_ADDRESS+8,(flag_alarm_on<<8)|flag_alarm_on);//
        HAL_FLASH_Lock();							
   }
}

void Login_OneNet(void)
{		       
		printf("*408589#0001#app*\r\n");//ע��
}



void App_Wifi(void)
{
	unsigned int temp_x,temp_y;
	unsigned char i;
	
    App_Onenet_Cmd();
	
   if(cnt_app_wifi>1000){
   
	 point_app_wifi++;
	 if(point_app_wifi>1){ point_app_wifi=0;}
	 
	 switch(point_app_wifi)
	 {
		 case 0:
            Login_OneNet();
		 
			    //	usart_sentstring(UART1,"login\r\n");    
		 break;
	
		 case 1://����ʪ�ȡ������¶ȡ�����ʪ�ȡ�ģʽ�����͡��쳣�ϱ�
				//	usart_sentstring(UART1,"info report\r\n");

				tx_temp[0]=0x5a;
				tx_temp[1]=0x5a;
				tx_temp[2]=12;//data����10�ֽ�
				tx_temp[3]=0x01;//����1	
				
				tx_temp[4]=1;

				temp_y=temp_x=(unsigned char)dht11_temperature;//�¶�	 
				temp_x=(temp_x/10)<<4;
				temp_y=(temp_y%10);					 
				tx_temp[5]=temp_x|temp_y;

				temp_y=temp_x=(unsigned char)dht11_humidity;//ʪ��	 
				temp_x=(temp_x/10)<<4;
				temp_y=(temp_y%10);					 
				tx_temp[6]=temp_x|temp_y;
		 

 				temp_y=temp_x=(unsigned char)light;//	 
				temp_x=(temp_x/10)<<4;
				temp_y=(temp_y%10);					 
				tx_temp[7]=temp_x|temp_y;
				
 				temp_y=temp_x=(unsigned char)soil;//
				temp_x=(temp_x/10)<<4;
				temp_y=(temp_y%10);					 
				tx_temp[8]=temp_x|temp_y;				
				
				 
        tx_temp[9]=flag_alarm_on;//�Ƿ����澯
        tx_temp[10]=flag_beep;//�Ƿ�澯
				

       if(flag_beep==1){//���ͱ���
			    
				 if(flag_message==0&&limit_message==0)//û�з��͹��ʼ�����û�б�����
					{
					  flag_message=1;//�����ʼ�
						limit_message=1;//���Ʒ����ʼ�
					}
					else
					{
					  flag_message=0;//���Ʒ����ʼ�
					}
			 }
			 else
			 {
			    flag_message=0;//�����ʼ����ͱ�־
				 limit_message=0;//ȡ�����Ʒ����ʼ�
			 }

        tx_temp[11]=flag_message;
				tx_temp[12]=alarm_temperature;
			  tx_temp[13]=alarm_humidity;
			  tx_temp[14]=alarm_light;
			  tx_temp[15]=alarm_soil;
        tx_temp[16]=0xA5;
				
				 for(i=0;i<tx_temp[2]+5;i++) 
				   {							   
							 
							 usart_sentdata(UART2,tx_temp[i]);
							 
						//	 usart_sentdata(UART1,rx_temp[i]);	
				   }
		 break;
		 	
		 	
	 }

   	cnt_app_wifi=0;
   }
}

void esp8266_exit_cipsend(void)
{
	unsigned char i;
	
	for(i=0;i<20;i++){
		
	   printf("+++");
		
	   delayms(100);
		
		if(ok_esp8266){ 
			//usart_sentstring(UART1,"ESP8266 Back OK\r\n");
		break;
		}
		
	}
	
	FlashIn_Read_NByte(FLASH_NET_ADDRESS,80);
	 
	if(Flash_Buf[0]!=0xff){

	 for(i=0;i<20;i++){
		
		 ssid[i]=Flash_Buf[i];
		 password[i]=Flash_Buf[20+i];
		 tcps[i]=Flash_Buf[40+i];
		 port[i]=Flash_Buf[60+i];
		}
	 	

	}
	
}



//static void wipe_buffer(unsigned char *s,unsigned char len)
//{
//  do
//  {
//   *s=0;
//    s++;
//  }while(len--);
//}

/****************************
��������:esp8266 sta״̬��
ESP8266����wifi·����,��������TCP����������
****************************/
void esp8266_sta_connect(void)
{
  switch(status_esp8266)
	{
		case esp8266_mode_set:
		if(cnt_esp8266==0)
			{  
				cnt_esp8266=1;//��ʱ��ʼ
				rx_index=0;wipe_buffer(rx_temp,100);
				ok_esp8266=0;
				printf("AT+CWMODE=1\r\n");//satģʽ����
				usart_sentstring(UART1,"---AT+CWMODE=1\r\n");
			}
	else{
			if(cnt_esp8266>200)
				{
					if(ok_esp8266==1)
						{//���óɹ�
							ok_esp8266=0;
							cnt_esp8266=0;  
							status_esp8266=esp8266_rst; //������һ��״̬  
						}
					else{
							cnt_esp8266=0;//����
							}
         }  
      }   
		break;
		case esp8266_rst:
		if(cnt_esp8266==0)
			{          
				ok_esp8266=0;
				rx_index=0;wipe_buffer(rx_temp,100);
				cnt_esp8266=1;//��ʱ��ʼ
				printf("AT+RST\r\n");   //��λ
				usart_sentstring(UART1,"---AT+RST\r\n\r\n");							
			}
		else
			{
				if(cnt_esp8266>3000){ //3���                    
				if(ok_esp8266==1){//���óɹ�
				ok_esp8266=0;rx_index=0;wipe_buffer(rx_temp,100);
				cnt_esp8266=0;
				status_esp8266=esp8266_connect_wifi; //���óɹ���������һ��״̬ 
				}else{            //����δ�ɹ�
				if(cnt_esp8266>3000){
				cnt_esp8266=0;//����                                
							}
					}
				}
			}  
		break;  					
	case esp8266_connect_wifi:
            if(cnt_esp8266==0){          
                ok_esp8266=0;
                rx_index=0;wipe_buffer(rx_temp,100);
                cnt_esp8266=1;//��ʱ��ʼ
                 printf("AT+CWJAP=\"%s\",\"%s\"\r\n",ssid,password);   //����wifi
							    usart_sentstring(UART1,"---AT+CWJAP");
            }
            else{
                  if(cnt_esp8266>5000){ //5��� 
										
                      if(ok_esp8266==1){//���óɹ�
                       ok_esp8266=0;rx_index=0;wipe_buffer(rx_temp,100);
                       cnt_esp8266=0;
												point_led=500;
                       status_esp8266=esp8266_connect_tcps; //���óɹ���������һ��״̬ 
                      }else{            //����δ�ɹ�
                            if(cnt_esp8266>4000){
                                cnt_esp8266=0;//����                                
                           }
														
                      }
                  }
            }  
      break;						
						

case esp8266_connect_tcps:
if(cnt_esp8266==0){      
	ok_esp8266=0;
	rx_index=0;wipe_buffer(rx_temp,100);
	cnt_esp8266=1;//��ʱ��ʼ
	printf("AT+CIPSTART=\"TCP\",\"%s\",%s\r\n",TCPS_IP,TCPS_PORT);//����TCP������
	usart_sentstring(UART1,"---AT+CIPSTART\r\n");
}
else{
	if(cnt_esp8266>2000){     
	if(ok_esp8266==1){ //���óɹ�
		ok_esp8266=0;
		rx_index=0;
		wipe_buffer(rx_temp,100);
		cnt_esp8266=0;
		status_esp8266=esp8266_usart_set; //������һ��״̬ 
		}
	else{          //����δ�ɹ�
		cnt_esp8266=0;//���� 
			}
		}
	}           
break;  

      case esp8266_usart_set:
        
             if(cnt_esp8266==0){      
                ok_esp8266=0;
                rx_index=0;
                wipe_buffer(rx_temp,100);
                cnt_esp8266=1;//��ʱ��ʼ
                printf("AT+CIPMODE=1\r\n");//͸������
               usart_sentstring(UART1,"---AT+CIPMODE=1\r\n");							 
            }
            else{
                  if(cnt_esp8266>200){     
                      if(ok_esp8266==1){
                         ok_esp8266=0;
                         rx_index=0;
                         wipe_buffer(rx_temp,100);
                         cnt_esp8266=0;
                         status_esp8266=esp8266_usart_go;//������һ��״̬  
                      }
                      else{       //����δ�ɹ�
                          cnt_esp8266=0;//���� 
                      }
                  }
            }                  
      break;
     
      case esp8266_usart_go:
				
              if(cnt_esp8266==0){      
                ok_esp8266=0;
                rx_index=0;
                wipe_buffer(rx_temp,100);
                cnt_esp8266=1;//��ʱ��ʼ
								point_led=2000;
								
                printf("AT+CIPSEND\r\n");//͸������
								usart_sentstring(UART1,"---AT+CIPSEND\r\n");		
             }
              else{
                  if(cnt_esp8266>200){     
                      if(ok_esp8266==1){
                         
                         rx_index=0;
                         wipe_buffer(rx_temp,100);
                         cnt_esp8266=0;
                         status_esp8266=eps8266_config_ok;//������һ��״̬ 
                         Login_OneNet();												
                      }
                      else{       //����δ�ɹ�
                          cnt_esp8266=0;//���� 
                      }
                  }
            }            
      break; 
       
       case eps8266_config_ok:  
 
	         App_Wifi();
  
       break;   
       
      default:break;
    }
		

	

			
}


/**********************
��������:esp8266 AP״̬��
�ֻ�����ESP8266������TCPS��ESP8266��������TCP����������
**********************/
void esp8266_ap_connect(void)
{
  switch(status_esp8266)
    {
      case esp8266_mode_set:
        
              if(cnt_esp8266==0){  
                    cnt_esp8266=1;//��ʱ��ʼ
                    rx_index=0;wipe_buffer(rx_temp,100);
                    ok_esp8266=0;
                    printf("AT+CWMODE=3\r\n");//apģʽ����
								    usart_sentstring(UART1,"---AT+CWMODE=3\r\n");	
              }
              else{
                  if(cnt_esp8266>100){
                    
                      if(ok_esp8266==1){//���óɹ�
                         ok_esp8266=0;
                         cnt_esp8266=0;  
                         status_esp8266=esp8266_rst; //������һ��״̬  
                      }
                      else{
                           cnt_esp8266=0;//����
                      }
                  }  
              }   
      break;
      case esp8266_rst:
        
            if(cnt_esp8266==0){          
                ok_esp8266=0;
                rx_index=0;wipe_buffer(rx_temp,100);
                cnt_esp8266=1;//��ʱ��ʼ
                 printf("AT+RST\r\n");   //��λ 
							  usart_sentstring(UART1,"---AT+RST\r\n");	
            }
            else{
                  if(cnt_esp8266>2000){ //2���                    
                      if(ok_esp8266==1){//���óɹ�
                       ok_esp8266=0;rx_index=0;wipe_buffer(rx_temp,100);
                       cnt_esp8266=0;
                       status_esp8266=esp8266_connect_tcps; //���óɹ���������һ��״̬ 
                      }else{            //����δ�ɹ�
                            if(cnt_esp8266>3000){
                                cnt_esp8266=0;//����                                
                          }
                      }
                  }
            }  
      break;  
 
      case esp8266_connect_tcps:
        
             if(cnt_esp8266==0){      
                ok_esp8266=0;
                rx_index=0;wipe_buffer(rx_temp,100);
                cnt_esp8266=1;//��ʱ��ʼ
                printf("AT+CIPSTART=\"TCP\",\"%s\",%s\r\n",AP_TCPS_IP,AP_TCPS_PORT);//����TCP������ 
							  usart_sentstring(UART1,"---AT+CIPSTART\r\n");
            }
            else{
                  if(cnt_esp8266>1000){     
                      
                     if(ok_esp8266==1){ //���óɹ�
                         ok_esp8266=0;
                         rx_index=0;
                         wipe_buffer(rx_temp,100);
                         cnt_esp8266=0;
                         status_esp8266=esp8266_usart_set; //������һ��״̬ 
                      }
                      else{          //����δ�ɹ�
                          cnt_esp8266=0;//���� 
                      }
                  }
            }           
        
      break;  
      case esp8266_usart_set:
        
             if(cnt_esp8266==0){      
                ok_esp8266=0;
                rx_index=0;
                wipe_buffer(rx_temp,100);
                cnt_esp8266=1;//��ʱ��ʼ
                printf("AT+CIPMODE=1\r\n");//͸������
                usart_sentstring(UART1,"---AT+CIPMODE=1\r\n");							 
            }
            else{
                  if(cnt_esp8266>200){     
                      if(ok_esp8266==1){
                         ok_esp8266=0;
                         rx_index=0;
                         wipe_buffer(rx_temp,100);
                         cnt_esp8266=0;
                         status_esp8266=esp8266_usart_go;//������һ��״̬  
                      }
                      else{       //����δ�ɹ�
                          cnt_esp8266=0;//���� 
                      }
                  }
            }                  
      break;
     
      case esp8266_usart_go:
              if(cnt_esp8266==0){      
                ok_esp8266=0;
                rx_index=0;
                wipe_buffer(rx_temp,100);
                cnt_esp8266=1;//��ʱ��ʼ
                printf("AT+CIPSEND\r\n");//͸������
								 usart_sentstring(UART1,"---AT+CIPSEND\r\n");	
             }
              else{
                  if(cnt_esp8266>200){     
                      if(ok_esp8266==1){
                         
                         rx_index=0;
                         wipe_buffer(rx_temp,100);
                         cnt_esp8266=0;
                         status_esp8266=eps8266_config_ok;//������һ��״̬  
                      }
                      else{       //����δ�ɹ�
                          cnt_esp8266=0;//���� 
                      }
                  }
            }            
      break; 
       
       case eps8266_config_ok:      

         if(cnt_esp8266==0){
            cnt_esp8266=1;
         }
         else{
             if(cnt_esp8266>1000){
               printf("*175380#0001#app*\r\n");

               cnt_esp8266=0;
             }
         }
         
       break;   
       
      default:break;
    }
	
	
	




}








/****************************
��������:esp8266���ڱ�־λ����
��־λ:  ok_esp8266
****************************/
void esp8266_usart_isr(void)
{
    if(rx_index>0){ //OK
			
        if(rx_temp[rx_index]=='K'&&rx_temp[rx_index-1]=='O'){
           ok_esp8266=1;
        }
    }
    if(rx_index>3){ //ready
        if(rx_temp[rx_index]=='y'&&rx_temp[rx_index-1]=='d'&&rx_temp[rx_index-2]=='a'&&rx_temp[rx_index-3]=='e'&&rx_temp[rx_index-4]=='r'){
           ok_esp8266=1;
        }
    }    
    if(rx_index>13){ //ALREADY CONNECTED
        if(rx_temp[rx_index]=='D'&&rx_temp[rx_index-1]=='E'&&rx_temp[rx_index-2]=='T'&&rx_temp[rx_index-3]=='C'&&rx_temp[rx_index-4]=='E'){
          if(rx_temp[rx_index-5]=='N'&&rx_temp[rx_index-6]=='N'&&rx_temp[rx_index-7]=='O'&&rx_temp[rx_index-8]=='C'){
						if(rx_temp[rx_index-9]==' '&&rx_temp[rx_index-10]=='Y'&&rx_temp[rx_index-11]=='D'&&rx_temp[rx_index-12]=='A'&&rx_temp[rx_index-13]=='E'&&rx_temp[rx_index-14]=='R')
              ok_esp8266=1;
          }
        }
    }
		
		if(rx_index>1){
		
        if(rx_temp[rx_index]=='+' && rx_temp[rx_index-1]=='+' && rx_temp[rx_index-2]=='+'){
           ok_esp8266=1;
        }			
		}
		
    
    if(rx_temp[rx_index]=='>'){
       ok_esp8266=1;
    }
		
		 if(rx_index>0){
			 
			 if(rx_temp[rx_index]==0x0a && rx_temp[rx_index-1]==0x0d){
		
				 
				if(set_update==0){set_update=1;save_index=rx_index;}
				
			 }
		 }
	
		 
	 if(rx_index>0){
		 
		 if(rx_temp[rx_index]=='.' && rx_temp[rx_index-1]=='.'){
	 				
	   	    value_onenet=rx_temp[rx_index-2]-0x30;			
			cmd_onenet=rx_temp[rx_index-4];

			update_onenet=1;
								
		 }
	 }		
		
		
}




/***********************
*ssid:    ssid=XXX\r\n
*
*password:word=XXX\r\n
*
*tcps:    tcps=XXX\r\n
*
*port:    port=XXX\r\n
***********************/
void uart_set_net_info(void)
{
  unsigned char i;
	
	unsigned char len;
	
	unsigned char save=0;
	
	if(set_update){//�������

			if(save_index>6){//�������ٴ���1�����ȣ���������ȡ����Ƶ����ٴ���6�������壬��SSID=K\r\n

						i=3;	

						while(rx_temp[save_index-i]!='=' && save_index!=i)
						{	

						 if(save_index>i)i++; 
							
						}
																																																																																																																																																																																																																														
						len=i-2;//�������	
						if(len>20)len=20;

						
						//printf("len=%d\r\n",len);
						
						if(save_index>len+5){
							
									if(rx_temp[save_index-len-6]=='s' && rx_temp[save_index-len-5]=='s' && rx_temp[save_index-len-4]=='i' && rx_temp[save_index-len-3]=='d'){
									
										
										for(i=0;i<len;i++)
												 ssid[i]=rx_temp[save_index-len-1+i];
									
										ssid[len]=0;//����ĩ�˸�ֵ0���պò����ӡ����
									
										for(i=len+1;i<20;i++)  ssid[i]=0xff;

									save=1;
										printf("ssid=%s\r\n",ssid);
									
									}
									
									if(rx_temp[save_index-len-6]=='w' && rx_temp[save_index-len-5]=='o' && rx_temp[save_index-len-4]=='r' && rx_temp[save_index-len-3]=='d'){
									

										for(i=0;i<len;i++)
												 password[i]=rx_temp[save_index-len-1+i];
									
										password[len]=0;//����ĩ�˸�ֵ0���պò����ӡ����
									
										for(i=len+1;i<20;i++)  password[i]=0xff;

									save=1;
										printf("word=%s\r\n",password);
									
									}						
									
									if(rx_temp[save_index-len-6]=='t' && rx_temp[save_index-len-5]=='c' && rx_temp[save_index-len-4]=='p' && rx_temp[save_index-len-3]=='s'){
									

										for(i=0;i<len;i++)
												 tcps[i]=rx_temp[save_index-len-1+i];
									
										tcps[len]=0;//����ĩ�˸�ֵ0���պò����ӡ����
									
										for(i=len+1;i<20;i++)  tcps[i]=0xff;

									save=1;
										printf("tcps=%s\r\n",tcps);
									
									}

									if(rx_temp[save_index-len-6]=='p' && rx_temp[save_index-len-5]=='o' && rx_temp[save_index-len-4]=='r' && rx_temp[save_index-len-3]=='t'){
									
										for(i=0;i<len;i++)
												 port[i]=rx_temp[save_index-len-1+i];
									
										port[len]=0;//����ĩ�˸�ֵ0���պò����ӡ����
									
										for(i=len+1;i<20;i++)  port[i]=0xff;

									save=1;
										printf("port=%s\r\n",port);
									
									}
								 
									if(save==1){
										
										FlashIn_Erase_Page(FLASH_NET_ADDRESS,1);//����һҳ
										delayms(100);

										FlashIn_Write_NByte(FLASH_NET_ADDRESS,ssid,20);
										
										FlashIn_Write_NByte(FLASH_NET_ADDRESS+20,password,20);
									
										FlashIn_Write_NByte(FLASH_NET_ADDRESS+40,tcps,20);
									
										FlashIn_Write_NByte(FLASH_NET_ADDRESS+60,port,20);
									
										FlashIn_Read_NByte(FLASH_NET_ADDRESS,80);
										 
										 for(i=0;i<20;i++){
											
											 ssid[i]=Flash_Buf[i];
											 password[i]=Flash_Buf[20+i];
											 tcps[i]=Flash_Buf[40+i];
											 port[i]=Flash_Buf[60+i];
											}
										 
										printf("ssid=%s\r\n",ssid);
										printf("word=%s\r\n",password);
										printf("tcps=%s\r\n",tcps);				
										printf("port=%s\r\n",port);
									}
					
						}
						
					}

		rx_index=0;
		set_update=0;
		}	
}




