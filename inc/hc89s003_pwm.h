/*
* 文件说明：hc89s003f4 12位pwm模块，包括pwm0，1,2及互补的3路输出
*/
#ifndef HC89S003_12BITSPWM_H
#define HC89S003_12BITSPWM_H

#include "typedef.h"

// pwm0/1/2
#define ENABLE_PWM(module)   do{module |= 0x01;}while(0)
#define DISABLE_PWM(module)  do{module &= 0xfe;}while(0)

#define PWM_OUT_EN    ((uint8_t)0x02)
#define PWM_OUT_HH    ((uint8_t)0x0)       // pwm0输出高有效，pwm01输出高有效
#define PWM_OUT_HL    ((uint8_t)0x04)      // pwm0输出高有效，pwm01输出低有效
#define PWM_OUT_LH    ((uint8_t)0x08)      // pwm0输出低有效，pwm01输出高有效
#define PWM_OUT_LL    ((uint8_t)0x0c)      // pwm0输出低有效，pwm01输出低有效

#define PWM_CLK_FOSC_1     ((uint8_t)0x0)
#define PWM_CLK_FOSC_8     ((uint8_t)0x01)
#define PWM_CLK_FOSC_32    ((uint8_t)0x02)
#define PWM_CLK_FOSC_128   ((uint8_t)0x03)

// pwm3
#define ENABLE_PWM3()   do{PWM3C |= 0x80;}while(0)
#define DISABLE_PWM3()  do{PWM3C &= 0x7f;}while(0)

#define PWM3_EN				((uint8_t)0x80)
#define PWM3_OUT_EN         ((uint8_t)0x10)
#define PWM3_OUT_H          ((uint8_t)0x00)
#define PWM3_OUT_L          ((uint8_t)0x08)
#define PWM3_CLK_FOSC_1     ((uint8_t)0x0)
#define PWM3_CLK_FOSC_2     ((uint8_t)0x01)
#define PWM3_CLK_FOSC_4     ((uint8_t)0x02)
#define PWM3_CLK_FOSC_8     ((uint8_t)0x03)
#define PWM3_CLK_FOSC_16    ((uint8_t)0x04)
#define PWM3_CLK_FOSC_32    ((uint8_t)0x05)
#define PWM3_CLK_FOSC_64    ((uint8_t)0x06)
#define PWM3_CLK_FOSC_128   ((uint8_t)0x07)

//void setPwm0Period(uint16_t p);
//void setPwm1Period(uint16_t p);
//void setPwm2Period(uint16_t p);
void setPwm0Duty(uint16_t p);
void setPwm1Duty(uint16_t p);
void setPwm2Duty(uint16_t p);

void pwm0Config(void);
void pwm1Config(void);
void pwm2Config(void);
void pwm3Config(void);



#endif
