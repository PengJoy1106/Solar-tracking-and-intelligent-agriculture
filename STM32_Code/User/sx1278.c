/*
		 SX1278函数模块
载波频率设(寄存器值):Frf(23:0) = 2^19 * RF(载波频率) / FXOSC(时钟32M)
电池低压检测：可通过寄存器RegLowBat设置调整阀值，通过编辑RegDioMapping可将中断信号映射至任意一个DIO引脚上。
CLKOUT设置：通过修改RegDioMapping2中的ClkOut位，可以在DIO5引脚上输出参考频率或分頻。
*/

#include "sx1278.h"

/*********************************************/

unsigned char Frequency[3] = { 0x6c, 0x80, 0x00 };//434Mhz 载波频率设置            Frf(23:0) = 2^19 * RF(载波频率) / FXOSC(时钟32M)
unsigned char power_data[8] = { 0x80, 0x80, 0x80, 0x83, 0x86, 0x89, 0x8c, 0x8f };  //PA功率设置

/******************************

最大功率：17dBm 0B10001111

最小功率：-5.8dBm  0B00000000

******************************/


unsigned char powerValue = 7;

unsigned char SpreadingFactor = 7;  //扩频因子7-12， 调越高速率越慢，但通信距离增大
unsigned char CodingRate = 1;        //1-4          调越高速率越慢，但通信距离增大
unsigned char Bw_Frequency = 9;      //带宽6-9       调越高速率越快
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
//函 数 名： void  SX1278LORA_INT(void) 
//功    能： 设置SX1278模块初始化
//入口参数： 
//返 回 值：
//------------------------------------
void  SX1278LORA_INT(void) 
{
	sx1278_gpio_config();

	SX1278_RESET(); //Lora复位   
	
	SX1278LoRaSetOpMode(Sleep_mode);  											//设置睡眠模式
	SX1278LoRaFsk(LORA_mode);	      												//设置扩频模式，只能在睡眠模式下设置
	SX1278LoRaSetOpMode(Stdby_mode);   											//设置普通模式
	
	SX1278_WRITE_BUFFER( REG_LR_DIOMAPPING1, GPIO_VARE_1);  //设置DIO映射功能
	SX1278_WRITE_BUFFER( REG_LR_DIOMAPPING2, GPIO_VARE_2);
	
	SX1278LoRaSetRFFrequency();      												//设置载波频率
	SX1278LoRaSetRFPower(powerValue);												//设置射频PA功率
	
	SX1278LoRaSetSpreadingFactor(SpreadingFactor);	 				//设置扩频因子
	SX1278LoRaSetErrorCoding(CodingRate);		 								//设置有效数据比
	SX1278LoRaSetPacketCrcOn(true);			  									//CRC 校验打开
	SX1278LoRaSetSignalBandwidth(Bw_Frequency);	 						//设置扩频带宽
	SX1278LoRaSetImplicitHeaderOn(false);										//同步头是显性模式
	SX1278LoRaSetPayloadLength(0xff);//0x22 timeout中断
	SX1278LoRaSetSymbTimeout(0x3FF);
	SX1278LoRaSetMobileNode(true); 			 //低数据优化
	RF_RECEIVE();                        //设置为接收模式
}
//--------------------------------------------------------------------//
//函 数 名： void  FUN_RF_SENDPACKET(unsigned char *RF_TRAN_P,	unsigned char LEN) 
//功    能： 设置SX1278发送数据包
//入口参数： 
//返 回 值：
//------------------------------------
void  FUN_RF_SENDPACKET(unsigned char *RF_TRAN_P,	unsigned char LEN) 
{
	unsigned char ASM_i;
	SX1278LoRaSetOpMode(Stdby_mode);					//普通模式
	SX1278_WRITE_BUFFER( REG_LR_HOPPERIOD, 0);	//不做频率跳变
	SX1278_WRITE_BUFFER(REG_LR_IRQFLAGSMASK, IRQN_TXD_Value);	//打开发送中断
	SX1278_WRITE_BUFFER( REG_LR_PAYLOADLENGTH, LEN);	 //最大数据包设置
	SX1278_WRITE_BUFFER( REG_LR_FIFOTXBASEADDR, 0);    //设置起始Tx数据
	SX1278_WRITE_BUFFER( REG_LR_FIFOADDRPTR, 0);       //FIFO SPI指针
	
	SPI_CS_0;    //lpTypefunc.lpSwitchEnStatus(enOpen);
	SPI_WRITE_DATA(0x80);	//lpTypefunc.lpByteWritefunc(0x80);

	for (ASM_i = 0; ASM_i < LEN; ASM_i++) {
		SPI_WRITE_DATA(*RF_TRAN_P);//lpTypefunc.lpByteWritefunc(*RF_TRAN_P);
		RF_TRAN_P++;
	}

	SPI_CS_1;	//lpTypefunc.lpSwitchEnStatus(enClose);
	SX1278_WRITE_BUFFER(REG_LR_DIOMAPPING1, 0x40);
	SX1278_WRITE_BUFFER(REG_LR_DIOMAPPING2, 0x00);
	SX1278LoRaSetOpMode(Transmitter_mode);   //发送模式

}

//--------------------------------------------------------------------//
//函 数 名： void  RF_RECEIVE(void) 
//功    能： SX1278接收模式设置
//入口参数： 
//返 回 值：
//-----------------------------------
void  RF_RECEIVE(void) 
{
	SX1278LoRaSetOpMode(Stdby_mode);    //普通模式
	SX1278_WRITE_BUFFER(REG_LR_IRQFLAGSMASK, IRQN_RXD_Value);  //可选IRQ标志屏蔽   打开发送中断
	SX1278_WRITE_BUFFER(REG_LR_HOPPERIOD, PACKET_MIAX_Value);  //设置调频周期
	SX1278_WRITE_BUFFER( REG_LR_DIOMAPPING1, 0X00);
	SX1278_WRITE_BUFFER( REG_LR_DIOMAPPING2, 0X00);
	SX1278LoRaSetOpMode(Receiver_mode);   //接收模式
}
//--------------------------------------------------------------------//0x01
//函 数 名： SX1278LoRaSetOpMode(RFMode_SET opMode) 
//功    能： SX1278运行模式设置             0x01
//入口参数： opMode,运行模式参数    000睡眠模式    001待机模式    010频率合成器转至TX频率    011发送模式    100频率合成器转至RX频率    101接收模式
//返 回 值： 无
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
//函 数 名： SX1278LoRaFsk(void)
//功    能： SX1278扩频设置，只能在睡眠模式下设置    模式设置  0FSK模式    1lora模式
//入口参数： 
//返 回 值：
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
//函 数 名： SX1278LoRaSetRFFrequency(void)
//功    能： SX1278射频载波频率设置
//入口参数： 
//返 回 值：
//------------------------------------
void  SX1278LoRaSetRFFrequency(void)
{
	SX1278_WRITE_BUFFER( REG_LR_FRFMSB, Frequency[0]);//0x04射频载波频率最高有效位
	SX1278_WRITE_BUFFER( REG_LR_FRFMID, Frequency[1]);//0x07射频载波频率中间有效位
	SX1278_WRITE_BUFFER( REG_LR_FRFLSB, Frequency[2]);//0x00射频载波频率最低有效位
}
//--------------------------------------------------------------------//0x4D    0x09=8C
//函 数 名： SX1278LoRaSetRFPower(void)
//功    能： SX1278射频PA功率设置
//入口参数： 
//返 回 值：
//------------------------------------
void  SX1278LoRaSetRFPower(unsigned char power) 
{
	SX1278_WRITE_BUFFER( REG_LR_PADAC, 0x87);
	SX1278_WRITE_BUFFER( REG_LR_PACONFIG, power_data[power]);
}
//--------------------------------------------------------------------//0x31
//函 数 名： void  SX1276LoRaSetNbTrigPeaks(unsigned char value)
//功    能： SX1278设置数据包长度最高值
//入口参数： 
//返 回 值：
//------------------------------------
void  SX1278LoRaSetNbTrigPeaks(unsigned char value)
{
	unsigned char RECVER_DAT;
	RECVER_DAT = SX1278_READ_BUFFER(REG_LR_PACKETCONFIG2);
	RECVER_DAT = (RECVER_DAT & 0xF8) | value;
	SX1278_WRITE_BUFFER(REG_LR_PACKETCONFIG2, RECVER_DAT);
}
//--------------------------------------------------------------------//0x1E
//函 数 名： SX1278LoRaSetSpreadingFactor(unsigned char factor) 
//功    能： SX1278设置扩频因子    频率偏移最高有效位   必须在1D前读取
//入口参数： 
//返 回 值：
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
//函 数 名： SX1278LoRaSetPacketCrcOn(BOOL enable) 
//功    能： SX1278  CRC校验设置         频率偏移最低有效位
//入口参数： 
//返 回 值：
//------------------------------------
void  SX1278LoRaSetPacketCrcOn(BOOL enable) 
{
	unsigned char RECVER_DAT;
	RECVER_DAT = SX1278_READ_BUFFER( REG_LR_MODEMCONFIG2);
	RECVER_DAT = (RECVER_DAT & RFLR_MODEMCONFIG2_RXPAYLOADCRC_MASK)	| (enable << 2);
	SX1278_WRITE_BUFFER( REG_LR_MODEMCONFIG2, RECVER_DAT);
}
//--------------------------------------------------------------------//0x1D
//函 数 名： void  SX1278LoRaSetErrorCoding(unsigned char value) 
//功    能： SX1278有效数据比         频率偏移最高有效位
//入口参数： 
//返 回 值：
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
//函 数 名： void  SX1278LoRaSetSignalBandwidth(unsigned char bw) 
//功    能： SX1278设置扩频带宽        频率偏移最低有效位
//入口参数： 
//返 回 值：
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
//函 数 名： void  SX1278LoRaSetImplicitHeaderOn(BOOL enable) 
//功    能： SX1278 同步头为显性模式       频率偏移最低有效位
//入口参数： 
//返 回 值：
//------------------------------------
void  SX1278LoRaSetImplicitHeaderOn(BOOL enable) 
{
	unsigned char RECVER_DAT;
	RECVER_DAT = SX1278_READ_BUFFER( REG_LR_MODEMCONFIG1);
	RECVER_DAT = (RECVER_DAT & RFLR_MODEMCONFIG1_IMPLICITHEADER_MASK)	| (enable);
	SX1278_WRITE_BUFFER( REG_LR_MODEMCONFIG1, RECVER_DAT);
}
//--------------------------------------------------------------------//0x22
//函 数 名： void  SX1276LoRaSetPayloadLength(unsigned char value) 
//功    能： SX1278设置LoRa负载长度             TIMEOUT中断模式设置 RX模式下
//入口参数： 
//返 回 值：
//------------------------------------
void  SX1278LoRaSetPayloadLength(unsigned char value) 
{
	SX1278_WRITE_BUFFER( REG_LR_PAYLOADLENGTH, value);
}
//--------------------------------------------------------------------//0x1E   0x1F
//函 数 名： void  SX1278LoRaSetSymbTimeout(unsigned int value) 
//功    能： SX1278接收机超时值
//入口参数： 
//返 回 值：
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
//函 数 名： void  SX1276LoRaSetSymbTimeout(unsigned int value) 
//功    能： SX1278数据优化  待发送前导码长度
//入口参数： 
//返 回 值：
//-----------------------------------
void  SX1278LoRaSetMobileNode(BOOL enable) 
{
	unsigned char RECVER_DAT;
	RECVER_DAT = SX1278_READ_BUFFER( REG_LR_MODEMCONFIG3);
	RECVER_DAT = (RECVER_DAT & RFLR_MODEMCONFIG3_MOBILE_NODE_MASK) | (enable << 3);
	SX1278_WRITE_BUFFER( REG_LR_MODEMCONFIG3, RECVER_DAT);
}
//--------------------------------------------------------------------//
//函 数 名： SX1278_RESET(void)
//功    能： 复位SX1278
//入口参数： 无
//返 回 值： 无
//------------------------------------
void	SX1278_RESET(void)
{
		SX1278_RST_L;
		//延时100uS以上才能成功复位
	  Delay200us();Delay200us();
	  SX1278_RST_H;
	  Delay20ms();Delay20ms();
	  //延时5mS以上才能正常通信
}
//======================================================================================
//--------------------------------------------------------------------//
//函 数 名： SX1278_READ_BUFFER(void)
//功    能： 从SX1278读取一个字节
//入口参数： addr  地址
//返 回 值： 读出数据
//------------------------------------
unsigned char	SX1278_READ_BUFFER(unsigned char	addr)
{
	unsigned char	readVAl;
		SPI_CS_0;
		SPI_WRITE_DATA(addr & 0x7F);		//写数据   地址
		readVAl = SPI_READ_DATA();      //读数据
		SPI_CS_1;
	  return(readVAl);
}
//--------------------------------------------------------------------//
//函 数 名： SX1278_WRITE_BUFFER(uchar	addr,uchar buffer)
//功    能： 忘SX1278写入一字节数据
//入口参数： addr  地址   buffer写入的数据
//返 回 值： 无
//------------------------------------
void	SX1278_WRITE_BUFFER(unsigned char	addr,unsigned char buffer)
{
		SPI_CS_0;
		SPI_WRITE_DATA(addr | 0x80);		//写数据   地址
		SPI_WRITE_DATA(buffer);					//写入数据
		SPI_CS_1;
}
//--------------------------------------------------------------------//
//函 数 名： SPI_WRITE_DATA(uchar DATA)
//功    能： 发送FLASH指令 \数据
//入口参数： DATA为要通信发送的数据（1字节）
//返 回 值： 无
//------------------------------------
void	SPI_WRITE_DATA(unsigned char DATA)		//写数据
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
//函 数 名： SPI_FLASH_READ_DATA()
//功    能： 从存储器接收数据  8位
//入口参数： 指令
//返 回 值： 返回读取的数据（1字节）
//------------------------------------
unsigned char	SPI_READ_DATA()		           //读数据
{
   unsigned char	i,temp;
	
		for (i=0;i<8;i++)
		{
			SPI_CLK_1;	NOP();NOP();NOP();NOP();	
			SPI_CLK_0;	NOP();NOP();NOP();NOP();		  
			temp = temp<<1|SX1278_MISO_READ;//从MISO读取数据
            NOP();NOP();NOP();NOP();
		}
		SPI_CLK_1;NOP();NOP();
		return	temp;
}
//********************************************
//END
