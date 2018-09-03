/*
* 文件说明：根据项目hc89s003f4系统和外设配置的函数
*/
#include "mcu_config.h"
#include "HC89S003F4.h"

/*
* 输入：
* 输出：
* 功能：选择HC89S003的时钟源为HRC，Fosc = 4M(8分频)，Fcpu = 4M(1分频）
*/
void initSystemClk()
{
	HRCFreqConfig(RC32M_DIV_8, 1);
	SET_FREQ_CLK(CPU_FREQ_4M);
}