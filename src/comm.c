/*
* 文件说明：通信与数据存储
*/


#include "HC89S003F4.h"
#include "hc89s003_timer4.h"
#include "hc89s003_uart.h"
#include "hc89s003_int.h"
#include "hc89s003_flash.h"
#include "board.h"
#include "tick.h"
#include "comm.h"

#define FLASH_ADDR		(0x3f00)
#define FLASH_ADDR_BAK	(0x3f80)	// 最后一个扇区
#define RX_BUF_LENGTH	(12)
static XDATA uint8_t rxBuf[RX_BUF_LENGTH] = 0;
static uint8_t rxPtr = 0;

extern XDATA uint16_t warningNum;

/*
* 输入：
* 输出：
* 功能：uart1接收中断
*/
void UART1_ISR(void) interrupt UART1_VECTOR
{
	//判断接收中断标志位
	if(SCON & SCON_RI)						
	{
		//转存8位串口接收数据
		if(rxPtr < RX_BUF_LENGTH)
		{
			rxBuf[rxPtr++] = SBUF;
		}
		
		//清除接收中断标志位
		SCON &=~SCON_RI;					
	}									
}



/*
* 输入：dat-数据首地址，length-数据长度
* 输出：校验和
* 功能：校验和计算
*/
static uint8_t checkSum(uint8_t *dat, uint8_t length)
{
	uint8_t sum = 0;
	uint8_t i = 0;
	for(i = 0; i < length; i++)
	{
		sum += dat[i];
	}
	
	return sum;
}

/*
* 输入：
* 输出：
* 功能：读取热电偶，温度计算直线参数
*/
void readTempeartureParam(TemperatureParam_t *param)
{
	uint8_t tmp[5];
	Flash_ReadArr(FLASH_ADDR, 5, tmp);
	
	if(tmp[4] != checkSum(tmp, 4))
	{
		Flash_ReadArr(FLASH_ADDR_BAK, 5, tmp);
		
		if(tmp[4] != checkSum(tmp, 4))
		{
			return;
		}
	}
	
	param->k = ((uint16_t)tmp[0]) << 8;
	param->k += tmp[1];
	
	param->b = ((uint16_t)tmp[2]) << 8;
	param->b += tmp[3];
}

#define RESET_RX_BUF()	do{rxPtr = 0;}while(0)
#define START_CODE ((uint8_t)0x2f)

/*
* 输入：
* 输出：
* 功能：通过串口发送数据
*/
static void uartSendData(uint8_t *d, uint8_t len)
{
    uint8_t i = 0;
    DISABLE_UART1_INT();
    
    for(i= 0; i < len; i++)
	{
		SBUF = d[i];        //发送8位串口数据
		while(!(SCON & SCON_TI));
		SCON &= ~SCON_TI;   //清除发送中断标志位
	}
    SCON &= ~SCON_RI;
    ENABLE_UART1_INT();
}

/*
* 输入：
* 输出：
* 功能：串口协议解析
* 一帧数据共8字节
* byte1-0x2f，帧起始码
* byte2-命令字
* byte3~byte7-数据段
* byte8-校验和
*/
static void rxDataProcess(void)
{
	uint8_t ptr = rxPtr;
	uint8_t i;
	if(ptr >= 8)
	{
		for(i = 0; i < ptr; i++)
		{
			if(rxBuf[i] == START_CODE)
			{
				break;
			}
		}
		
		if(ptr - i >= 8)
		{
			// 校验成功接收到完整数据帧
			if(checkSum(rxBuf + i + 1, 6) == rxBuf[i + 7])
			{
				// 计算数据校验和
				rxBuf[i + 6] = checkSum(rxBuf + i + 2, 4);
				
                
                if(rxBuf[i + 1] == WRTIE_PARAMETERS)
                {
                    // 存储主分区
                    Flash_EraseBlock(FLASH_ADDR);
                    Flash_WriteArr(FLASH_ADDR, 5, rxBuf + i + 2);
                    
                    // 存储备份区
                    Flash_EraseBlock(FLASH_ADDR_BAK);
                    Flash_WriteArr(FLASH_ADDR_BAK, 5, rxBuf + i + 2);
                    
                    // 复位接收缓冲指针
                    RESET_RX_BUF();
                }
                else if(rxBuf[i + 1] == READ_WARNING_NUM)
                {
                    uartSendData((uint8_t*)&warningNum, 2);
                }				
			}
		}
		else if(i + 8 >= RX_BUF_LENGTH)
		{
			RESET_RX_BUF();
		}
	}
	
	if(ptr >= RX_BUF_LENGTH)
	{
		RESET_RX_BUF();
	}
}

/*
* 输入：
* 输出：
* 功能：通信任务
*/
void commTask(void)
{
	static uint16_t oldTick = 0;
	uint16_t newTick = getTick();
	
	if(oldTick != newTick)
	{
		oldTick = newTick;
		rxDataProcess();
	}
}






// end of file
