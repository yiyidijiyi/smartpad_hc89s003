/*
 最后修改：2018-05-06 by syf
 功能描述：按键扫描，与状态切换
*/
#include "typedef.h"
#include "key.h"
#include "alarm.h"
#include "beep.h"
#include "board.h"
#include "common.h"
#include "tick.h"
#include "HC89S003F4.h"

#define KEY_STATE (P2_7)

static uint8_t keyPressFlag = 0;	// 按键状态
static uint8_t lastKeyValue = KEY_NONE;
static uint16_t keyPressedTick = 0;	// 检测到按键被按下时的时刻
static uint16_t keyTaskTick = 0;
static uint16_t lowTemperatureTick = 0;
static uint8_t lowTemperatureFlag = 0;

RunState_t runState = FreeRunState;
static uint16_t settingAlarmTick = 0;	// 判断退出闹钟设定，进入闹钟倒计时的时间戳


/*
 参数：
 返回：当前按键值
 功能：按键扫描程序
*/	
static uint8_t keyScan(void)
{
	uint16_t curTick = getTick();
	uint16_t incTick = 0;
	uint8_t keyValue = KEY_NONE;
	
	if(0 == KEY_STATE)	// 按键为按下状态
	{
		if(0 == keyPressFlag)
		{
			// 按键刚被按下
			keyPressFlag = 1;
			keyPressedTick = curTick;
		}
		else
		{
			// 长按键判断
			incTick = curTick - keyPressedTick;
			if(incTick >= KEY_DELAY_2S)
			{
				keyValue = KEY_ALARM;
			}
			
			if(incTick >= KEY_DELAY_4S)
			{
				keyValue = KEY_POWER_OFF;
			}
		}
	}
	else	// 按键为弹起状态
	{
		if(1 == keyPressFlag)
		{
			incTick = curTick - keyPressedTick;
			if(incTick < KEY_DELAY_2S)
			{
				keyValue = KEY_SHORT_PRESS;
			}
		}
		
		keyPressFlag = 0;
	}
	
	// 避免重复的长按键值
	switch(keyValue)
	{
		case KEY_ALARM:
			if(lastKeyValue == KEY_ALARM)
			{
				keyValue = KEY_NONE;
			}
			else
			{
				lastKeyValue = keyValue;
			}
			break;
		case KEY_POWER_OFF:
			if(lastKeyValue == KEY_POWER_OFF)
			{
				keyValue = KEY_NONE;
			}
			else
			{
				lastKeyValue = keyValue;
			}
			break;
		case KEY_SHORT_PRESS:
		case KEY_NONE:
		default:
			lastKeyValue = keyValue;
			break;
	}
	
	return keyValue;
}

/*
 参数：
 返回：
 功能：根据按键操作，处理FreeRunState时的工作
*/	
static void processFreeRunState(uint8_t key)
{
	uint16_t curTick = getTick();
	
	if(getTemperature() <= MIN_TEMPERATURE)
	{
		if(0 == lowTemperatureFlag)
		{
			lowTemperatureTick = curTick;
			lowTemperatureFlag = 1;
		}
	}
	else
	{
		lowTemperatureFlag = 0;
	}
	
	switch(key)
	{
		case KEY_POWER_OFF:
			runState = ShutDownState;
			//powerOff();
			break;
		case KEY_ALARM:
			// 进入闹钟设定状态，蜂鸣器响一次
			clearAlarmMinutes();
			beepStartBuzz(1, ELAPSED_TIME_200_MS, ELAPSED_TIME_500_MS);
			settingAlarmTick = curTick;
			runState = SettingAlarmState;
			break;
		case KEY_SHORT_PRESS:
			break;
		case KEY_NONE:
			if((1 == lowTemperatureFlag) && (curTick - lowTemperatureTick >= ELAPSED_TIME_1_MINUTE))
			{
				// 温度小于50摄氏度，持续时间超过1分钟
				runState = ShutDownState;
			}
		default:
			break;
	}
}

/*
 参数：
 返回：
 功能：根据按键操作，处理SetttingAlarmState时的工作
*/
static void processSettingAlarmState(uint8_t key)
{
	uint16_t curTick = getTick();
	switch(key)
	{
		case KEY_POWER_OFF:
			runState = ShutDownState;
			//powerOff();
			break;
		case KEY_ALARM:
			// 清除闹钟，蜂鸣器响一次
			clearAlarmMinutes();
			beepStartBuzz(1, ELAPSED_TIME_300_MS, ELAPSED_TIME_500_MS);
			runState = FreeRunState;
			break;
		case KEY_SHORT_PRESS:
			// 闹钟设定分钟数增1
			incAlarmMinutes();
			settingAlarmTick = getTick();
			break;
		case KEY_NONE:
			// 3秒钟无按键，退出SettingAlarmState，蜂鸣器响一次
			if(curTick - settingAlarmTick >= ELAPSED_TIME_5_SECOND)
			{
				if(getAlarmMinutes() > 0)
				{
					// 设定的闹钟大于1分钟，进入AlarmCountDown状态
					runState = AlarmCountDownState;					
				}
				else
				{
					// 设定的闹钟为0，进入FreeRunState
					runState = FreeRunState;
				}
				
				beepStartBuzz(1, ELAPSED_TIME_300_MS, ELAPSED_TIME_500_MS);
			}
			break;
		default:
				break;
	}
}

/*
 参数：
 返回：
 功能：根据按键操作，处理AlarmCountDown时的工作
*/
static void processAlarmCountDownState(uint8_t key)
{
	switch(key)
	{
		case KEY_POWER_OFF:
			runState = ShutDownState;
			//powerOff();
			break;
		case KEY_ALARM:
			// 清除闹钟，蜂鸣器响一次
			clearAlarmMinutes();
			beepStartBuzz(1, ELAPSED_TIME_300_MS, ELAPSED_TIME_500_MS);
			runState = FreeRunState;
			break;
		case KEY_SHORT_PRESS:
		case KEY_NONE:
		default:
				break;
	}
	
	if(AlarmCountDownState == runState)
	{
		alarmCountDown();
		
		// 闹钟倒计时结束，蜂鸣器响3次
		if(0 == getAlarmMinutes())
		{
			runState = FreeRunState;
			beepStartBuzz(3, ELAPSED_TIME_300_MS, ELAPSED_TIME_700_MS);
		}
	}
}


/*
 参数：
 返回：
 功能：按键任务，由于设备的运行状态是由按键改变的，因此把状态切换也放入此任务中
*/	
void keyTask(void)
{
	uint16_t curTick = getTick();
	uint8_t key = KEY_NONE;
	
	// system变化时才检测按键
	if(keyTaskTick != curTick)
	{
		keyTaskTick = curTick;
		
		key = keyScan();

// 用于测试按键功能是否正常		
//		switch(key)
//		{
//			case KEY_SHORT_PRESS:
//				dbg_printf("key short!\r\n");
//				break;
//			case KEY_ALARM:
//				dbg_printf("key alarm!\r\n");
//				break;
//			case KEY_POWER_OFF:
//				dbg_printf("key power off!\r\n");
//				break;
//			default:break;
//		}
		
		switch(runState)
		{
			case FreeRunState:
				processFreeRunState(key);
				break;
			case SettingAlarmState:
				processSettingAlarmState(key);
				break;
			case AlarmCountDownState:
				processAlarmCountDownState(key);
				break;
			case ShutDownState:
				break;
			default:
				break;
		}
	}
}

/*
 参数：
 返回：
 功能：电源自锁管理任务
*/	
void powerTask(void)
{
	if(ShutDownState == runState)
	{
		powerOff();
	}
}




// end of file
