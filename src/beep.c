/*
* 文件说明：无源蜂鸣器操作
*/
#include "HC89S003F4.h"
#include "beep.h"
#include "tick.h"
#include "hc89s003_pwm.h"
#include "hc89s003_gpio.h"

static uint16_t buzzCounter = 0;	// 蜂鸣器间断性鸣叫的次数
static uint16_t startTick = 0;		// 鸣叫的时间戳
static uint16_t beepOnInterval = 0xff;
static uint16_t beepOffInterval = 0xff;
static uint8_t  buzzStatus = 0;		// 0-当前处于不发声状态，当前处于发声状态

#define BEEP_PIN	P0_0


#define BEEP_OFF()	do{PWM3C &= ~(PWM3_EN | PWM3_OUT_EN); BEEP_PIN = 0;}while(0)
#define BEEP_ON()	do{PWM3C |= (PWM3_EN | PWM3_OUT_EN);}while(0)


/*
 参数：n--蜂鸣器鸣叫的次数，0xffff表示不间断鸣叫; onInterval--响声的时长，offInterval--不响声的时长(单位100ms)
 返回：
 功能：蜂鸣器开始间断性鸣叫，
*/
void beepStartBuzz(uint16_t n, uint16_t onInterval, uint16_t offInterval)
{
	// 蜂鸣器已处于长鸣状态，不再接受新的控制
	if(buzzCounter != 0xffff)
	{
		BEEP_ON();
		startTick = getTick();
		buzzCounter = n;
		buzzStatus = 1;
		beepOnInterval = onInterval;
		beepOffInterval = offInterval;
	}
}

/*
 参数：
 返回：
 功能：蜂鸣器停止鸣叫
*/
void beepStopBuzz(void)
{
	BEEP_OFF();
	
	buzzCounter = 0;
	buzzStatus = 0;
}


/*
 参数：
 返回：
 功能：蜂鸣器任务
*/
void beepTask(void)
{
	uint16_t curTick = getTick();
	if(buzzCounter > 0)
	{
		if((1 == buzzStatus) && (curTick - startTick >= beepOnInterval))
		{			
			if(buzzCounter != 0xffff)
			{				
				buzzCounter--;
                BEEP_OFF();
			}
			startTick = curTick;
			buzzStatus = 0;			
		}
		else if((0 == buzzStatus) && (curTick - startTick >= beepOffInterval))
		{
			BEEP_ON();
			startTick = curTick;
			buzzStatus = 1;			
		}
	}
}

