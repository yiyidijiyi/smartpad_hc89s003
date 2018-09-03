/*
* 文件说明：hc89s003f4串口操作
*/
#ifndef HC89S003_UART_H
#define	HC89S003_UART_H

#include "typedef.h"


#define SCON_FE		((uint8_t)0x80)
#define SCON_RXROV	((uint8_t)0x40)
#define SCON_TXCOL	((uint8_t)0x20)
#define SCON_REN	((uint8_t)0x10)
#define SCON_TB8	((uint8_t)0x08)
#define SCON_RB8	((uint8_t)0x04)
#define SCON_TI		((uint8_t)0x02)
#define SCON_RI		((uint8_t)0x01)

#define SCON2_SMOD	((uint8_t)0x80)
#define SCON2_UX6	((uint8_t)0x20)
#define SCON2_MODE0	((uint8_t)0x00)
#define SCON2_MODE1	((uint8_t)0x02)
#define SCON2_MODE2	((uint8_t)0x04)
#define SCON2_MODE3	((uint8_t)0x06)
#define SCON2_SM2	((uint8_t)0x01)

#define ENABLE_UART1_RX()	do{SCON |= SCON_REN;}while(0)
#define DISABLE_UART1_RX()	do{SCON &= ~SCON_REN;}while(0)

void uart1Config(void);



#endif
