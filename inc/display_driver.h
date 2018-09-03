/*
* 文件说明：断码液晶显示功能函数
*/
#ifndef DISPLAY_DRIVER_H
#define DISPLAY_DRIVER_H

#include "typedef.h"

#define SEG_B   BIT7
#define SEG_J   BIT6
#define SEG_C   BIT5
#define SEG_K   BIT4
#define SEG_A   BIT3
#define SEG_G   BIT2
#define SEG_D   BIT1
#define SEG_L   BIT0

#define SEG_H   BIT7
#define SEG_F   BIT6
#define SEG_M   BIT5
#define SEG_E   BIT4
#define SEG_I   BIT3

#define SEG_1I  BIT3
#define SEG_2I  BIT0
#define SEG_3I  BIT3

#define SEG_B3   BIT3
#define SEG_B2   BIT2
#define SEG_B1   BIT1
#define SEG_B0   BIT0

#define SEG_S1   BIT2
#define SEG_S2   BIT2
#define SEG_S3   BIT3
#define SEG_S4   BIT2
#define SEG_S5   BIT1
#define SEG_S6   BIT0

#define ICON_MIN        SEG_S1
#define ICON_CLOCK      SEG_S2
#define ICON_BT         SEG_S3
#define ICON_CELSIUS    (SEG_S4 | SEG_S6)
#define ICON_BAT_LV0    SEG_B0
#define ICON_BAT_LV1    (SEG_B0 | SEG_B1)
#define ICON_BAT_LV2    (SEG_B0 | SEG_B1 | SEG_B2)
#define ICON_BAT_LV3    (SEG_B0 | SEG_B1 | SEG_B2 | SEG_B3)

typedef enum{
    IconMin = 0,
    IconClock,
    IconBT,
    IconCelsius,
    IconBatLv0,
    IconBatLv1,
    IconBatLv2,
    IconBatLv3,
    IconMax
}Icon_t;

void displayNum(uint8_t n, char c);
void displayIcon(Icon_t icon, Bool_t flag);
void clearDisplayRam(void);
void updataDisplayRam(void);


#endif
