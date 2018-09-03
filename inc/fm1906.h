/*
* 文件说明：fm1906显示驱动
*/
#ifndef FM1906_H
#define FM1906_H

#include "typedef.h"
#include "HC89S003F4.h"
#include "hc89s003_gpio.h"
#include "intrins.h"

#define CS_PORT     P0
#define CS_PIN      GPIO_PIN_5
#define WR_PORT     P0
#define WR_PIN      GPIO_PIN_4
#define RD_PORT
#define RD_PIN
#define DATA_PORT   P0
#define DATA_PIN    GPIO_PIN_3


#define CS_H    do{P0_5 = 1;}while(0)
#define CS_L    do{P0_5 = 0;}while(0)
#define WR_H    do{P0_4 = 1;}while(0)
#define WR_L    do{P0_4 = 0;}while(0)
#define RD_H    
#define RD_L    
#define DATA_H  do{P0_3 = 1;}while(0)
#define DATA_L  do{P0_3 = 0;}while(0)

#define WAIT() do{uint8_t n = 399; for(; n > 0; n--);}while(0)

/*
// 命令操作100
#define FM1906_COMMAND  do{ \
    WR_L;   \
    DATA_H; \
    WAIT(); \
    WR_H;   \
    WAIT(); \
    WR_L;   \
    DATA_L; \
    WAIT(); \
    WR_H;   \
    WAIT(); \
    WR_L;   \
    DATA_L; \
    WAIT(); \
    WR_H;   \
    WAIT(); \
    } \
    while(0)
        
 // 写操作101
#define FM1906_WRITE    do{ \
    WR_L;   \
    DATA_H; \
    WAIT(); \
    WR_H;   \
    WAIT(); \
    WR_L;   \
    DATA_L; \
    WAIT(); \
    WR_H;   \
    WAIT(); \
    WR_L;   \
    DATA_H; \
    WAIT(); \
    WR_H;   \
    WAIT(); \
    } \
    while(0)

// 读改写操作，同读操作    
#define FM1906_READ_MODIFY_WRITE    FM1906_WIRTE
    
// 读操作110
#define FM1906_READ     do{ \
    WR_L;   \
    DATA_H; \
    WAIT(); \
    WR_H;   \
    WAIT(); \
    WR_L;   \
    DATA_H; \
    WAIT(); \
    WR_H;   \
    WAIT(); \
    WR_L;   \
    DATA_L; \
    WAIT(); \
    WR_H;   \
    WAIT(); \
    } \
    while(0)
 */
    
// FM1906的命令字，命令字总是12位的，其中前3位为命令码
// 100 0000 0000 x
#define CMD_SYS_DIS     ((uint16_t)0x8000)
// 100 0000 0001 x
#define CMD_SYS_EN      ((uint16_t)0x8020)
// 100 0000 0010 x
#define CMD_LCD_OFF     ((uint16_t)0x8040)
// 100 0000 0011 x      
#define CMD_LCD_ON      ((uint16_t)0x8060)
// 100 0000 0100 x
#define CMD_TIMER_DIS   ((uint16_t)0x8080)
// 100 0000 0110 x
#define CMD_TIMER_EN    ((uint16_t)0x80c0)
// 100 0000 0101 x
#define CMD_WDT_DIS     ((uint16_t)0x80a0)
// 100 0000 0111 x
#define CMD_WDT_EN      ((uint16_t)0x80e0)
// 100 0000 1000 x
#define CMD_TONE_OFF    ((uint16_t)0x8100)
// 100 0000 1001 x
#define CMD_TONE_ON     ((uint16_t)0x8120)
// 100 0000 11xx x
#define CMD_CLR_TIMER   ((uint16_t)0x8180)
// 100 0000 111x x
#define CMD_CLR_WDT     ((uint16_t)0x81c0)
// 100 0001 01xx x
#define CMD_XTAL32K     ((uint16_t)0x8280)
// 100 0001 10xx x
#define CMD_RC256K      ((uint16_t)0x8300)
// 100 0001 11xx x
#define CMD_EXT256K     ((uint16_t)0x8380)
// 100 0010 0000 0
#define CMD_BIAS_1_2    ((uint16_t)0x8400)
// 100 0010 0001 0
#define CMD_BIAS_1_3    ((uint16_t)0x8420)
// 100 0010 0000 0
#define CMD_COM_2       ((uint16_t)0x8400)
// 100 0010 0100 0
#define CMD_COM_3       ((uint16_t)0x8480)
// 100 0010 1000 0
#define CMD_COM_4       ((uint16_t)0x8500)
// 100 0100 0000 0
#define CMD_TONE_4K     ((uint16_t)0x8800)
// 100 0110 0000 0
#define CMD_TONE_2K     ((uint16_t)0x8c00)
// 100 1000 0000 0
#define CMD_IRQ_DIS     ((uint16_t)0x9000)
// 100 1000 1000 0  
#define CMD_IRQ_EN      ((uint16_t)0x9100)
// 100 1010 0000 0      
#define CMD_F1          ((uint16_t)0x9400)
// 100 1010 0001 0
#define CMD_F2          ((uint16_t)0x9420)
// 100 1010 0010 0
#define CMD_F4          ((uint16_t)0x9440)
// 100 1010 0011 0
#define CMD_F8          ((uint16_t)0x9460)
// 100 1010 0100 0
#define CMD_F16         ((uint16_t)0x9480)
// 100 1010 0101 0  
#define CMD_F32         ((uint16_t)0x94a0)
// 100 1010 0110 0
#define CMD_F64         ((uint16_t)0x94c0)
// 100 1010 0111 0
#define CMD_F128        ((uint16_t)0x94e0)
// 100 1110 0000 0
#define CMD_TEST        ((uint16_t)0x9c00)
// 100 1110 0011 0
#define CMD_NORMAL      ((uint16_t)0x9c60)


void fm1906WriteCmd(uint16_t cmd);
void fm1906WriteData(uint8_t addr, const uint8_t* buf, uint8_t bits);
void fm1906Config(void);

#endif
