/*
* 文件说明：hc89s003f4 adc模块操作
*/
#include "hc89s003_adc.h"
#include "HC89S003F4.h"
#include "hc89s003_int.h"

/*
* 输入：
* 输出：
* 功能：ADC模块初始化，内部参考电压2.7V，转换时钟500k，
*/
void adcConfig(void)
{
    ENABLE_ADC();
    
    ADCC0 |= INREF_2V;
    ADCC2 |= ADCL_12BITS + ALIGN_1 + ADCTS_1M + ADC_CLK_FOSC_8;
	
	ENABLE_ADC_INT();
}

/*
* 输入：
* 输出：
* 功能：返回ADC结果值
*/
uint16_t getAdcResult(AdcResult_t t)
{
    uint16_t v = ADCRH & (uint8_t)t;
    v <<= 8;
    v += ADCRL;
	
	return v;
}


// end of file
