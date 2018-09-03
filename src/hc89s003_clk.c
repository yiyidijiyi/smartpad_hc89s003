/*
* 文件说明：hc89s003f4系统时钟配置
*/
#include "HC89S003F4.h"
#include "hc89s003_clk.h"

/*
* 输入：div1-HRC Fosc分频系数（外设时钟分配系数)，div2-HRC Fcpu分频系数
* 输出：
* 功能：采用HRC作为系统的时钟HRC为32M，通过div1(8/4/2/1)分频为Fosc，再经过div2(1~255)分频为Fcpu
*/
void HRCFreqConfig(uint8_t div1, uint8_t div2)
{
	// 使能HRC
	ENABLE_HSRC();
	
	// 判断HRC是否准备好
	while(IS_HSRC_READY() == 0);
	
	// 选择HRC为芯片时钟源
	CLK_SELECT(CLK_SEL_HSRC);
	
	// 判断时钟源状态
	while(CLK_STATUS != CLK_STA_HSRC);
	
	// 关闭外部晶振
	DISABLE_XTAL();
	
	// 设置Fosc分频
	SET_HSRC_DIV(div1);
	
	// 设置Fcpu分频
	SET_CLK_DIV(div2);
    
    // flash读写配置
    SET_FREQ_CLK(CPU_FREQ_4M);
}