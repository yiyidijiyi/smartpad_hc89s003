/*
 最后修改：2018-05-06 by syf
 功能描述：闹钟操作
*/

#include "alarm.h"
#include "common.h"
#include "tick.h"

static uint8_t alarmMinutes = 0;		// 定时的分钟数0-99
static uint16_t alarmTick = 0;			// 闹钟倒计时工作时的时间戳

/*
 参数：
 返回：
 功能：获取闹钟倒计时剩余分钟数
*/
uint8_t getAlarmMinutes(void)
{
	return alarmMinutes;
}

/*
 参数：
 返回：
 功能：清除设定的闹钟
*/
void clearAlarmMinutes(void)
{
	alarmMinutes = 0;
}

/*
 参数：
 返回：
 功能：闹钟分钟数增加1
*/
void incAlarmMinutes(void)
{
	alarmTick = getTick();
	
	if(alarmMinutes < MAX_ALARM_MINUTES)
	{
		alarmMinutes++;
	}
	else
	{
		alarmMinutes = 0;
	}
}

/*
 参数：
 返回：
 功能：闹钟倒计时工作
*/
void alarmCountDown(void)
{
	uint16_t curTick = getTick();
	
	if(curTick - alarmTick >= ELAPSED_TIME_1_MINUTE)
	{
		alarmTick = curTick;
		
		if(alarmMinutes > 0)
		{
			alarmMinutes--;
		}
	}
}

// end of file
