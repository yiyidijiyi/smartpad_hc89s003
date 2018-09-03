/*
* 文件说明：
*/
#ifndef BOARD_H
#define BOARD_H

#include "HC89S003F4.h"
#include "typedef.h"
#include "mcu_config.h"
#include "hc89s003_gpio.h"
#include "hc89s003_delay.h"
#include "hc89s003_adc.h"
#include "hc89s003_timer3.h"
#include "hc89s003_pwm.h"
#include "hc89s003_uart.h"
#include "hc89s003_flash.h"
#include "hc89s003_wdt.h"
#include "display_driver.h"
#include "fm1906.h"
#include "comm.h"


typedef enum{
	BatteryVoltage = 1,
	Temperature = 2
}AdcChannel_t;

typedef enum{
	BatteryVoltageLv0,
	BatteryVoltageLv1,
	BatteryVoltageLv2,
	BatteryVoltageLv3
}BatteryVoltageLv_t;

void initWdt(void);
void initGpio(void);
void initAdc(void);
void initTimer(void);
void initLEDControl(void);
void initBeepControl(void);
void initUart(void);
void initLcdDriver(void);
void initTemperatureMeasure(void);
void switchAdcChannel(void);


void powerOn(void);
void powerOff(void);
void setRGB(uint8_t r, uint8_t g, uint8_t b, uint16_t brightness);
uint8_t getBatteryVoltageLv(void);
int16_t getTemperature(void);


#endif


