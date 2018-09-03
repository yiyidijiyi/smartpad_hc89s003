#include "ht1621.h"
#include "HC89S003F4.h"
#include "hc89s003_delay.h"
#include "fm1906.h"
 

void ht1621_send_high_order_data(uint8_t data1,uint8_t len)
{
	 uint8_t i;
 
	for (i=0; i<len; i++)
	{
		if((data1&0x80) == 0)
		{
			DATA_L;	
		}
		else
		{
			DATA_H;
		}
		
		WR_L;
		delay_ms(1);
		WR_H;	
		
		data1 <<= 1;
	}
}
 
void ht1621_send_low_order_data(uint8_t data1, uint8_t len)
{
	uint8_t i;
	
	for (i=0; i<len; i++)
	{
		if((data1&0x80) == 0)
		{
			DATA_L;	
 
		}
		else
		{
			DATA_H;
  
		}
		
		WR_L;
		delay_ms(1);
		WR_H;	
		
		data1 <<= 1;
	}
}
 
void ht1621_send_cmd(uint8_t command)
{
	CS_L;	
	ht1621_send_high_order_data(0x80, 4);
	ht1621_send_high_order_data(command, 8);
	CS_H;	
}
 
void ht1621_write(uint8_t addr, uint8_t data1)
{
	CS_L;
	ht1621_send_high_order_data(0xA0, 3);
	ht1621_send_high_order_data(addr<<2, 6);
	ht1621_send_low_order_data(data1, 4); 
	CS_H;
}
 
void ht1621_write_all(uint8_t addr, uint8_t *p, uint8_t len)
{
	uint8_t i;
	
	CS_L;
	ht1621_send_high_order_data(0xA0, 3);
	ht1621_send_high_order_data(addr<<2, 6);
	
	for (i=0; i<len; i++, p++)
	{
		ht1621_send_low_order_data(*p, 8);
	}
	
	CS_H;	
}
 
 
 
void ht1621_clr_all_display()
{
	uint8_t i;
	uint8_t addr = 0;
	
	for (i=0; i<16; i++)
	{
		ht1621_write(addr, 0x00);
		addr += 2;
	}
}
 
void ht1621_all_display()
{
	uint8_t i;
	uint8_t addr = 0;
	
	for (i=0; i<16; i++)
	{
		ht1621_write(addr, 0xFF);
		addr += 2;
	}	
}
 
void ht1621_init()
{
	ht1621_send_cmd(HT_SYS_EN);
	ht1621_send_cmd(HT_RCOSC);
	ht1621_send_cmd(HT_BISA_COM);
	ht1621_send_cmd(HT_LCD_ON);
}
 
 
void set_lcd_on()
{
	ht1621_send_cmd(HT_LCD_ON);
}
 
void set_lcd_off()
{
	ht1621_send_cmd(HT_LCD_OFF);
}

void fm1906WriteData1(uint8_t addr, const uint8_t *buf, uint8_t bits)
{
	uint8_t i;
	uint8_t m;
	uint8_t n;
	CS_L;
	ht1621_send_high_order_data(0xA0, 3);
	ht1621_send_high_order_data(addr << 2, 6);

	n = bits >> 3;
	m = bits % 8;
	for (i = 0; i < n; i++)
	{
		ht1621_send_high_order_data(*(buf + i), 8);
	}

	if(m != 0)
	{
		ht1621_send_high_order_data(*(buf+n), m);
	}

	CS_H;
}