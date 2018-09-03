#ifndef _HT1621_H
#define _HT1621_H

#include "fm1906.h"
 
 
#define HT_BISA_COM			0x52		//(1<<1) | (0<<3) | (1<<4) | (0<<5) | (1<<6) | (0<<7) | (0<<8) | (0<<9) | (0<<10) | (1<<11)
#define HT_LCD_OFF			0x04		//(0<<1) | (1<<2) | (0<<4) | (0<<5) | (0<<6) | (0<<7) | (0<<8) | (0<<9) | (0<<10) | (1<<11)
#define HT_LCD_ON			0x06		//(1<<1) | (1<<2) | (0<<4) | (0<<5) | (0<<6) | (0<<7) | (0<<8) | (0<<9) | (0<<10) | (1<<11)
#define HT_WRITE_CMD		0x80		//(0<<0) | (0<<1) | (1<<2)  | (0<<3) | (1<<4) | (0<<5) | (1<<6) | (0<<7) | (1<<8)
#define HT_WRITE_DATA		0xA0
#define HT_SYS_EN			0x02
#define HT_RCOSC			0x30
 
 
void ht1621_init();
void ht1621_all_display();

void ht1621_clr_all_display();


void ht1621_send_cmd(uint8_t command);
void ht1621_write(uint8_t addr, uint8_t data1);
void ht1621_write_all(uint8_t addr, uint8_t *p, uint8_t len);
void fm1906WriteData1(uint8_t addr, const uint8_t* buf, uint8_t bits);


#endif