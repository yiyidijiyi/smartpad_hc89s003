/*
* 文件说明：hc89s003f4看门狗模块
*/
#include "HC89S003F4.h"
#include "hc89s003_wdt.h"
#include "hc89s003_delay.h"

static uint8_t wdtCCR = 0;

/*
* 输入：div-wdt计数时钟分频，ccr-wdt溢出比较值
* 输出：
* 功能：wdt的时钟源为44k内部低速RC，wdt的溢出时间计算方式为div * ccr / 44000
*/
void WDTConfig(uint8_t div, uint8_t ccr)
{
    DISABLE_WDT();
    delay_ms(1);
    
    wdtCCR = ccr;
    SET_WDT_DIV(div);
    //SET_WDT_CCR(ccr);
    
    //ENABLE_WDT();
}

/*
* 输入：
* 输出：
* 功能：启动wdt
*/
void startWdt(void)
{
    ENABLE_WDT();
    SET_WDT_CCR(wdtCCR);
}


// end of file
