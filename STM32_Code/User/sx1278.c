/*
		 SX1278����ģ��
�ز�Ƶ����(�Ĵ���ֵ):Frf(23:0) = 2^19 * RF(�ز�Ƶ��) / FXOSC(ʱ��32M)
��ص�ѹ��⣺��ͨ���Ĵ���RegLowBat���õ�����ֵ��ͨ���༭RegDioMapping�ɽ��ж��ź�ӳ��������һ��DIO�����ϡ�
CLKOUT���ã�ͨ���޸�RegDioMapping2�е�ClkOutλ��������DIO5����������ο�Ƶ�ʻ���l��
*/

#include "sx1278.h"

/*********************************************/

unsigned char Frequency[3] = { 0x6c, 0x80, 0x00 };//434Mhz �ز�Ƶ������            Frf(23:0) = 2^19 * RF(�ز�Ƶ��) / FXOSC(ʱ��32M)
unsigned char power_data[8] = { 0x80, 0x80, 0x80, 0x83, 0x86, 0x89, 0x8c, 0x8f };  //PA��������

/******************************

����ʣ�17dBm 0B10001111

��С���ʣ�-5.8dBm  0B00000000

******************************/


unsigned char powerValue = 7;

unsigned char SpreadingFactor = 7;  //��Ƶ����7-12�� ��Խ������Խ������ͨ�ž�������
unsigned char CodingRate = 1;        //1-4          ��Խ������Խ������ͨ�ž�������
unsigned char Bw_Frequency = 9;      //����6-9       ��Խ������Խ��
unsigned char RF_EX0_STATUS;
unsigned char CRC_Value;
unsigned char SX1278_RLEN;


void sx1278_gpio_config(void)
{
 GPIO_InitTypeDef GPIO_InitStructure;

   __HAL_RCC_SX1278_CLK_ENABLE();

	GPIO_InitStructure.Pin=SX1278_SCLK_PIN|SX1278_MOSI_PIN|SX1278_RST_PIN|SX1278_CS_PIN;             
	GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Pull=GPIO_PULLUP;
	GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_HIGH;	
	HAL_GPIO_Init(SX1278_PORT, &GPIO_InitStructure);	


	GPIO_InitStructure.Pin=SX1278_MISO_PIN;             
	GPIO_InitStructure.Mode=GPIO_MODE_INPUT;
	GPIO_InitStructure.Pull=GPIO_PULLUP;
	GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_HIGH;	
	HAL_GPIO_Init(SX1278_PORT, &GPIO_InitStructure);	
}

//============================================
void Delay200us()		//@11.0592MHz
{
	unsigned char i, j;

	i = 3;
	j = 35;
	do
	{
		while (--j);
	} while (--i);
}
//============================================
void Delay20ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	i = 1;
	j = 216;
	k = 35;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
//============================================
void Delay100ms()		//@11.0592MHz
{
	unsigned char i, j, k;


	i = 5;
	j = 52;
	k = 195;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
//--------------------------------------------------------------------//
//�� �� ���� void  SX1278LORA_INT(void) 
//��    �ܣ� ����SX1278ģ���ʼ��
//��ڲ����� 
//�� �� ֵ��
//------------------------------------
void  SX1278LORA_INT(void) 
{
	sx1278_gpio_config();

	SX1278_RESET(); //Lora��λ   
	
	SX1278LoRaSetOpMode(Sleep_mode);  											//����˯��ģʽ
	SX1278LoRaFsk(LORA_mode);	      												//������Ƶģʽ��ֻ����˯��ģʽ������
	SX1278LoRaSetOpMode(Stdby_mode);   											//������ͨģʽ
	
	SX1278_WRITE_BUFFER( REG_LR_DIOMAPPING1, GPIO_VARE_1);  //����DIOӳ�书��
	SX1278_WRITE_BUFFER( REG_LR_DIOMAPPING2, GPIO_VARE_2);
	
	SX1278LoRaSetRFFrequency();      												//�����ز�Ƶ��
	SX1278LoRaSetRFPower(powerValue);												//������ƵPA����
	
	SX1278LoRaSetSpreadingFactor(SpreadingFactor);	 				//������Ƶ����
	SX1278LoRaSetErrorCoding(CodingRate);		 								//������Ч���ݱ�
	SX1278LoRaSetPacketCrcOn(true);			  									//CRC У���
	SX1278LoRaSetSignalBandwidth(Bw_Frequency);	 						//������Ƶ����
	SX1278LoRaSetImplicitHeaderOn(false);										//ͬ��ͷ������ģʽ
	SX1278LoRaSetPayloadLength(0xff);//0x22 timeout�ж�
	SX1278LoRaSetSymbTimeout(0x3FF);
	SX1278LoRaSetMobileNode(true); 			 //�������Ż�
	RF_RECEIVE();                        //����Ϊ����ģʽ
}
//--------------------------------------------------------------------//
//�� �� ���� void  FUN_RF_SENDPACKET(unsigned char *RF_TRAN_P,	unsigned char LEN) 
//��    �ܣ� ����SX1278�������ݰ�
//��ڲ����� 
//�� �� ֵ��
//------------------------------------
void  FUN_RF_SENDPACKET(unsigned char *RF_TRAN_P,	unsigned char LEN) 
{
	unsigned char ASM_i;
	SX1278LoRaSetOpMode(Stdby_mode);					//��ͨģʽ
	SX1278_WRITE_BUFFER( REG_LR_HOPPERIOD, 0);	//����Ƶ������
	SX1278_WRITE_BUFFER(REG_LR_IRQFLAGSMASK, IRQN_TXD_Value);	//�򿪷����ж�
	SX1278_WRITE_BUFFER( REG_LR_PAYLOADLENGTH, LEN);	 //������ݰ�����
	SX1278_WRITE_BUFFER( REG_LR_FIFOTXBASEADDR, 0);    //������ʼTx����
	SX1278_WRITE_BUFFER( REG_LR_FIFOADDRPTR, 0);       //FIFO SPIָ��
	
	SPI_CS_0;    //lpTypefunc.lpSwitchEnStatus(enOpen);
	SPI_WRITE_DATA(0x80);	//lpTypefunc.lpByteWritefunc(0x80);

	for (ASM_i = 0; ASM_i < LEN; ASM_i++) {
		SPI_WRITE_DATA(*RF_TRAN_P);//lpTypefunc.lpByteWritefunc(*RF_TRAN_P);
		RF_TRAN_P++;
	}

	SPI_CS_1;	//lpTypefunc.lpSwitchEnStatus(enClose);
	SX1278_WRITE_BUFFER(REG_LR_DIOMAPPING1, 0x40);
	SX1278_WRITE_BUFFER(REG_LR_DIOMAPPING2, 0x00);
	SX1278LoRaSetOpMode(Transmitter_mode);   //����ģʽ

}

//--------------------------------------------------------------------//
//�� �� ���� void  RF_RECEIVE(void) 
//��    �ܣ� SX1278����ģʽ����
//��ڲ����� 
//�� �� ֵ��
//-----------------------------------
void  RF_RECEIVE(void) 
{
	SX1278LoRaSetOpMode(Stdby_mode);    //��ͨģʽ
	SX1278_WRITE_BUFFER(REG_LR_IRQFLAGSMASK, IRQN_RXD_Value);  //��ѡIRQ��־����   �򿪷����ж�
	SX1278_WRITE_BUFFER(REG_LR_HOPPERIOD, PACKET_MIAX_Value);  //���õ�Ƶ����
	SX1278_WRITE_BUFFER( REG_LR_DIOMAPPING1, 0X00);
	SX1278_WRITE_BUFFER( REG_LR_DIOMAPPING2, 0X00);
	SX1278LoRaSetOpMode(Receiver_mode);   //����ģʽ
}
//--------------------------------------------------------------------//0x01
//�� �� ���� SX1278LoRaSetOpMode(RFMode_SET opMode) 
//��    �ܣ� SX1278����ģʽ����             0x01
//��ڲ����� opMode,����ģʽ����    000˯��ģʽ    001����ģʽ    010Ƶ�ʺϳ���ת��TXƵ��    011����ģʽ    100Ƶ�ʺϳ���ת��RXƵ��    101����ģʽ
//�� �� ֵ�� ��
//------------------------------------
void  SX1278LoRaSetOpMode(RFMode_SET opMode) 
{
	unsigned char opModePrev;
	opModePrev = SX1278_READ_BUFFER(REG_LR_OPMODE);
	opModePrev &= 0xf8;
	opModePrev |= (unsigned char) opMode;
	SX1278_WRITE_BUFFER( REG_LR_OPMODE, opModePrev);
}
//--------------------------------------------------------------------//0x01
//�� �� ���� SX1278LoRaFsk(void)
//��    �ܣ� SX1278��Ƶ���ã�ֻ����˯��ģʽ������    ģʽ����  0FSKģʽ    1loraģʽ
//��ڲ����� 
//�� �� ֵ��
//------------------------------------
void  SX1278LoRaFsk(Debugging_fsk_ook opMode)
{
	unsigned char opModePrev;
	opModePrev = SX1278_READ_BUFFER(REG_LR_OPMODE);
	opModePrev &= 0x7F;
	opModePrev |= (unsigned char) opMode;
	SX1278_WRITE_BUFFER( REG_LR_OPMODE, opModePrev);
}
//--------------------------------------------------------------------//0x06---0x08
//�� �� ���� SX1278LoRaSetRFFrequency(void)
//��    �ܣ� SX1278��Ƶ�ز�Ƶ������
//��ڲ����� 
//�� �� ֵ��
//------------------------------------
void  SX1278LoRaSetRFFrequency(void)
{
	SX1278_WRITE_BUFFER( REG_LR_FRFMSB, Frequency[0]);//0x04��Ƶ�ز�Ƶ�������Чλ
	SX1278_WRITE_BUFFER( REG_LR_FRFMID, Frequency[1]);//0x07��Ƶ�ز�Ƶ���м���Чλ
	SX1278_WRITE_BUFFER( REG_LR_FRFLSB, Frequency[2]);//0x00��Ƶ�ز�Ƶ�������Чλ
}
//--------------------------------------------------------------------//0x4D    0x09=8C
//�� �� ���� SX1278LoRaSetRFPower(void)
//��    �ܣ� SX1278��ƵPA��������
//��ڲ����� 
//�� �� ֵ��
//------------------------------------
void  SX1278LoRaSetRFPower(unsigned char power) 
{
	SX1278_WRITE_BUFFER( REG_LR_PADAC, 0x87);
	SX1278_WRITE_BUFFER( REG_LR_PACONFIG, power_data[power]);
}
//--------------------------------------------------------------------//0x31
//�� �� ���� void  SX1276LoRaSetNbTrigPeaks(unsigned char value)
//��    �ܣ� SX1278�������ݰ��������ֵ
//��ڲ����� 
//�� �� ֵ��
//------------------------------------
void  SX1278LoRaSetNbTrigPeaks(unsigned char value)
{
	unsigned char RECVER_DAT;
	RECVER_DAT = SX1278_READ_BUFFER(REG_LR_PACKETCONFIG2);
	RECVER_DAT = (RECVER_DAT & 0xF8) | value;
	SX1278_WRITE_BUFFER(REG_LR_PACKETCONFIG2, RECVER_DAT);
}
//--------------------------------------------------------------------//0x1E
//�� �� ���� SX1278LoRaSetSpreadingFactor(unsigned char factor) 
//��    �ܣ� SX1278������Ƶ����    Ƶ��ƫ�������Чλ   ������1Dǰ��ȡ
//��ڲ����� 
//�� �� ֵ��
//------------------------------------
void  SX1278LoRaSetSpreadingFactor(unsigned char factor) 
{
	unsigned char RECVER_DAT;
	SX1278LoRaSetNbTrigPeaks(3);
	RECVER_DAT = SX1278_READ_BUFFER( REG_LR_MODEMCONFIG2);
	RECVER_DAT = (RECVER_DAT & RFLR_MODEMCONFIG2_SF_MASK) | (factor << 4);
	SX1278_WRITE_BUFFER( REG_LR_MODEMCONFIG2, RECVER_DAT);
}
//--------------------------------------------------------------------//0x1E
//�� �� ���� SX1278LoRaSetPacketCrcOn(BOOL enable) 
//��    �ܣ� SX1278  CRCУ������         Ƶ��ƫ�������Чλ
//��ڲ����� 
//�� �� ֵ��
//------------------------------------
void  SX1278LoRaSetPacketCrcOn(BOOL enable) 
{
	unsigned char RECVER_DAT;
	RECVER_DAT = SX1278_READ_BUFFER( REG_LR_MODEMCONFIG2);
	RECVER_DAT = (RECVER_DAT & RFLR_MODEMCONFIG2_RXPAYLOADCRC_MASK)	| (enable << 2);
	SX1278_WRITE_BUFFER( REG_LR_MODEMCONFIG2, RECVER_DAT);
}
//--------------------------------------------------------------------//0x1D
//�� �� ���� void  SX1278LoRaSetErrorCoding(unsigned char value) 
//��    �ܣ� SX1278��Ч���ݱ�         Ƶ��ƫ�������Чλ
//��ڲ����� 
//�� �� ֵ��
//------------------------------------
void  SX1278LoRaSetErrorCoding(unsigned char value) 
{
	unsigned char RECVER_DAT;
	RECVER_DAT = SX1278_READ_BUFFER( REG_LR_MODEMCONFIG1);
	RECVER_DAT = (RECVER_DAT & RFLR_MODEMCONFIG1_CODINGRATE_MASK)	| (value << 1);
	SX1278_WRITE_BUFFER( REG_LR_MODEMCONFIG1, RECVER_DAT);
// LoRaSettings.ErrorCoding = value;
}
//--------------------------------------------------------------------//0x1D
//�� �� ���� void  SX1278LoRaSetSignalBandwidth(unsigned char bw) 
//��    �ܣ� SX1278������Ƶ����        Ƶ��ƫ�������Чλ
//��ڲ����� 
//�� �� ֵ��
//------------------------------------
void  SX1278LoRaSetSignalBandwidth(unsigned char bw) 
{
	unsigned char RECVER_DAT;
	RECVER_DAT = SX1278_READ_BUFFER( REG_LR_MODEMCONFIG1);
	RECVER_DAT = (RECVER_DAT & RFLR_MODEMCONFIG1_BW_MASK) | (bw << 4);
	SX1278_WRITE_BUFFER( REG_LR_MODEMCONFIG1, RECVER_DAT);
// LoRaSettings.SignalBw = bw;
}
//--------------------------------------------------------------------//0x1D
//�� �� ���� void  SX1278LoRaSetImplicitHeaderOn(BOOL enable) 
//��    �ܣ� SX1278 ͬ��ͷΪ����ģʽ       Ƶ��ƫ�������Чλ
//��ڲ����� 
//�� �� ֵ��
//------------------------------------
void  SX1278LoRaSetImplicitHeaderOn(BOOL enable) 
{
	unsigned char RECVER_DAT;
	RECVER_DAT = SX1278_READ_BUFFER( REG_LR_MODEMCONFIG1);
	RECVER_DAT = (RECVER_DAT & RFLR_MODEMCONFIG1_IMPLICITHEADER_MASK)	| (enable);
	SX1278_WRITE_BUFFER( REG_LR_MODEMCONFIG1, RECVER_DAT);
}
//--------------------------------------------------------------------//0x22
//�� �� ���� void  SX1276LoRaSetPayloadLength(unsigned char value) 
//��    �ܣ� SX1278����LoRa���س���             TIMEOUT�ж�ģʽ���� RXģʽ��
//��ڲ����� 
//�� �� ֵ��
//------------------------------------
void  SX1278LoRaSetPayloadLength(unsigned char value) 
{
	SX1278_WRITE_BUFFER( REG_LR_PAYLOADLENGTH, value);
}
//--------------------------------------------------------------------//0x1E   0x1F
//�� �� ���� void  SX1278LoRaSetSymbTimeout(unsigned int value) 
//��    �ܣ� SX1278���ջ���ʱֵ
//��ڲ����� 
//�� �� ֵ��
//------------------------------------
void  SX1278LoRaSetSymbTimeout(unsigned int value) 
{
	unsigned char RECVER_DAT[2];
	RECVER_DAT[0] = SX1278_READ_BUFFER( REG_LR_MODEMCONFIG2);
	RECVER_DAT[1] = SX1278_READ_BUFFER( REG_LR_SYMBTIMEOUTLSB);
	RECVER_DAT[0] = (RECVER_DAT[0] & RFLR_MODEMCONFIG2_SYMBTIMEOUTMSB_MASK)	| ((value >> 8) & ~RFLR_MODEMCONFIG2_SYMBTIMEOUTMSB_MASK);
	RECVER_DAT[1] = value & 0xFF;
	SX1278_WRITE_BUFFER( REG_LR_MODEMCONFIG2, RECVER_DAT[0]);
	SX1278_WRITE_BUFFER( REG_LR_SYMBTIMEOUTLSB, RECVER_DAT[1]);
}
//--------------------------------------------------------------------//0x26
//�� �� ���� void  SX1276LoRaSetSymbTimeout(unsigned int value) 
//��    �ܣ� SX1278�����Ż�  ������ǰ���볤��
//��ڲ����� 
//�� �� ֵ��
//-----------------------------------
void  SX1278LoRaSetMobileNode(BOOL enable) 
{
	unsigned char RECVER_DAT;
	RECVER_DAT = SX1278_READ_BUFFER( REG_LR_MODEMCONFIG3);
	RECVER_DAT = (RECVER_DAT & RFLR_MODEMCONFIG3_MOBILE_NODE_MASK) | (enable << 3);
	SX1278_WRITE_BUFFER( REG_LR_MODEMCONFIG3, RECVER_DAT);
}
//--------------------------------------------------------------------//
//�� �� ���� SX1278_RESET(void)
//��    �ܣ� ��λSX1278
//��ڲ����� ��
//�� �� ֵ�� ��
//------------------------------------
void	SX1278_RESET(void)
{
		SX1278_RST_L;
		//��ʱ100uS���ϲ��ܳɹ���λ
	  Delay200us();Delay200us();
	  SX1278_RST_H;
	  Delay20ms();Delay20ms();
	  //��ʱ5mS���ϲ�������ͨ��
}
//======================================================================================
//--------------------------------------------------------------------//
//�� �� ���� SX1278_READ_BUFFER(void)
//��    �ܣ� ��SX1278��ȡһ���ֽ�
//��ڲ����� addr  ��ַ
//�� �� ֵ�� ��������
//------------------------------------
unsigned char	SX1278_READ_BUFFER(unsigned char	addr)
{
	unsigned char	readVAl;
		SPI_CS_0;
		SPI_WRITE_DATA(addr & 0x7F);		//д����   ��ַ
		readVAl = SPI_READ_DATA();      //������
		SPI_CS_1;
	  return(readVAl);
}
//--------------------------------------------------------------------//
//�� �� ���� SX1278_WRITE_BUFFER(uchar	addr,uchar buffer)
//��    �ܣ� ��SX1278д��һ�ֽ�����
//��ڲ����� addr  ��ַ   bufferд�������
//�� �� ֵ�� ��
//------------------------------------
void	SX1278_WRITE_BUFFER(unsigned char	addr,unsigned char buffer)
{
		SPI_CS_0;
		SPI_WRITE_DATA(addr | 0x80);		//д����   ��ַ
		SPI_WRITE_DATA(buffer);					//д������
		SPI_CS_1;
}
//--------------------------------------------------------------------//
//�� �� ���� SPI_WRITE_DATA(uchar DATA)
//��    �ܣ� ����FLASHָ�� \����
//��ڲ����� DATAΪҪͨ�ŷ��͵����ݣ�1�ֽڣ�
//�� �� ֵ�� ��
//------------------------------------
void	SPI_WRITE_DATA(unsigned char DATA)		//д����
{
     unsigned char	i;     
		for (i=0;i<8;i++)
		{
   
			SPI_CLK_0;	NOP();NOP();NOP();NOP();
            if((DATA<<i)&0x80)
			          SX1278_MOSI_H;	
            else
                SX1278_MOSI_L;
           NOP();NOP();NOP();NOP(); 
			SPI_CLK_1;NOP();NOP();	NOP();NOP();		
		}
}


//--------------------------------------------------------------------//
//�� �� ���� SPI_FLASH_READ_DATA()
//��    �ܣ� �Ӵ洢����������  8λ
//��ڲ����� ָ��
//�� �� ֵ�� ���ض�ȡ�����ݣ�1�ֽڣ�
//------------------------------------
unsigned char	SPI_READ_DATA()		           //������
{
   unsigned char	i,temp;
	
		for (i=0;i<8;i++)
		{
			SPI_CLK_1;	NOP();NOP();NOP();NOP();	
			SPI_CLK_0;	NOP();NOP();NOP();NOP();		  
			temp = temp<<1|SX1278_MISO_READ;//��MISO��ȡ����
            NOP();NOP();NOP();NOP();
		}
		SPI_CLK_1;NOP();NOP();
		return	temp;
}
//********************************************
//END
