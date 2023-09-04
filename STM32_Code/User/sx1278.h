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
//LoRa模块寄存器地址定义
#define REG_LR_FIFO                                  0x00     //FIFO数据输入输出
 // Common settings  常规设置寄存器
#define REG_LR_OPMODE                                0x01     //运行模式&LoRa/FSK选择
#define	REG_LR_BITRATEMSB														 0x02			//比特率最高有效位
#define	REG_LR_BITRATELSB														 0x03			//比特率最低有效位
#define REG_LR_BANDSETTING                           0x04			//频率偏移有效位              04和05为频率偏移有效位  Lora模式没用

#define REG_LR_FRFMSB                                0x06 		//射频载波频率  最高有效位
#define REG_LR_FRFMID                                0x07 		//射频载波频率  中间位
#define REG_LR_FRFLSB                                0x08  		//射频载波频率  最低有效位
 // Tx settings  发射机寄存器
#define REG_LR_PACONFIG                              0x09  		//PA选择和输出功率控制
#define REG_LR_PARAMP                                0x0A  		//PA斜升/斜降时间和低相噪PLL的控制
#define REG_LR_OCP                                   0x0B  		//过流保护控制
 // Rx settings  接收机寄存器
#define REG_LR_LNA                                   0x0C 		//LNA设置		
 // LoRa registers
#define REG_LR_FIFOADDRPTR                           0x0D  		//FIFO SPI指针
#define REG_LR_FIFOTXBASEADDR                        0x0E  		//起始Tx数据
#define REG_LR_FIFORXBASEADDR                        0x0F  		//起始Rx数据 
#define REG_LR_FIFORXCURRENTADDR                     0x10  		//最后接收数据包的起始地址
#define REG_LR_IRQFLAGSMASK                          0x11   	//可选IRQ标志屏蔽
#define REG_LR_IRQFLAGS                              0x12 		//IRQ标志
#define REG_LR_NBRXBYTES                             0x13 		//接收到的字节数
#define REG_LR_RXHEADERCNTVALUEMSB                   0x14 		//接收到的有效报头数  高
#define REG_LR_RXHEADERCNTVALUELSB                   0x15 		//接收到的有效报头数  低
#define REG_LR_RXPACKETCNTVALUEMSB                   0x16 		//接收到的有效数据包数  高
#define REG_LR_RXPACKETCNTVALUELSB                   0x17 		//接收到的有效数据包数  低
#define REG_LR_MODEMSTAT                             0x18 		//LoRa调制解调器现场状态
#define REG_LR_PKTSNRVALUE                           0x19 		//最后一个数据包的信噪比估值
#define REG_LR_PKTRSSIVALUE                          0x1A 		//最后一个数据包的RSSI
#define REG_LR_RSSIVALUE                             0x1B 		//电流RSSI
#define REG_LR_HOPCHANNEL                            0x1C 		//FHSS起始信道
#define REG_LR_MODEMCONFIG1                          0x1D 		//调制解调器物理层配置1
#define REG_LR_MODEMCONFIG2                          0x1E 		//调制解调器物理层配置2
#define REG_LR_SYMBTIMEOUTLSB                        0x1F 		//接收机超时值
#define REG_LR_PREAMBLEMSB                           0x20 		//前导码长度  高
#define REG_LR_PREAMBLELSB                           0x21 		//前导码长度  低
#define REG_LR_PAYLOADLENGTH                         0x22 		//LoRa负载长度
#define REG_LR_PAYLOADMAXLENGTH                      0x23 		//LoRa负载长度最大值
//RC振荡器寄存器
#define REG_LR_HOPPERIOD                             0x24 		//FHSS跳频周期
//数据包处理寄存器
#define REG_LR_FIFORXBYTEADDR                        0x25			//FIFO中最后写入字节的地址
#define REG_LR_MODEMCONFIG3                          0x26			//调制解调器物理层配置3
#define REG_LR_SYNCCONFIG                            0x27			//同步字识别控制
#define REG_LR_SYNCVALUE1                            0x28			//同步字字节1
#define REG_LR_SYNCVALUE2                            0x29			//同步字字节2
#define REG_LR_SYNCVALUE3                            0x2A			//同步字字节3
#define REG_LR_SYNCVALUE4                            0x2B			//同步字字节4
#define REG_LR_SYNCVALUE5                            0x2C			//同步字字节5
#define REG_LR_SYNCVALUE6                            0x2D			//同步字字节6
#define REG_LR_SYNCVALUE7                            0x2E			//同步字字节7
#define REG_LR_SYNCVALUE8                            0x2F			//同步字字节8
#define REG_LR_PACKETCONFIG1                         0x30			//数据包模式设置1
#define REG_LR_PACKETCONFIG2                         0x31			//数据包模式设置2           数据包长度最高有效值
//#define REG_LR_PAYLOADLENGTH                         0x32			//负载长度设置
#define REG_LR_NODEADRS                              0x33			//节点地址
#define REG_LR_BROADCASTADRS                         0x34			//广播地址
#define REG_LR_FIFOTHRESH                            0x35			//FIFO阀值、TX起始条件
#define REG_LR_SEQCONFIG1                            0x36			//顶级定序器设置1
#define REG_LR_SEQCONFIG2                            0x37			//顶级定序器设置2
#define REG_LR_TIMERRESOL                            0x38			//定时器1和2分辨率控制
#define REG_LR_TIMER1COEF                            0x39			//定时器1设置
#define REG_LR_TIMER2COEF                            0x3A			//定时器2设置
#define REG_LR_IMAGECAL                              0x3B			//镜像校准引擎控制
#define REG_LR_TEMP                                  0x3C			//温度传感器值
#define REG_LR_LOWBAT                                0x3D			//低电量指示设置
#define REG_LR_IRQFLAGS1                             0x3E			//状态寄存器：PLL锁定状态、超时、RSSI
#define REG_LR_IRQFLAGS2                             0x3F			//状态寄存器：FIFO处理标准、低电量
 // end of documented register in datasheet
 // I/O settings
#define REG_LR_DIOMAPPING1                           0x40			//DIO0到DIO3引脚映射
#define REG_LR_DIOMAPPING2                           0x41			//DIO4到DIO5引脚映射、ClkOut频率
 // Version
#define REG_LR_VERSION                               0x42			//芯片版本--相关升特ID
 // Additional settings
#define REG_LR_PLLHOP                                0x44			//控制快速调频模式
#define REG_LR_TCXO                                  0x4B			//TCXO或XTAL输入设置
#define REG_LR_PADAC                                 0x4D			//PA更大功率设置
#define REG_LR_FORMERTEMP                            0x5B			//IQ校准器件存储温度
#define REG_LR_BITRATEFRAC                           0x5D			//比特率分配比小数部分
#define REG_LR_AGCREF                                0x61			//AGC阀值调整
#define REG_LR_AGCTHRESH1                            0x62			//AGC阀值调整
#define REG_LR_AGCTHRESH2                            0x63			//AGC阀值调整
#define REG_LR_AGCTHRESH3                            0x64			//AGC阀值调整
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
   Sleep_mode	        = (unsigned char)0x00, //睡眠模式
   Stdby_mode	        = (unsigned char)0x01, //待机模式
   TX_mode 	          = (unsigned char)0x02,//频率合成器转换至TX频率(FSTx)
   Transmitter_mode		= (unsigned char)0x03,//发送模式
   RF_mode 						= (unsigned char)0x04,//频率合成器转换至RX频率(FSRx)
   Receiver_mode			= (unsigned char)0x05,//接收模式
   receive_single			= (unsigned char)0x06,//预留
   CAD_mode						= (unsigned char)0x07,//预留
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
extern void	SPI_WRITE_DATA(unsigned char DATA);		//写数据	
extern unsigned char	SPI_READ_DATA(void);		           //读数据
//================================================================================================
#endif
