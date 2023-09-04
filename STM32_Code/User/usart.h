#ifndef  __USART_H
#define  __USART_H

#include "system.h"

#define UART1_PORT GPIOA
#define TXD1  GPIO_PIN_9
#define RXD1  GPIO_PIN_10

#define UART2_PORT GPIOA
#define TXD2  GPIO_PIN_14
#define RXD2  GPIO_PIN_15

#define UART1 0x01
#define UART2 0x02

extern unsigned char  rx_temp[100],uart_temp[10];
extern unsigned char  rx_temp2[100];

extern uint8_t  rx_update,rx_flag;

extern uint16_t rx_index,rx_index2;


extern void usart_sentdata(unsigned char uart,unsigned char ch);
extern void usart_sentstring(unsigned char uart,uint8_t *s);

extern UART_HandleTypeDef UART1_Handle;
extern UART_HandleTypeDef UART2_Handle;

extern void Usart_Config(void);

static void UART_DMA_Config(UART_HandleTypeDef *huart);

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);

extern void USART_Config(void);

extern unsigned char *str2str(const unsigned char *str1, const unsigned char *str2);

extern void wipe_buffer(unsigned char* temp,unsigned short len);


#endif
