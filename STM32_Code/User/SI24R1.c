#include "SI24R1.h"


const u8  TX_ADDRESS[TX_ADR_WIDTH] = {0x0A,0x01,0x07,0x0E,0x01};  // ����һ����̬���͵�ַ

unsigned char rf_buffer[50];
unsigned char tx_buffer[32];

void SI24R1_Config(void)
{

  GPIO_InitTypeDef GPIO_InitStructure;

	__HAL_RCC_NRF_CLK_ENABLE();


	GPIO_InitStructure.Pin=CSN|MOSI|CE|SCK;             
	GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Pull=GPIO_PULLUP;
	GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_HIGH;	
	HAL_GPIO_Init(NRF_PORT, &GPIO_InitStructure);	
 

	GPIO_InitStructure.Pin=IRQ|MISO;             
	GPIO_InitStructure.Mode=GPIO_MODE_INPUT;
	GPIO_InitStructure.Pull=GPIO_PULLUP;
	GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_HIGH;	
	HAL_GPIO_Init(NRF_PORT, &GPIO_InitStructure);	

}



static u8 SPI_RW(u8 byte)
{
	u8 bit_ctr;
	for(bit_ctr=0; bit_ctr<8; bit_ctr++)
	{
		if(byte & 0x80)
		     MOSI_1;
		else
			   MOSI_0;
		
		byte = (byte << 1);                      
		SCK_1;                               
		byte |= READ_MISO;                        
		SCK_0;                               
	}
	return(byte);                              
}


/********************************************************
�������ܣ�SI24R1���ų�ʼ��                
��ڲ�������
����  ֵ����
*********************************************************/
void SI24R1_Init(void)
{
	SI24R1_Config();
	
	SCK_0; 													//SPIʱ��������
	CSN_1;				
	CE_0;				
	IRQ_1;
}


/********************************************************
�������ܣ�д�Ĵ�����ֵ�����ֽڣ�                
��ڲ�����reg:�Ĵ���ӳ���ַ����ʽ��WRITE_REG��reg��
					value:�Ĵ�����ֵ
����  ֵ��״̬�Ĵ�����ֵ
*********************************************************/
u8 SI24R1_Write_Reg(u8 reg, u8 value)
{
	u8 status;

	CSN_0;              
	status = SPI_RW(reg);				
	SPI_RW(value);
	CSN_1;  
	
	return(status);
}


/********************************************************
�������ܣ�д�Ĵ�����ֵ�����ֽڣ�                  
��ڲ�����reg:�Ĵ���ӳ���ַ����ʽ��WRITE_REG��reg��
					pBuf:д�����׵�ַ
					bytes:д�����ֽ���
����  ֵ��״̬�Ĵ�����ֵ
*********************************************************/
u8 SI24R1_Write_Buf(u8 reg, const u8 *pBuf, u8 bytes)
{
	u8 status,byte_ctr;

  CSN_0;                                			
  status = SPI_RW(reg);                          
  for(byte_ctr=0; byte_ctr<bytes; byte_ctr++)     
    SPI_RW(*pBuf++);
  CSN_1;    
	
  return(status);       
}							  					   


/********************************************************
�������ܣ���ȡ�Ĵ�����ֵ�����ֽڣ�                  
��ڲ�����reg:�Ĵ���ӳ���ַ����ʽ��READ_REG��reg��
����  ֵ���Ĵ���ֵ
*********************************************************/
u8 SI24R1_Read_Reg(u8 reg)
{
 	u8 value;

	CSN_0;  
	SPI_RW(reg);			
	value = SPI_RW(0);
	CSN_1;           

	return(value);
}


/********************************************************
�������ܣ���ȡ�Ĵ�����ֵ�����ֽڣ�                  
��ڲ�����reg:�Ĵ���ӳ���ַ��READ_REG��reg��
					pBuf:���ջ��������׵�ַ
					bytes:��ȡ�ֽ���
����  ֵ��״̬�Ĵ�����ֵ
*********************************************************/
u8 SI24R1_Read_Buf(u8 reg, u8 *pBuf, u8 bytes)
{
	u8 status,byte_ctr;

  CSN_0;                                     
  status = SPI_RW(reg);                           
  for(byte_ctr=0;byte_ctr<bytes;byte_ctr++) 
	pBuf[byte_ctr] = SPI_RW(0);                   //��ȡ���ݣ����ֽ���ǰ
  
	CSN_1;                                        

  return(status);    
}



/********************************************************
�������ܣ�SI24R1����ģʽ��ʼ��                      
��ڲ�������
����  ֵ����
*********************************************************/
void SI24R1_RX_Mode(void)
{
	CE_0;
	SI24R1_Write_Buf(NRF_WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH);	// �����豸����ͨ��0ʹ�úͷ����豸��ͬ�ķ��͵�ַ
	SI24R1_Write_Reg(NRF_WRITE_REG + EN_AA, 0x01);               						// ʹ�ܽ���ͨ��0�Զ�Ӧ��
	SI24R1_Write_Reg(NRF_WRITE_REG + EN_RXADDR, 0x01);           						// ʹ�ܽ���ͨ��0
	SI24R1_Write_Reg(NRF_WRITE_REG + RF_CH, 40);                 						// ѡ����Ƶͨ��0x40
	SI24R1_Write_Reg(NRF_WRITE_REG + RX_PW_P0, TX_PLOAD_WIDTH);  						// ����ͨ��0ѡ��ͷ���ͨ����ͬ��Ч���ݿ��
	SI24R1_Write_Reg(NRF_WRITE_REG + RF_SETUP, 0x0f);            						// ���ݴ�����2Mbps�����书��7dBm
	SI24R1_Write_Reg(NRF_WRITE_REG + CONFIG, 0x0f);              						// CRCʹ�ܣ�16λCRCУ�飬�ϵ磬����ģʽ
	SI24R1_Write_Reg(NRF_WRITE_REG + STATUS, 0xff);  												//������е��жϱ�־λ
	CE_1;                                            									// ����CE���������豸
}						


/********************************************************
�������ܣ�SI24R1����ģʽ��ʼ��                      
��ڲ�������
����  ֵ����
*********************************************************/
void SI24R1_TX_Mode(void)
{
	CE_0;
	SI24R1_Write_Buf(NRF_WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);     // д�뷢�͵�ַ
	SI24R1_Write_Buf(NRF_WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH);  // Ϊ��Ӧ������豸������ͨ��0��ַ�ͷ��͵�ַ��ͬ

	SI24R1_Write_Reg(NRF_WRITE_REG + EN_AA, 0x01);       											// ʹ�ܽ���ͨ��0�Զ�Ӧ��
	SI24R1_Write_Reg(NRF_WRITE_REG + EN_RXADDR, 0x01);   											// ʹ�ܽ���ͨ��0
	SI24R1_Write_Reg(NRF_WRITE_REG + SETUP_RETR, 0x0a);  											// �Զ��ط���ʱ�ȴ�250us+86us���Զ��ط�10��
	SI24R1_Write_Reg(NRF_WRITE_REG + RF_CH, 40);         											// ѡ����Ƶͨ��0x40
	SI24R1_Write_Reg(NRF_WRITE_REG + RF_SETUP, 0x0f);    											// ���ݴ�����2Mbps�����书��7dBm
	SI24R1_Write_Reg(NRF_WRITE_REG + CONFIG, 0x0e);      											// CRCʹ�ܣ�16λCRCУ�飬�ϵ�
	//CE = 1;
}


/********************************************************
�������ܣ���ȡ��������                       
��ڲ�����rxbuf:�������ݴ���׵�ַ
����  ֵ��0:���յ�����
          1:û�н��յ�����
*********************************************************/
u8 SI24R1_RxPacket(u8 *rxbuf)
{
	u8 state;
	state = SI24R1_Read_Reg(STATUS);  			                 //��ȡ״̬�Ĵ�����ֵ    	  
	SI24R1_Write_Reg(NRF_WRITE_REG+STATUS,state);               //���RX_DS�жϱ�־

	if(state & RX_DR)								                           //���յ�����
	{
	
		SI24R1_Read_Buf(RD_RX_PLOAD,rxbuf,TX_PLOAD_WIDTH);     //��ȡ����
		SI24R1_Write_Reg(FLUSH_RX,0xff);					              //���RX FIFO�Ĵ���
		return 0; 
	}	   
	return 1;                                                   //û�յ��κ�����
}


/********************************************************
�������ܣ�����һ�����ݰ�                      
��ڲ�����txbuf:Ҫ���͵�����
����  ֵ��0x10:�ﵽ����ط�����������ʧ�� 
          0x20:���ͳɹ�            
          0xff:����ʧ��                  
*********************************************************/
u8 SI24R1_TxPacket(u8 *txbuf)
{
	u8 state;
	
	CE_0;																										  //CE���ͣ�ʹ��SI24R1����
  SI24R1_Write_Buf(WR_TX_PLOAD, txbuf, TX_PLOAD_WIDTH);	    //д���ݵ�TX FIFO,32���ֽ�
 	CE_1;																										  //CE�øߣ�ʹ�ܷ���	   
	
	//while(READ_IRQ == 1);																				  //�ȴ��������
	
	state = SI24R1_Read_Reg(STATUS);  											  //��ȡ״̬�Ĵ�����ֵ	   
	SI24R1_Write_Reg(NRF_WRITE_REG+STATUS, state); 								//���TX_DS��MAX_RT�жϱ�־
	if(state&MAX_RT)																			    //�ﵽ����ط�����
	{
		SI24R1_Write_Reg(FLUSH_TX,0xff);										    //���TX FIFO�Ĵ��� 
		return MAX_RT; 
	}
	if(state&TX_DS)																			      //�������
	{
		return TX_DS;
	}
	return 0XFF;																						  //����ʧ��
}

