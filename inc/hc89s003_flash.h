/*
* 文件说明：hc89s003f4 flash模拟eeprom操作
*/
#ifndef HC89S003_FLASH_H
#define HC89S003_FLASH_H

//void flashReadWriteConfig(void);
void Flash_EraseBlock(unsigned int fui_Address);
void FLASH_WriteData(unsigned char fuc_SaveData, unsigned int fui_Address);
void Flash_WriteArr(unsigned int fui_Address,unsigned char fuc_Length,unsigned char *fucp_SaveArr);
void Flash_ReadArr(unsigned int fui_Address,unsigned char fuc_Length,unsigned char *fucp_SaveArr);

#endif
