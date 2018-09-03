/*
* 文件说明：hc89s003f4 flash模拟eeprom操作
*/
#include "HC89S003F4.h"
#include "hc89s003_flash.h"
#include "hc89s003_clk.h"


/*
* 输入：
* 输出：
* 功能：根据CPU时钟，配置flash读写时钟
*/
//void flashReadWriteConfig(void)
//{
//	SET_FREQ_CLK(CPU_FREQ_4M);
//}



/**
  * @说明  	扇区擦除，约消耗5ms的时间
  * @参数  	fui_Address ：被擦除的扇区内的任意一个地址
  * @返回值 无
  * @注		只要操作扇区里面的任意一个地址，就可以擦除此扇区
  */
#pragma disable							//确保调整时不会进中断导致调整失败
void Flash_EraseBlock(unsigned int fui_Address)
{
	IAP_CMD = 0xF00F;				//Flash解锁
	IAP_ADDR = fui_Address;			//写入擦除地址
	IAP_CMD = 0xD22D;				//选择操作方式， 扇区擦除
	IAP_CMD = 0xE11E; 				//触发后IAP_ADDRL&IAP_ADDRH指向0xFF，同时自动锁定
}

/**
  * @说明  	写入一个字节数据到Flash里面
  * @参数  	fui_Address ：FLASH地址
  *	@参数	fucp_SaveData：写入的数据
  * @返回值 无
  * @注		写之前必须先对操作的扇区进行擦除
  */
#pragma disable							//确保调整时不会进中断导致调整失败
void FLASH_WriteData(unsigned char fuc_SaveData, unsigned int fui_Address)
{
	IAP_DATA = fuc_SaveData;
	IAP_CMD=0xF00F;				//Flash解锁
	IAP_ADDR = fui_Address;
	IAP_CMD=0xB44B;				//字节编程
	IAP_CMD=0xE11E;				//触发一次操作
}

/**
  * @说明  	写入任意长度的数据到FLASH里面
  * @参数  	fui_Address ：FLASH起始地址
  *	@参数	fuc_Length ： 写入数据长度
  *			取值范围：0x00-0xFF
  *	@参数	*fucp_SaveArr：写入的数据存放区域的首地址
  * @返回值 无
  * @注		写之前必须先对操作的扇区进行擦除
  */
#pragma disable							//确保调整时不会进中断导致调整失败
void Flash_WriteArr(unsigned int fui_Address,unsigned char fuc_Length,unsigned char *fucp_SaveArr)
{
	unsigned char fui_i = 0;
	for(fui_i=0;fui_i<fuc_Length;fui_i++)
	{
		FLASH_WriteData(*(fucp_SaveArr++), fui_Address++); 
	}
}

/**
  * @说明  	从FLASH里面读取任意长度的数据
  * @参数  	fui_Address ：FLASH起始地址
  *	@参数	fuc_Length ：读取数据长度
  *			取值范围：0x00-0xFF
  *	@参数	*fucp_SaveArr：读取数据存放的区域首地址
  * @返回值 无
  * @注		无
  */
void Flash_ReadArr(unsigned int fui_Address,unsigned char fuc_Length,unsigned char *fucp_SaveArr)
{
	while(fuc_Length--)
	*(fucp_SaveArr++)=*((unsigned char code *)(fui_Address++));//读取数据
}





// end of file
