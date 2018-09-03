/*
* 文件说明：hc89s003f4看门狗模块
*/
#ifndef HC89S003_WDT_H
#define HC89S003_WDT_H

#include "typedef.h"

#define WDT_DIV_8       (0x0)
#define WDT_DIV_16      (0x01)
#define WDT_DIV_32      (0x02)
#define WDT_DIV_64      (0x03)
#define WDT_DIV_128     (0x04)
#define WDT_DIV_256     (0x05)
#define WDT_DIV_512     (0x06)
#define WDT_DIV_1024    (0x07)

#define ENABLE_WDT()    do{WDTC |= 0x40;}while(0)
#define DISABLE_WDT()   do{WDTC &= ~0x40; WDTCCR = 0;}while(0)
#define CLEAR_WDT()     do{WDTC |= 0x10;}while(0)
#define ENABLE_WDT_PD()    do{WDTC |= 0x08;}while(0)
#define DISABLE_WDT_PD()    do{WDTC &= ~0x08;}while(0)
#define SET_WDT_DIV(div)    do{uint8_t tmp = WDTC; tmp &= ~0x07; tmp |= div; WDTC = tmp;}while(0)
#define SET_WDT_CCR(val)    do{WDTCCR = val;}while(0)

void startWdt(void);
void WDTConfig(uint8_t div, uint8_t ccr);

#endif
