#include "sx1278.h"	
#include "lora.h"

unsigned char lora_rx_index;
unsigned char lora_rx;//罗拉接收标志位

unsigned char recv[100];											

void LoRa_FSM(void)
{
		unsigned char i;
								
		RF_EX0_STATUS = SX1278_READ_BUFFER( REG_LR_IRQFLAGS);//读中断寄存器

		if (RF_EX0_STATUS > 0)
			{
				if ((RF_EX0_STATUS & 0x40) == 0x40)   //数据包接收完毕
							{
								CRC_Value = SX1278_READ_BUFFER( REG_LR_MODEMCONFIG2);
								
								if (CRC_Value & 0x04 == 0x04)     //CAD校验完成
									{	 
							        cycle_led=3;																		
										// printf("LORA 数据校验完成\r\n");
										
											SX1278_WRITE_BUFFER(REG_LR_FIFOADDRPTR, 0x00);
											SX1278_RLEN = SX1278_READ_BUFFER(REG_LR_NBRXBYTES);//数据包长度
											
											SPI_CS_0;   
											SPI_WRITE_DATA(0x00);
											
											for (lora_rx_index = 0; lora_rx_index < SX1278_RLEN;lora_rx_index++) 
											{
													recv[lora_rx_index] = SPI_READ_DATA();												
											}
											
											SPI_CS_1;

											lora_rx = 1;//数据接收标志
											
									}
									SX1278LoRaSetOpMode(Stdby_mode);
									SX1278_WRITE_BUFFER(REG_LR_IRQFLAGSMASK, IRQN_RXD_Value); //打开接收中断
									SX1278_WRITE_BUFFER(REG_LR_HOPPERIOD, PACKET_MIAX_Value);
									SX1278_WRITE_BUFFER( REG_LR_DIOMAPPING1, 0X00);
									SX1278_WRITE_BUFFER( REG_LR_DIOMAPPING2, 0x00);
									SX1278LoRaSetOpMode(Receiver_mode);
							}
							else if ((RF_EX0_STATUS & 0x08) == 0x08)//发送完成，回到接收模式
							{
								//  printf("LORA 发送成功\r\n");												
									SX1278LoRaSetOpMode(Stdby_mode);
									SX1278_WRITE_BUFFER(REG_LR_IRQFLAGSMASK, IRQN_RXD_Value); //打开接收中断
									SX1278_WRITE_BUFFER(REG_LR_HOPPERIOD, PACKET_MIAX_Value);
									SX1278_WRITE_BUFFER( REG_LR_DIOMAPPING1, 0X00);
									SX1278_WRITE_BUFFER( REG_LR_DIOMAPPING2, 0x00);
									SX1278LoRaSetOpMode(Receiver_mode);	     	
							}
							else if ((RF_EX0_STATUS & 0x04) == 0x04) 
							{
									 printf("(RF_EX0_STATUS & 0x04) == 0x04\r\n");
								
									if ((RF_EX0_STATUS & 0x01) == 0x01) 
									{ 
											printf("(RF_EX0_STATUS & 0x01) == 0x01\r\n");
										SX1278LoRaSetOpMode(Stdby_mode);
										SX1278_WRITE_BUFFER(REG_LR_IRQFLAGSMASK, IRQN_RXD_Value); //打开接收中断
										SX1278_WRITE_BUFFER(REG_LR_HOPPERIOD, PACKET_MIAX_Value);
										SX1278_WRITE_BUFFER( REG_LR_DIOMAPPING1, 0X02);
										SX1278_WRITE_BUFFER( REG_LR_DIOMAPPING2, 0x00);
										SX1278LoRaSetOpMode(Receiver_mode);					
									} 
									else 
									{ 
										printf("(S1\r\n");										
										SX1278LoRaSetOpMode(Stdby_mode);
										SX1278_WRITE_BUFFER(REG_LR_IRQFLAGSMASK, IRQN_SEELP_Value); //打开接收中断
										SX1278_WRITE_BUFFER( REG_LR_DIOMAPPING1, 0X00);
										SX1278_WRITE_BUFFER( REG_LR_DIOMAPPING2, 0x00);
										SX1278LoRaSetOpMode(Receiver_mode);	
									}
					}
					i = 0;
					SX1278_WRITE_BUFFER( REG_LR_IRQFLAGS, 0xff);
			}


		if(lora_rx)//接收标志为1，表示收到无线数据
				{	
					
					 lora_rx = 0;//清除标志位
          			
           if(recv[lora_rx_index-1]=='\n'&&recv[lora_rx_index-2]=='\r'){
                

             if(recv[lora_rx_index-3]=='k'&&recv[lora_rx_index-4]=='o'){
						 
							 printf("  SEND OK\r\n");
						
							 
						 }else{
							       printf("\r\nloRa：");	
										 for(i=0;i<100;i++)	//清除接收缓存区
											 {
												 
												if(recv[i]>0)	printf("%c",recv[i]);
                        else break;
												 
												recv[i]=0;
											 }	
											printf("\r\n");		
											 

						       FUN_RF_SENDPACKET("ok\r\n",4);
						 }				 
					 }

           RS485_RX;					 
				}
}





