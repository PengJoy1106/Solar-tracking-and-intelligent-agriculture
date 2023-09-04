#ifndef  __ESP8266_H
#define  __ESP8266_H
#include "app.h"       //头文件管理

#define esp8266_mode_set      0x00
#define esp8266_rst           0x01
#define esp8266_connect_wifi  0x02
#define esp8266_connect_tcps  0x03
#define esp8266_usart_set     0x04
#define esp8266_usart_go      0x05
#define eps8266_config_ok     0x06

extern unsigned int  cnt_esp8266;
extern unsigned char status_esp8266;
extern unsigned char ok_esp8266;   //通信成功标志
extern unsigned char save_index;
extern unsigned char set_update;
extern void esp8266_usart_isr(void);
extern void esp8266_sta_connect(void);
extern void esp8266_ap_connect(void);
extern void esp8266_exit_cipsend(void);


extern unsigned int  cnt_app_wifi;
extern void uart_set_net_info(void);

#endif
