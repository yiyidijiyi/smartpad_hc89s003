/*
* 文件说明：hc89s003f4系统时钟配置
*/
#ifndef HC89S003_H
#define HC89S003_H

#include "typedef.h"

// 时钟控制寄存器-CLKCON
#define HXTAL_RDY 	(0x80)
#define LXTAL_RDY 	(0x40)
#define HSRC_RDY 	(0x20)
#define LSRC_RDY	(0x10)
#define XTAL_EN		(0x04)
#define HSRC_EN		(0x02)

#define IS_HXTAL_READY() (CLKCON & 0x80)
#define IS_LXTAL_READY() (CLKCON & 0x40)
#define IS_HSRC_READY()	(CLKCON & 0x20)
#define IS_LSRC_READY()	(CLKCON & 0x10)

#define ENABLE_XTAL()	do{CLKCON |= 0x40;}while(0)
#define ENABLE_HSRC()	do{CLKCON |= 0x20;}while(0)
#define DISABLE_XTAL()	do{CLKCON &= ~0x40;}while(0)
#define DISABLE_HSRC()	do{CLKCON &= ~0x20;}while(0)

// 时钟选择寄存器-CLKSWR
#define CLK_STA_HXTAL	(0xc0)
#define CLK_STA_LXTAL	(0x80)
#define CLK_STA_HSRC		(0x40)
#define CLK_STA_LSSRC		(0x0)

#define CLK_SEL_HXTAL	(0x30)
#define CLK_SEL_LXTAL	(0x20)
#define CLK_SEL_HSRC	(0x10)
#define CLK_SEL_LSRC	(0x0)
#define CLK_SEL_MASK	(0x30)

#define RC32M_DIV_8		(0x03)
#define RC32M_DIV_4		(0x02)
#define RC32M_DIV_2		(0x01)
#define RC32M_DIV_1		(0x0)
#define RC32M_DIV_MASK	(0x03)


#define CLK_STATUS	(CLKSWR & 0xc0)
#define CLK_SELECT(sel)	do{uint8_t clkswr = CLKSWR; clkswr &= ~CLK_SEL_MASK;  clkswr |= sel; CLKSWR = clkswr;}while(0)

#define HRC_DIV_8	(0x03)
#define HRC_DIV_4	(0x02)
#define HRC_DIV_2	(0x01)
#define HRC_DIV_1	(0x0)

#define SET_HSRC_DIV(div) do{uint8_t clkswr = CLKSWR; clkswr &= ~RC32M_DIV_MASK; clkswr |= div; CLKSWR = clkswr;}while(0)
#define SET_CLK_DIV(div)  do{CLKDIV = div;}while(0)

// 时钟输出寄存器-CLKOUT
#define CLK_OUT_SEL_CPU			(0x0)
#define CLK_OUT_SEL_OSC			(0x01)
#define CLK_OUT_SEL_WDT			(0x02)
#define CLK_OUT_SEL_XTAL		(0x03)
#define CLK_OUT_SEL_HRC_32M		(0x04)
#define CLK_OUT_SEL_HRC_16M		(0x05)
#define CLK_OUT_SEL_HRC_8M		(0x06)
#define CLK_OUT_SEL_HRC_4M		(0x07)

#define ENABLE_CLK_OUT	do{CLKOUT |= 0x08;}while(0)
#define DISABLE_CLK_OUT do{CLKOUT &= ~0x08;}while(0)

// 外部晶振配置寄存器-XTALCFG
#define HXTAL_2048	(0x0)
#define HXTAL_256	(0x40)
#define HXTAL_16384	(0x80)
#define HXTAL_65536	(0xc0)

#define LXTAL_16384 (0x0)
#define LXTAL_4096	(0x10)
#define LXTAL_1024	(0x20)
#define LXTAL_65536	(0x30)

#define HXTAL_MODE_SEL_00	(0x0)
#define HXTAL_MODE_SEL_01	(0x04)
#define HXTAL_MODE_SEL_11	(0x0c)

#define SELECT_XTAL_FREQ(sel) do{XTALCFG |= sel;}while(0)
#define SELECT_HXTAL_MODE(mode) do{XTALCFG |= mode;}while(0)
#define ENABLE_RC_PD	do{XTALCFG |= 0x01;}while(0)
#define DISABLE_RC_PD	do{XTALCFG &= ~0x01;}while(0)

// 系统时钟频率寄存器-FREQ_CLK
#define CPU_FREQ_16M	(0x10)
#define CPU_FREQ_8M		(0x08)
#define CPU_FREQ_4M		(0x04)
#define CPU_FREQ_2M		(0x02)
#define CPU_FREQ_1M		(0x01)
#define SET_FREQ_CLK(freq) do{FREQ_CLK = freq;}while(0)


void HRCFreqConfig(uint8_t div1, uint8_t div2);

#endif // HC89S003_H
