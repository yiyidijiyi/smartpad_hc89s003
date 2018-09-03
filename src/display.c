/*
 最后修改：2018-05-06 by syf
 功能描述：跟当前运行任务，处理显示对应的显示工作
*/
#include "display.h"
#include "typedef.h"
#include "display_driver.h"
#include "tick.h"
#include "common.h"
#include "key.h"
#include "board.h"
#include "alarm.h"


extern RunState_t runState;

/*
 参数：
 返回：
 功能：显示温度值
*/
static void displayTemperature(int16_t t)
{
    uint8_t b = 0;
    uint8_t s = 0;
    
    if(t < 0)
    {
        t = -t;
        if(t % 10 >= 5)
        {
            t = t / 10 + 1;
        }
        else
        {
            t = t / 10;
        }
        
        displayNum(1, '-');
        
        // 实际小于-99℃
        if(t > 100)
        {
            displayNum(2, '9');
            displayNum(3, '9');
        }
        else
        {
            t = -t;
            s = t / 10;
            displayNum(2, s + '0');
            b = t % 10;
            displayNum(3, b + '0');
        }
    }
    else
    {
        if(t % 10 >= 5)
        {
            t = t / 10 + 1;
        }
        else
        {
            t = t / 10;
        }
        
        // 实际温度大于999℃
        if(t > 999)
        {
            displayNum(1, '9');
            displayNum(2, '9');
            displayNum(3, '9');
        }
        else
        {
            // 温度大于100度显示百位数
            if(t >= 100)        
            {
                b = t / 100;
                displayNum(1, b + '0');
            }
            
            // 温度大于10度显示十位数
            if(t >= 10)
            {
                s = (t - b * 100) / 10;
                displayNum(2, s + '0');
            }
            
            displayNum(3, t % 10 + '0');
        }
    }  
    
    // 显示摄氏度符号
    displayIcon(IconCelsius, True);
}

/*
 参数：
 返回：
 功能：显示分钟数
*/
static void displayAlarmMinute(uint8_t min)
{  
    // 分钟数大于10显示十位数
    if(min >= 10)
    {
        displayNum(2, min / 10 + '0');
    }
    
    displayNum(3, min % 10 + '0');
}

/*
 参数：
 返回：
 功能：根据运行状态，显示对应的内容
*/
void displayTask(void)
{
	static uint16_t displayTick = 0;
	static uint8_t flashFlag = 0;
	
	uint16_t curTick = getTick();
    uint8_t batteryVoltageLv = getBatteryVoltageLv();
	
    // 100ms刷新一次
	if(curTick - displayTick >= ELAPSED_TIME_100_MS)
	{
		displayTick = curTick;
		
		if(curTick % 10 >= ELAPSED_TIME_500_MS)
		{
			flashFlag = 1;
		}
		else
		{
			flashFlag = 0;
		}
		
		// 清除现在的显示内容，重新填充显存
		clearDisplayRam();				
		
		// 显示电池状态
		displayIcon(batteryVoltageLv, True);
        if(batteryVoltageLv == ICON_BAT_LV0)
        {
            if(flashFlag)
            {
                displayIcon(batteryVoltageLv, False);
            }
        }
	
		switch(runState)
		{
			case FreeRunState:
                // 显示温度
      displayTemperature(getTemperature());
				break;
			case SettingAlarmState:
				displayIcon(IconClock, True);
                displayIcon(IconMin, True);
				displayAlarmMinute(getAlarmMinutes());
				break;
			case AlarmCountDownState:
				if(flashFlag)
				{
					displayIcon(IconClock, False);
				}
                else
                {
                    displayIcon(IconClock, True);
                }
                displayIcon(IconMin, True);
				displayAlarmMinute(getAlarmMinutes());			
				break;
			case ShutDownState:
                // 关机显示OFF
				clearDisplayRam();
				displayNum(1, '0');
                displayNum(2, 'F');
                displayNum(3, 'F');
				updataDisplayRam();
				break;
			default:
				break;
		}		
		updataDisplayRam();
	}
}


// end of file
