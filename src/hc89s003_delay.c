/*
* 文件说明：不精确延时函数
*/
#include "hc89s003_delay.h"

/*
* 输入：n-延时时间
* 输出：
* 功能：Fcpu = 16MHz(对应m=1596)，n = 1时，延时时间约为1Ms
*/
void delay_ms(uint16_t n)
{
	unsigned int m;
	for(;n > 0;n --)
	{
		for(m = 399;m > 0;m --);
	}
}

/*
* 输入：n-延时时间
* 输出：
* 功能：Fcpu = 16MHz, n = 1时，延时时间约为2us
*       Fcpu = 4MHz，至少延时8us
*/
void delay_us(uint16_t n)
{
	while(n--);	
}



// end of file
