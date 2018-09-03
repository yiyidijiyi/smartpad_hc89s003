/*
* 文件说明：断码液晶显示功能函数
*/

#include "display_driver.h"
#include "fm1906.h"
#include "ht1621.h"


static XDATA uint8_t displayRam[7] = {0};

/*
* 输入：n-选择显示的数码管编号，从左到右从1开始，c-要显示的内容
* 输出：
* 功能：指定数码管显示数字，显示空格表示空白
* 显示时每个数码管有13段，用2个字节表示，高位到低位分别为BJCK AGDL HFME I
* 0--BJCK AxDL HFME I
* 1--BJCK xxxx xxxx I
* 2--BJxK AGDL HxME I
* 3--BJCK AGDL HxMx I
* 4--BJCK xGxx HFMx I
* 5--xJCK AGDL HFMx I
* 6--xJCK AGDL HFME I
* 7--BJCK Axxx Hxxx I
* 8--BJCK AGDL HFME I
* 9--BJCK AGDL HFMx I
* A--BJCK AGxL HFME I
* F--xJxx AGxL HFME I
* ---xJxx xGxx xxMx x
*/
void displayNum(uint8_t n, char c)
{
    uint8_t h = 0;
    uint8_t l = 0;
    
    switch(c)
    {
        case '0':
            h = SEG_B | SEG_J | SEG_C | SEG_K | SEG_A | SEG_D | SEG_L;
            l = SEG_H | SEG_F | SEG_M | SEG_E | SEG_I;
            break;
        case '1':
            h = SEG_B | SEG_J | SEG_C | SEG_K;
            l = SEG_I;
            break;
        case '2':
            h = SEG_B | SEG_J | SEG_K | SEG_A | SEG_G | SEG_D | SEG_L;
            l = SEG_H | SEG_M | SEG_E | SEG_I;
            break;
        case '3':
            h = SEG_B | SEG_J | SEG_C | SEG_K | SEG_A | SEG_G | SEG_D | SEG_L;
            l = SEG_H | SEG_M | SEG_I;
            break;
        case '4':
            h = SEG_B | SEG_J | SEG_C | SEG_K | SEG_G;
            l = SEG_H | SEG_F | SEG_M | SEG_I;
            break;
        case '5':
            h = SEG_J | SEG_C | SEG_K | SEG_A | SEG_G | SEG_D | SEG_L;
            l = SEG_H | SEG_F | SEG_M | SEG_I;
            break;
        case '6':
            h = SEG_J | SEG_C | SEG_K | SEG_A | SEG_G | SEG_D | SEG_L;
            l = SEG_H | SEG_F | SEG_M | SEG_E | SEG_I;
            break;
        case '7':
            h = SEG_B | SEG_J | SEG_C | SEG_K | SEG_A;
            l = SEG_H | SEG_I;
            break;
        case '8':
            h = SEG_B | SEG_J | SEG_C | SEG_K | SEG_A | SEG_G | SEG_D | SEG_L;
            l = SEG_H | SEG_F | SEG_M | SEG_E | SEG_I;
            break;
        case '9':
            h = SEG_B | SEG_J | SEG_C | SEG_K | SEG_A | SEG_G | SEG_D | SEG_L;
            l = SEG_H | SEG_F | SEG_M | SEG_I;
            break;
        case 'A':
            h = SEG_B | SEG_J | SEG_C | SEG_K | SEG_A | SEG_G | SEG_L;
            l = SEG_H | SEG_F | SEG_M | SEG_E | SEG_I;
            break;
        case 'F':
            h = SEG_J | SEG_A | SEG_G | SEG_L;
            l = SEG_H | SEG_F | SEG_M | SEG_E | SEG_I;
            break;
        case '-':
            h = SEG_J | SEG_G;
            l = SEG_M;
            break;
        default:
            break;
    }
    
    switch(n)
    {
        case 3:
            displayRam[0] = h;
            displayRam[1] = (l & 0xf0) | (displayRam[1] & 0x0f);
            if(l & 0x08)
            {
                displayRam[5] |= SEG_3I;
            }
            else
            {
                displayRam[5] &= ~SEG_3I;
            }
            break;
        case 2:
            displayRam[1] = (displayRam[1] & 0xf0) | (h >> 4);
            displayRam[2] = (h << 4) | (l >> 4);
            if(l & 0x08)
            {
                displayRam[5] |= SEG_2I << 4;
            }
            else
            {
                displayRam[5] &= ~(SEG_2I << 4);
            }
            break;
        case 1:
            displayRam[3] = h;
            displayRam[4] = (l & 0xf0) | (displayRam[4] & 0x0f);
            if(l & 0x08)
            {
                displayRam[5] |= SEG_1I << 4;
            }
            else
            {
                displayRam[5] &= ~(SEG_1I << 4);
            }
            break;
        default:
            break;
    }
}

/*
* 输入：icon-需要显示的图标，flag-True显示图标，Flase清除图标
* 输出：
* 功能：显示图标
*/
void displayIcon(Icon_t icon, Bool_t flag)
{
    if(icon >= IconMax)
    {
        return;
    }
    
    if(flag)
    {
        switch(icon)
        {
            case IconMin:
                displayRam[5] |= ICON_MIN << 4;
                break;
            case IconClock:
                displayRam[5] |= ICON_CLOCK;
                break;
            case IconBT:
                displayRam[6] |= ICON_BT << 4;
                break;
            case IconCelsius:
                displayRam[6] |= ICON_CELSIUS << 4;
                break;
            case IconBatLv0:
                displayRam[4] |= ICON_BAT_LV0;
                break;
            case IconBatLv1:
                displayRam[4] |= ICON_BAT_LV1;
                break;
            case IconBatLv2:
                displayRam[4] |= ICON_BAT_LV2;
                break;
            case IconBatLv3:
                displayRam[4] |= ICON_BAT_LV3;
                break;
            default:
                break;
        }
    }
    else
    {
        switch(icon)
        {
            case IconMin:
                displayRam[5] &= ~(ICON_MIN << 4);
                break;
            case IconClock:
                displayRam[5] &= ~ICON_CLOCK;
                break;
            case IconBT:
                displayRam[6] &= ~(ICON_BT << 4);
                break;
            case IconCelsius:
                displayRam[6] &= ~(ICON_CELSIUS << 4);
                break;
            case IconBatLv0:
                displayRam[4] &= ~ICON_BAT_LV0;
                break;
            case IconBatLv1:
                displayRam[4] &= ~ICON_BAT_LV1;
                break;
            case IconBatLv2:
                displayRam[4] &= ~ICON_BAT_LV2;
                break;
            case IconBatLv3:
                displayRam[4] &= ~ICON_BAT_LV3;
                break;
            default:
                break;
        }
    }
}

/*
* 输入：
* 输出：
* 功能：清空显示内容
*/
void clearDisplayRam(void)
{
    uint8_t i;
    
    for(i = 0; i < 7; i++);
    {
        displayRam[i] = 0;
    }
}

/*
* 输入：
* 输出：
* 功能：更新显示内容
*/
void updataDisplayRam(void)
{
//	uint8_t i = 0;
//	for(i = 0; i < 7; i++)
//	{
//		displayRam[i] = 0x00;
//	}
//    fm1906WriteData1(0, displayRam, 52);  //king

   uint8_t i = 0;
   uint8_t addr = 2; 
	for(i = 0; i < 7; i++)
	{
	 	 ht1621_write(addr,displayRam[i]);
     addr+=2;
     ht1621_write(addr,(displayRam[i]<<4));
     addr+=2;
	}
}



// end of file