/*
* 文件说明：hc89s003f4 timer3模块操作
*/
#include "HC89S003F4.h"
#include "hc89s003_timer3.h"

/*
* 输入：v-重载计数器值
* 输出：
* 功能：设置timer3的重载计数器
*/
void setTimer3ReloadCounter(uint16_t v)
{
    DISABLE_TIMER3();
    
    TH3 = (uint8_t)(v >> 8);
    TL3 = (uint8_t)v;
}

/*
* 输入：status-中断状态使能或禁止，pri-中断优先级
* 输出：
* 功能：设置timer3中断
*/
void timer3InterruptConfig(FlagStatus_t status, IntPriority_t pri)
{
    uint8_t ip2 = 0;
    if(Set == status)
    {
        // 清中断标志位
        T3CON &= 0x7f;       
        
        // 设置中断优先级
        if(pri >= IntPriority3)
        {
            pri = IntPriority0;
        }
        
        ip2 = IP2;
        ip2 &= 0xf3;
        ip2 |= ((uint8_t)pri) << 2;
        IP2 = ip2;
		
		// 设置中断使能位
        ENABLE_T3_INT();
        
    }
    else
    {
        // 清中断标志位
        T3CON &= 0x7f;
        
        // 设置中断使能位
        DISABLE_T3_INT();
    }
}



/*
* 输入：
* 输出：
* 功能：配置timer3产生周期中断，中断周期为50ms
*/
void timer3Config(void)
{
    DISABLE_TIMER3();
    
    // 系统时钟与预分频配置，选择Fosc为系统时钟，64分频
    T3CON |= T3_CLK_FOSC | T3_PS_64;
    
    // 计数频率为4000000/64=62500
    // 产生100ms的中断，重装载值为65536 - 3125 = 59286(0xF3CB)
    TH3 = 0xf3;
    TL3 = 0xcb;
    
    // 使能中断，中断优先级为0
    timer3InterruptConfig(Set, IntPriority0);
    
    ENABLE_TIMER3();
}




// end of file
