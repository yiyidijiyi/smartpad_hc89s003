/*
* 文件说明：hc89s003f4 timer4操作
*/
#ifndef HC89S003_TIMER4_H
#define HC89S003_TIMER4_H

#define TF4			((uint8_t)0x80)
#define TC4			((uint8_t)0x40)
#define T4PS_1		((uint8_t)0x00)
#define T4PS_8		((uint8_t)0x10)
#define T4PS_64		((uint8_t)0x20)
#define T4PS_256	((uint8_t)0x30)
#define T4M_MODE0	((uint8_t)0x00)
#define T4M_MODE1	((uint8_t)0x04)
#define T4M_MODE2	((uint8_t)0x08)
#define T4M_MODE3	((uint8_t)0x0c)
#define T4CLK_FOSC	((uint8_t)0x00)
#define T4CLK_EXT	((uint8_t)0x01)

#define ENABLE_T4()	do{T4CON |= 0x02;}while(0)
#define DISABLE_T4()	do{T4CON &= 0xfd;}while(0)



#endif
