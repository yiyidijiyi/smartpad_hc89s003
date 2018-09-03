/*
* 文件说明：hc89s003f4 GPIO模块
*/
#ifndef HC89S003_GPIO_H
#define HC89S003_GPIO_H

#include "typedef.h"

#define GPIO_P0 ((uint8_t)0x0)
#define GPIO_P1 ((uint8_t)0x01)
#define GPIO_P2 ((uint8_t)0x02)

#define GPIO_PIN_0  ((uint8_t)0x01)
#define GPIO_PIN_1  ((uint8_t)0x02)
#define GPIO_PIN_2  ((uint8_t)0x04)
#define GPIO_PIN_3  ((uint8_t)0x08)
#define GPIO_PIN_4  ((uint8_t)0x10)
#define GPIO_PIN_5  ((uint8_t)0x20)
#define GPIO_PIN_6  ((uint8_t)0x40)
#define GPIO_PIN_7  ((uint8_t)0x80)


#define RES_50K     ((uint8_t)0x00)
#define RES_100K    ((uint8_t)0x10)
#define RES_150K    ((uint8_t)0x20)
#define RES_300K    ((uint8_t)0x30)

#define DBCLK_FOSC_1    ((uint8_t)0x0)
#define DBCLK_FOSC_4    ((uint8_t)0x01)
#define DBCLK_FOSC_16   ((uint8_t)0x02)
#define DBCLK_FOSC_64   ((uint8_t)0x03)

typedef enum{
    Input_NonSchmitt = 0,
    Input_PullDown_NonSchmitt = 0x01,
    Input_PullUp_NonSchmitt = 0x02,
    Analog = 0x03,
    Input_Schmitt = 0x04,
    Input_PullDowen_Schmitt = 0x05,
    Input_PullUp_Schmitt = 0x06,
    Output_PP = 0x08,
    Output_OD = 0x09,
    Output_PullUp_OD = 0x0a
}GPIOMode_t;


#define GPIO_PIN_MAP(reg, port, pin) do{reg = (port << 4) + pin;}while(0)
#define PULLUP_RES_SEL(res) do{P0LPU = res;}while(0)
#define DBCLK_SET(reg, clk, count) do{reg = clk + (count & 0x1f);}while(0)


void gpioConfig(uint8_t port, uint8_t pins, GPIOMode_t mode);


#endif 
