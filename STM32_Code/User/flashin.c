#include "flashin.h"


unsigned short  bit16[30];

 


/***********
�������ñ����ڵ�63K�ռ��У���ʼ��ַΪ((uint32_t)0x0800FC00)��
�������ñ����ڵ�63K�ռ��У���ʼ��ַΪ((uint32_t)0x0800FC00)��

�������ô洢��ʽ��                         
setflag+                                                                  1�ֽ�  0x0800F800
passward[6]+                                                              6�ֽ�  0x0800F802--0x0800F807
systemconfig[10]+                                                         10�ֽ� 0x0800F808--0x0800F811
number0[11]                                                               12�ֽ� 0x0800F812--0x0800F81D

����洢��ʽ��   
number1[11]+number2[11]+number3[11]+number4[11]+number5[11]+              60�ֽ� 0x0800FC00+0x0800FC47
police1[11]+police2[11]+police3[11]+police4[11]+police5[11]+              60�ֽ� 0x0800FC48+0x0800FC83
white1[11]+white2[11]+white3[11]+white4[11]+white5[11]                    60�ֽ� 0x0800FC84+0x0800FCBF

˵����
��setflagΪ0x00,��˵���Ѿ����ù�����
��setflagΪ0xff,��ʾ��δ�����������ã��ɽ�Ĭ������д��

systemconfig[10]=in1[1]+in2[1]+in3[1]+in4[1]+out1[1]+out2[1]+alarm[1]+lamp[1]+Ԥ��[2]

***********/



/*
��ʱģʽ�洢�ڵ�64K����ʼ��ַΪ((uint32_t)0x0800FC00)��
��ռ��4�ֽڣ���ʱ����ռ��2�ֽڣ�����Ƿ�Ϊ��һ���ϵ�1�ֽڣ���7�ֽڡ���0x0800FC00~0x0800FC06;

*/


uint8_t Flash_Buf[Flash_Buf_Max];

/**
*@brief  	��ҳ����
*@param		Address: ������ʼҳ��ַ
*@param		NbPage: ����ҳ��
*@return	��
*/
void FlashIn_Erase_Page(uint32_t Start_Addr,uint8_t NbPage)
{
  uint32_t PageError = 0; 
	FLASH_EraseInitTypeDef EraseInitStruct;
	
	HAL_FLASH_Unlock();	
				
  EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
	
  EraseInitStruct.PageAddress = Start_Addr;
	
  EraseInitStruct.NbPages = NbPage;
	
  HAL_FLASHEx_Erase(&EraseInitStruct,&PageError);
	
	HAL_FLASH_Lock(); 
}
/**
*@brief  	���ֽڶ�ȡ�ڲ�flash
*@param		Address: ��ȡ��ַ
*@return	��ַ���洢��ֵ
*/
static void FlashIn_Write_Byte(__IO uint32_t Address,uint8_t datas)
{  
	 *(__IO uint8_t *)Address=datas;  
}




void FlashIn_Write_NByte(__IO uint32_t Address,uint8_t* datas,uint8_t NByte)
{
  uint8_t i;
	
   HAL_FLASH_Unlock();	
	
	for(i=0;i<NByte;i+=2){
	  
		
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,Address+i,(*(datas+1)<<8)|*(datas));
	  //printf("temp=0x%x\r\n",(*(datas+1)<<8)|*(datas));
	  datas+=2;
		
	}
	
  HAL_FLASH_Lock();			
}

/**
*@brief  	���ֽڶ�ȡ�ڲ�flash
*@param		Address: ��ȡ��ַ
*@return	��ַ���洢��ֵ
*/
static uint8_t FlashIn_Read_Byte(__IO uint32_t Address)
{  
	return *(__IO uint8_t *)Address;  
}



/**
*@brief  	���ֽڶ�ȡ�ڲ�flash
*@param		Address: ��ȡ��ʼ��ַ
*@param   NByte  ����ȡ�ֽ����������ڻ�������
*@return	��
*/
void FlashIn_Read_NByte(uint32_t Start_Addr,uint16_t NByte)
{
	 uint16_t i;
   if(NByte>=Flash_Buf_Max) NByte=Flash_Buf_Max-1;
		 
	 for(i=0;i<NByte;i++)   			 
			 {
				 Flash_Buf[i]=FlashIn_Read_Byte(Start_Addr++);	
        // printf("flash_buf=%x\r\n",Flash_Buf[i]);
			 }
}

uint32_t Get_UDID(void)
{
			
	FlashIn_Read_NByte((uint32_t)0x1FFFF7AC,12);//UDID���ڵĵ�ַ
	
//	printf(">>>ALL_UDID=%02x%02x%02x%02x%02x%02x",Flash_Buf[11],Flash_Buf[10],Flash_Buf[9],Flash_Buf[8],Flash_Buf[7],Flash_Buf[6]);
//	printf("%02x%02x%02x%02x%02x%02x\r\n",Flash_Buf[5],Flash_Buf[4],Flash_Buf[3],Flash_Buf[2],Flash_Buf[1],Flash_Buf[0]);
//  return  *(__IO uint32_t *)(0x1FFFF7AC); 	
	return  (uint32_t)Flash_Buf[5]<<24|(uint32_t)Flash_Buf[2]<<16|(uint32_t)Flash_Buf[4]<<8|(uint32_t)Flash_Buf[0];
}




void bit8tobit16(unsigned char* bit8,unsigned short* bit16,unsigned char bit8len)
{
 unsigned char bit16h=0,bit16l=0;
		
	
	while((*bit8)&&(bit8len))
	{
	 bit16h=*bit8;
	// usart_txdat(2,*bit8);
	 bit8++;
	 bit16l=*bit8;		
	// usart_txdat(2,*bit8);
	// usart_txdat(2,0x0a);	
   *bit16=bit16l<<8|bit16h;//����STM32flash��д˳�����С���ȳ�
		
	 bit8++;
   bit16++;	
   bit8len--; 		
	}
}


