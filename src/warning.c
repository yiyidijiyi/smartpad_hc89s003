/*
* 文件说明：高温报警与RGB灯颜色指示
*/

#include "typedef.h"
#include "warning.h"
#include "board.h"
#include "common.h"
#include "tick.h"
#include "beep.h"
#include "hc89s003_flash.h"
#include "led.h"

// 用2个字节去记录超过300度的次数，因为FLASH擦除后的初始值为0x00，为区分该区域是否已使用，写入的次数的范围为0x0001~0xffff
// 为较少flash的擦写次数，只有一个扇区都写完时才擦除掉，重新从扇区首地址开始写，读到数值为0xffff表示该区域未使用
#define WARNNING_NUM_ADDR   ((uint16_t)0x3e80)
#define BLOCK_SIZE          ((uint8_t)0x80)

XDATA uint16_t warningNum = 0;

/*
* 输入：
* 输出：
* 功能：高温报警次数增加1
*/
static void warningNumInc(void)
{
    if(warningNum < 0xffff)
    {
        warningNum++;
    }
}

/*
* 输入：
* 输出：
* 功能：写入高温告警次数
*/
void saveWarningNum(void)
{
    uint8_t n = 0;
    uint16_t temp = 0;
    
    // 寻找未写入的地址
    while(n < BLOCK_SIZE)
    {
        Flash_ReadArr(n + WARNNING_NUM_ADDR, 2, (uint8_t*)&temp);
        
        if(temp == 0x0)
        {
            break;
        }
        else
        {
            n += 2;
        }
    }
    
    // 如果整个扇区已写完
    if(n == BLOCK_SIZE)
    {
        Flash_EraseBlock(WARNNING_NUM_ADDR);
        n = 0;
    }
    
    Flash_WriteArr(n + WARNNING_NUM_ADDR, 2, (uint8_t*)&warningNum);
}

/*
* 输入：
* 输出：
* 功能：读取高温告警次数
*/
void readWarningNum(void)
{
    uint8_t n = 0;
    uint16_t temp = 0;
    
    // 寻找最后一个写入值
    while(n < BLOCK_SIZE)
    {
        Flash_ReadArr(n + WARNNING_NUM_ADDR, 2, (uint8_t*)&temp);
        
        if(temp == 0x0)
        {
            break;
        }
        else
        {
            n += 2;
        }
    }
    
    if(n != 0)
    {
        n -= 2;
        Flash_ReadArr(n + WARNNING_NUM_ADDR, 2, (uint8_t*)&warningNum);
    }
    else
    {
        warningNum = 0;
    }
}

/*
* 输入：
* 输出：
* 功能：高温报警与RGB灯颜色调整任务
*/
void warningTask(void)
{
    static uint16_t oldTick = 0;
    static uint8_t warningFlag = 0;
    uint16_t tick = getTick();
    int16_t t;
    
    if(tick - oldTick >= ELAPSED_TIME_1_SECOND)
    {
        oldTick = tick;
        
        t = getTemperature();
        
        // 高于300度报警，低于300-5度结束报警
        if(t >= WARNING_TEMPERATURE)
        {
            if(warningFlag == 0)
            {
                // 0xffff表示蜂鸣器不间断响
                beepStartBuzz(0xffff, ELAPSED_TIME_300_MS, ELAPSED_TIME_700_MS);
                warningNumInc();
                saveWarningNum();
                
                warningFlag = 1;
            }
        }
        else if (t <= WARNING_TEMPERATURE - 50)
        {
            if(warningFlag == 1)
            {
                beepStopBuzz();
                warningFlag = 0;
            }
        }
        
        if(t >= RED_TEMPERATURE)
        {
            if(led.color != Red)
            {
                setRGB(255, 0, 0, BRIGHTNESS);
                led.color = Red;
            }                
        }
        else if(t >= YELLOW_TEMPERATURE)
        {
            if(led.color != Yellow)
            {
                setRGB(255, 255, 0, BRIGHTNESS);
                led.color = Yellow;
            }
        }
        else if(t >= GREEN_TEMPERATURE)
        {
            if(led.color != Green)
            {
                setRGB(0, 255, 0, BRIGHTNESS);
                led.color = Green;
            }
        }
        else
        {
            if(led.color != Blue)
            {
                setRGB(0, 0, 255, BRIGHTNESS);
                led.color = Blue;
            }
        }
    }
}




// end of file
