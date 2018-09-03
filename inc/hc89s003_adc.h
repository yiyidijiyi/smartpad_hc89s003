/*
* 文件说明：hc89s003f4 adc模块操作
*/
#ifndef HC89S003_ADC_H
#define HC89S003_ADC_H

#include "typedef.h"



#define VREF_OUT    (0x80)
#define VREF_EXTERN (0x40)
#define ADC_IF      (0x20)
#define INREF_VDD   (0x0)     
#define INREF_4V    (0x01)
#define INREF_3V    (0x02)
#define INREF_2V    (0x03)

#define ICH_DIS     (0x0)
#define ICH_1_4V    (0x40)
#define ICH_RESERVE (0x80)
#define ICH_GND     (0xc0)

#define ADCL_12BITS (0x0)
#define ADCL_10BITS (0x80)
#define ALIGN_0 (0x0)
#define ALIGN_1 (0x40) 

#define ADCTS_4M    (0x0)
#define ADCTS_2M    (0x10)
#define ADCTS_1M    (0x20)
#define ADC_CLK_FOSC_2  (0x0)
#define ADC_CLK_FOSC_4  (0x01)
#define ADC_CLK_FOSC_6  (0x02)
#define ADC_CLK_FOSC_8  (0x03)
#define ADC_CLK_FOSC_12 (0x04)
#define ADC_CLK_FOSC_16 (0x05)
#define ADC_CLK_FOSC_24 (0x06)
#define ADC_CLK_FOSC_32 (0x07)

#define AMW_EN  (0x80)
#define AMW_IF  (0x40)

typedef enum{
    Adc_12bits = 0x0f,
    Adc_10bis = 0x03
}AdcResult_t;

#define ENABLE_ADC()    do{ADCC0 |= 0x80;}while(0)
#define DISABLE_ADC()   do{ADCC0 &= 0x7f;}while(0)

#define START_CONVERT()   do{ADCC0 &= ~ADC_IF; ADCC0 |= 0x40;}while(0)
#define IS_CONVERT_COMPLETE() (ADCC0 & 0x40)
#define XCH_SEL(ch) do{ADCC1 = ch & 0x0f;}while(0);


void adcConfig(void);
uint16_t getAdcResult(AdcResult_t t);



#endif
