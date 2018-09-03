/*
* 文件说明：项目主函数
*/
#define	ALLOCATE_EXTERN
#include "HC89S003F4.h"
#include "mcu_config.h"
#include "board.h"
#include "comm.h"
#include "key.h"
#include "alarm.h"
#include "display.h"
#include "beep.h"
#include "warning.h"
#include "ht1621.h"
#include "intrins.h"
#include "stdlib.h"

//uint8_t arr[4] = {0};

void main(void)
{  
    // 关闭看门狗

    DISABLE_WDT();
    
    // 电源自锁
    powerOn(); 
    
    initWdt();
	initGpio();
	initSystemClk();
	initAdc();
	initTimer();
    initUart();
	initLEDControl();
	initBeepControl();
    initLcdDriver();
    //initTemperatureMeasure();
    readWarningNum();
    
    //startWdt();
	ENABLE_INTERRUPT();
	
    while(1)
    {     
        // 清看门狗
        //CLEAR_WDT();
    
        // 按键扫描， 运行状态切换
		keyTask();
        
		// 根据运行状态，显示对应内容
		displayTask();

        // 警报任务
        warningTask();
		
		// 蜂鸣器任务
		beepTask();
		
		// 串口通信任务
		commTask();
        
        // 电源自锁控制任务
		powerTask();
    }
}

// end of file
