/*
* 文件说明：hc89s003f4串口操作
*/
#include "HC89S003F4.h"
#include "hc89s003_timer4.h"
#include "hc89s003_uart.h"
#include "hc89s003_int.h"
#include "tick.h"



/*
* 输入：
* 输出：
* 功能：uart模式1，异步双工，波特率9600
*/
void uart1Config()
{
	// uart mode1 由timer4作为波特率发生器
	// Fosc为时钟源，不分频
	T4CON = T4PS_1 + T4M_MODE1 + T4CLK_FOSC;
	
	//波特率计算
	//波特率 = 1/16 * (T4时钟源频率 / 定时器4预分频比) / (65536 - T4)
	//       = 1/16 * ((4000000 / 1) / T4)

	//波特率9600
	//反推初值 = (65536 - ((T4时钟源频率 / 定时器4预分频比) * (1 / 16)) / 波特率)
	//		   = (65536 - (4000000 * (1 / 16) / 9600))
	//		   = (65536 - 26.04167)
	//         = 65510(FFE6)
	TH4 = 0xFF;
	TL4 = 0xE6;
	ENABLE_T4();
	
	// 选择uart mode1， 使能中断接收
	SCON2 = SCON2_MODE1;
	SCON = SCON_REN;
	
	// 使能串口中断
	ENABLE_UART1_INT();
}



// end of file
