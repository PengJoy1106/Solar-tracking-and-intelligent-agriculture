#ifndef __SX1278_H
#define __SX1278_H

#include "main.h"

#define __HAL_RCC_SX1278_CLK_ENABLE    __HAL_RCC_GPIOA_CLK_ENABLE
#define SX1278_PORT      GPIOA
#define SX1278_SCLK_PIN  GPIO_PIN_5
#define SX1278_MISO_PIN  GPIO_PIN_6
#define SX1278_MOSI_PIN  GPIO_PIN_7
#define SX1278_RST_PIN   GPIO_PIN_11
#define SX1278_CS_PIN    GPIO_PIN_12

#define SX1278_SCKL_H    HAL_GPIO_WritePin(SX1278_PORT, SX1278_SCLK_PIN, GPIO_PIN_SET)
#define SX1278_SCKL_L    HAL_GPIO_WritePin(SX1278_PORT, SX1278_SCLK_PIN, GPIO_PIN_RESET)
#define SX1278_MOSI_H    HAL_GPIO_WritePin(SX1278_PORT, SX1278_MOSI_PIN, GPIO_PIN_SET)
#define SX1278_MOSI_L    HAL_GPIO_WritePin(SX1278_PORT, SX1278_MOSI_PIN, GPIO_PIN_RESET)
#define SX1278_RST_H     HAL_GPIO_WritePin(SX1278_PORT, SX1278_RST_PIN, GPIO_PIN_SET)
#define SX1278_RST_L     HAL_GPIO_WritePin(SX1278_PORT, SX1278_RST_PIN, GPIO_PIN_RESET)
#define SX1278_CS_H      HAL_GPIO_WritePin(SX1278_PORT, SX1278_CS_PIN, GPIO_PIN_SET)
#define SX1278_CS_L      HAL_GPIO_WritePin(SX1278_PORT, SX1278_CS_PIN, GPIO_PIN_RESET)
#define SX1278_MISO_READ HAL_GPIO_ReadPin(SX1278_PORT,SX1278_MISO_PIN)

#define   SPI_CS_0          SX1278_CS_L
#define   SPI_CS_1          SX1278_CS_H
#define   SPI_CLK_0         SX1278_SCKL_L
#define   SPI_CLK_1         SX1278_SCKL_H
#define   SPI_MISO          SX1278_MISO_READ

#define NOP() __NOP()


//================================================================================================
//LoRaģ��Ĵ�����ַ����
#define REG_LR_FIFO                                  0x00     //FIFO�����������
 // Common settings  �������üĴ���
#define REG_LR_OPMODE                                0x01     //����ģʽ&LoRa/FSKѡ��
#define	REG_LR_BITRATEMSB														 0x02			//�����������Чλ
#define	REG_LR_BITRATELSB														 0x03			//�����������Чλ
#define REG_LR_BANDSETTING                           0x04			//Ƶ��ƫ����Чλ              04��05ΪƵ��ƫ����Чλ  Loraģʽû��

#define REG_LR_FRFMSB                                0x06 		//��Ƶ�ز�Ƶ��  �����Чλ
#define REG_LR_FRFMID                                0x07 		//��Ƶ�ز�Ƶ��  �м�λ
#define REG_LR_FRFLSB                                0x08  		//��Ƶ�ز�Ƶ��  �����Чλ
 // Tx settings  ������Ĵ���
#define REG_LR_PACONFIG                              0x09  		//PAѡ���������ʿ���
#define REG_LR_PARAMP                                0x0A  		//PAб��/б��ʱ��͵�����PLL�Ŀ���
#define REG_LR_OCP                                   0x0B  		//������������
 // Rx settings  ���ջ��Ĵ���
#define REG_LR_LNA                                   0x0C 		//LNA����		
 // LoRa registers
#define REG_LR_FIFOADDRPTR                           0x0D  		//FIFO SPIָ��
#define REG_LR_FIFOTXBASEADDR                        0x0E  		//��ʼTx����
#define REG_LR_FIFORXBASEADDR                        0x0F  		//��ʼRx���� 
#define REG_LR_FIFORXCURRENTADDR                     0x10  		//���������ݰ�����ʼ��ַ
#define REG_LR_IRQFLAGSMASK                          0x11   	//��ѡIRQ��־����
#define REG_LR_IRQFLAGS                              0x12 		//IRQ��־
#define REG_LR_NBRXBYTES                             0x13 		//���յ����ֽ���
#define REG_LR_RXHEADERCNTVALUEMSB                   0x14 		//���յ�����Ч��ͷ��  ��
#define REG_LR_RXHEADERCNTVALUELSB                   0x15 		//���յ�����Ч��ͷ��  ��
#define REG_LR_RXPACKETCNTVALUEMSB                   0x16 		//���յ�����Ч���ݰ���  ��
#define REG_LR_RXPACKETCNTVALUELSB                   0x17 		//���յ�����Ч���ݰ���  ��
#define REG_LR_MODEMSTAT                             0x18 		//LoRa���ƽ�����ֳ�״̬
#define REG_LR_PKTSNRVALUE                           0x19 		//���һ�����ݰ�������ȹ�ֵ
#define REG_LR_PKTRSSIVALUE                          0x1A 		//���һ�����ݰ���RSSI
#define REG_LR_RSSIVALUE                             0x1B 		//����RSSI
#define REG_LR_HOPCHANNEL                            0x1C 		//FHSS��ʼ�ŵ�
#define REG_LR_MODEMCONFIG1                          0x1D 		//���ƽ�������������1
#define REG_LR_MODEMCONFIG2                          0x1E 		//���ƽ�������������2
#define REG_LR_SYMBTIMEOUTLSB                        0x1F 		//���ջ���ʱֵ
#define REG_LR_PREAMBLEMSB                           0x20 		//ǰ���볤��  ��
#define REG_LR_PREAMBLELSB                           0x21 		//ǰ���볤��  ��
#define REG_LR_PAYLOADLENGTH                         0x22 		//LoRa���س���
#define REG_LR_PAYLOADMAXLENGTH                      0x23 		//LoRa���س������ֵ
//RC�����Ĵ���
#define REG_LR_HOPPERIOD                             0x24 		//FHSS��Ƶ����
//���ݰ�����Ĵ���
#define REG_LR_FIFORXBYTEADDR                        0x25			//FIFO�����д���ֽڵĵ�ַ
#define REG_LR_MODEMCONFIG3                          0x26			//���ƽ�������������3
#define REG_LR_SYNCCONFIG                            0x27			//ͬ����ʶ�����
#define REG_LR_SYNCVALUE1                            0x28			//ͬ�����ֽ�1
#define REG_LR_SYNCVALUE2                            0x29			//ͬ�����ֽ�2
#define REG_LR_SYNCVALUE3                            0x2A			//ͬ�����ֽ�3
#define REG_LR_SYNCVALUE4                            0x2B			//ͬ�����ֽ�4
#define REG_LR_SYNCVALUE5                            0x2C			//ͬ�����ֽ�5
#define REG_LR_SYNCVALUE6                            0x2D			//ͬ�����ֽ�6
#define REG_LR_SYNCVALUE7                            0x2E			//ͬ�����ֽ�7
#define REG_LR_SYNCVALUE8                            0x2F			//ͬ�����ֽ�8
#define REG_LR_PACKETCONFIG1                         0x30			//���ݰ�ģʽ����1
#define REG_LR_PACKETCONFIG2                         0x31			//���ݰ�ģʽ����2           ���ݰ����������Чֵ
//#define REG_LR_PAYLOADLENGTH                         0x32			//���س�������
#define REG_LR_NODEADRS                              0x33			//�ڵ��ַ
#define REG_LR_BROADCASTADRS                         0x34			//�㲥��ַ
#define REG_LR_FIFOTHRESH                            0x35			//FIFO��ֵ��TX��ʼ����
#define REG_LR_SEQCONFIG1                            0x36			//��������������1
#define REG_LR_SEQCONFIG2                            0x37			//��������������2
#define REG_LR_TIMERRESOL                            0x38			//��ʱ��1��2�ֱ��ʿ���
#define REG_LR_TIMER1COEF                            0x39			//��ʱ��1����
#define REG_LR_TIMER2COEF                            0x3A			//��ʱ��2����
#define REG_LR_IMAGECAL                              0x3B			//����У׼�������
#define REG_LR_TEMP                                  0x3C			//�¶ȴ�����ֵ
#define REG_LR_LOWBAT                                0x3D			//�͵���ָʾ����
#define REG_LR_IRQFLAGS1                             0x3E			//״̬�Ĵ�����PLL����״̬����ʱ��RSSI
#define REG_LR_IRQFLAGS2                             0x3F			//״̬�Ĵ�����FIFO�����׼���͵���
 // end of documented register in datasheet
 // I/O settings
#define REG_LR_DIOMAPPING1                           0x40			//DIO0��DIO3����ӳ��
#define REG_LR_DIOMAPPING2                           0x41			//DIO4��DIO5����ӳ�䡢ClkOutƵ��
 // Version
#define REG_LR_VERSION                               0x42			//оƬ�汾--�������ID
 // Additional settings
#define REG_LR_PLLHOP                                0x44			//���ƿ��ٵ�Ƶģʽ
#define REG_LR_TCXO                                  0x4B			//TCXO��XTAL��������
#define REG_LR_PADAC                                 0x4D			//PA����������
#define REG_LR_FORMERTEMP                            0x5B			//IQУ׼�����洢�¶�
#define REG_LR_BITRATEFRAC                           0x5D			//�����ʷ����С������
#define REG_LR_AGCREF                                0x61			//AGC��ֵ����
#define REG_LR_AGCTHRESH1                            0x62			//AGC��ֵ����
#define REG_LR_AGCTHRESH2                            0x63			//AGC��ֵ����
#define REG_LR_AGCTHRESH3                            0x64			//AGC��ֵ����
//================================================================================================

#define GPIO_VARE_1                                  0X00
#define GPIO_VARE_2                                  0X00
#define RFLR_MODEMCONFIG2_SF_MASK                    0x0f
#define RFLR_MODEMCONFIG1_CODINGRATE_MASK            0xF1 
#define RFLR_MODEMCONFIG2_RXPAYLOADCRC_MASK          0xFB 
#define RFLR_MODEMCONFIG1_BW_MASK                    0x0F 
#define RFLR_MODEMCONFIG1_IMPLICITHEADER_MASK        0xFE 
#define RFLR_MODEMCONFIG2_SYMBTIMEOUTMSB_MASK        0xfc
#define RFLR_MODEMCONFIG3_MOBILE_NODE_MASK           0xF7 

#define TIME_OUT_INT                                 0x80 
#define PACKET_RECVER_INT                            0x40 
#define CRC_ERROR_INT                                0x20 
#define RECVER_HEAR_INT                              0x10 
#define FIFO_SEND_OVER                               0x08 
#define RFLR_IRQFLAGS_CAD                            0x04 
#define RFLR_IRQFLAGS_FHSS                           0x02 
#define RFLR_IRQFLAGS_CADD                           0x01 

#define IRQN_TXD_Value                               0xF7
#define IRQN_RXD_Value                               0x9F
#define IRQN_CAD_Value                               0xFA
#define IRQN_SEELP_Value                             0xFF
#define PACKET_MIAX_Value                            0xff
//================================================================================================

typedef enum 
{
   Sleep_mode	        = (unsigned char)0x00, //˯��ģʽ
   Stdby_mode	        = (unsigned char)0x01, //����ģʽ
   TX_mode 	          = (unsigned char)0x02,//Ƶ�ʺϳ���ת����TXƵ��(FSTx)
   Transmitter_mode		= (unsigned char)0x03,//����ģʽ
   RF_mode 						= (unsigned char)0x04,//Ƶ�ʺϳ���ת����RXƵ��(FSRx)
   Receiver_mode			= (unsigned char)0x05,//����ģʽ
   receive_single			= (unsigned char)0x06,//Ԥ��
   CAD_mode						= (unsigned char)0x07,//Ԥ��
}RFMode_SET;

typedef enum 
{
   FSK_mode           = (unsigned char)0x00, 
   LORA_mode          = (unsigned char)0x80, 
}Debugging_fsk_ook;

typedef enum
{
	 false		=		0,
	 true			=		1
}BOOL;

typedef enum
{
		enOpen,
		enClose
}cmdEntype_t;

typedef enum
{
		rxOpen,
		txOpen
}cmdpaType_t;

typedef struct{
   void (*lpByteWritefunc)(unsigned char src);
   unsigned char (*lpByteReadfunc)();
   void (*lpSwitchEnStatus)(cmdEntype_t cmd);
//   void (*paSwitchCmdfunc)(cmdpaType_t cmd);
//   void (*lpRecvDataTousr)(unsigned char *lpbuf,unsigned short length);
}lpCtrlTypefunc_t;
//================================================================================================
extern unsigned char   RF_EX0_STATUS;

extern unsigned char   CRC_Value;
extern lpCtrlTypefunc_t lpTypefunc;
extern unsigned char   SX1278_RLEN;

extern unsigned char Frequency[3];
extern unsigned char powerValue;
extern unsigned char SpreadingFactor;    //7-12
extern unsigned char CodingRate ;        //1-4
extern unsigned char Bw_Frequency;      //6-9
extern unsigned char RF_EX0_STATUS;
extern unsigned char CRC_Value;
extern lpCtrlTypefunc_t ctrlTypefunc;
extern unsigned char SX1278_RLEN;

//================================================================================================
extern void sx1278_gpio_config(void);

extern void  SX1278LORA_INT(void) ;
extern void  FUN_RF_SENDPACKET(unsigned char *RF_TRAN_P,	unsigned char LEN);
extern void  RF_RECEIVE(void) ;
extern void  SX1278LoRaSetOpMode(RFMode_SET opMode);
extern void  SX1278LoRaFsk(Debugging_fsk_ook opMode);
extern void  SX1278LoRaSetRFFrequency(void);
extern void  SX1278LoRaSetRFPower(unsigned char power) ;
extern void  SX1276LoRaSetNbTrigPeaks(unsigned char value);
extern void  SX1278LoRaSetSpreadingFactor(unsigned char factor);
extern void  SX1278LoRaSetPacketCrcOn(BOOL enable) ;
extern void  SX1278LoRaSetErrorCoding(unsigned char value) ;
extern void  SX1278LoRaSetSignalBandwidth(unsigned char bw) ;
extern void  SX1278LoRaSetImplicitHeaderOn(BOOL enable) ;
extern void  SX1278LoRaSetPayloadLength(unsigned char value) ;
extern void  SX1278LoRaSetSymbTimeout(unsigned int value) ;
extern void  SX1278LoRaSetMobileNode(BOOL enable) ;
extern void	SX1278_RESET(void);
extern unsigned char	SX1278_READ_BUFFER(unsigned char	addr);
extern void	SX1278_WRITE_BUFFER(unsigned char	addr,unsigned char buffer);
extern void	SPI_WRITE_DATA(unsigned char DATA);		//д����	
extern unsigned char	SPI_READ_DATA(void);		           //������
//================================================================================================
#endif
