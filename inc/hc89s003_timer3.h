/*
* 文件说明：hc89s003f4 timer3模块操作
*/
#ifndef HC89S003_TIMER3_H
#define HC89S003_TIMER3_H

#include "typedef.h"
#include "hc89s003_int.h"

#define ENABLE_TIMER3()     do{T3CON |= 0x04;}while(0)
#define DISABLE_TIMER3()    do{T3CON &= ~0x04;}while(0)

// 掉电运行使能与禁止
#define ENABLE_TIMER_PD()     do{T3CON |= 0x40;}while(0)
#define DISABLE_TIMER3_PD()    do{T3CON &= ~0x40;}while(0)

// 控制寄存器位定义
// timer3时钟源选择位
#define T3_CLK_FOSC     ((uint8_t)0x0)
#define T3_CLK_EXTERNAL ((uint8_t)0x01)
#define T3_CLK_LXTAL    ((uint8_t)0x02)

// timer3时钟源预分频系数定义
#define T3_PS_1     ((uint8_t)0x0) 
#define T3_PS_8     ((uint8_t)0x10)
#define T3_PS_64    ((uint8_t)0x20)
#define T3_PS_256   ((uint8_t)0x30)

void setTimer3ReloadCounter(uint16_t v);
void timer3InterruptConfig(FlagStatus_t status, IntPriority_t pri);
void timer3Config(void);


#endif
