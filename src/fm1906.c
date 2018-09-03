/*
* 文件说明：fm1906显示驱动
*/
#include "HC89S003F4.h"
#include "fm1906.h"
#include "hc89s003_delay.h"

/*
* 输入：cmd-命令值
* 输出：
* 功能：写fm1906的命令， 包括命令码100，共12位，cmd的高位
*/
void fm1906WriteCmd(uint16_t cmd)
{
    int i = 12;
    
    CS_L;
    WAIT();
    while(i--)
    {
        WR_L;
        if(cmd & 0x8000)
        {
            DATA_H;
        }
        else
        {
            DATA_L;
        }
        WAIT();
        WR_H;
        WAIT();
        
        cmd <<= 1;
    }
    CS_H;
    WAIT();
}
    
/*
* 输入：addr-写入地址，buf-写入数据首地址，bits-写入的位数
* 输出：
* 功能：写fm1906的寄存器，写之前先发送命令码110和地址
*/   
void fm1906WriteData(uint8_t addr, const uint8_t* buf, uint8_t bits)
{
    uint8_t d = 0;
    uint8_t i = 9;
    uint16_t cmd = (uint16_t)0xa000 + ((uint16_t)addr & 0x003f) << 7;

    CS_L;
    WAIT();
    
    // 写发送读命令码和地址值
    while(i--)
    {
        WR_L;
        if(cmd & 0x8000)
        {
            DATA_H;
        }
        else
        {
            DATA_L;
        }
        WAIT();
        WR_H;
        WAIT();
        
        addr <<= 1;
    }
    
    
    for(i = 0; i < bits; i++)
    {
        if(0 == i % 8)
        {
            d = *buf++;
        }
        
        WR_L;
        if(d & 0x80)
        {
            DATA_H;
        }
        else
        {
            DATA_L;
        }
        WAIT();
        WR_H;
        WAIT();
        
        d <<= 1;
    }
    
    CS_H;
    WAIT();
}

/*
* 输入：
* 输出：
* 功能：fm1906初始化配置
*/ 
void fm1906Config(void)
{
	delay_ms(50);
//    fm1906WriteCmd(CMD_LCD_OFF);    
//    fm1906WriteCmd(CMD_TIMER_DIS);    
//    fm1906WriteCmd(CMD_TONE_OFF);
//    fm1906WriteCmd(CMD_IRQ_DIS);
//    fm1906WriteCmd(CMD_NORMAL);
    
    fm1906WriteCmd(CMD_BIAS_1_3 | CMD_COM_4);
	fm1906WriteCmd(CMD_RC256K);
	fm1906WriteCmd(CMD_SYS_DIS);
	fm1906WriteCmd(CMD_WDT_DIS);
    
    delay_ms(100);
    fm1906WriteCmd(CMD_SYS_EN);
    delay_ms(100);
    fm1906WriteCmd(CMD_LCD_ON);
}



// end of file
