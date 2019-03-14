/*
 * fecc_lcd.c
 *
 * Created: 12.08.2016 17:01:33
 *  Author: it.admin3
 * Library for Fordata FECC1602D-FLYYBW-65LR LCD
 * 4-bit interface mode
 */ 

#include <avr/io.h>
#include <avr/pgmspace.h>

#include "avr035.h"
#include "fecc_lcd.h"
#include <util/delay.h>

void lcd_init (void)
{
	_delay_ms(15);                 // wait after power on for start display
	LCD_DDR1 |= LCD_PORT1_BITMASK; // set pins to output
	LCD_DDR2 |= LCD_PORT2_BITMASK;
	
	// function set 4-bit mode
	SETBIT(LCD_PORT1, LCD_DB5);    
	ENABLE();
	_delay_us(LCD_EXECDELAY);
	
	// function set: 4-bit, 2-line display, 5x8 dots format mode
	ENABLE();  // send upper half byte like previous
		
	SETBIT(LCD_PORT2, LCD_DB7);
	ENABLE();  // send lower half byte
	_delay_us(LCD_EXECDELAY);
	
	// display off, cursor off, blink off
	LCD_PORT1 &= ~((1<<LCD_DB4) | (1<<LCD_DB5));  // clear data pins
	LCD_PORT2 &= ~((1<<LCD_DB7) | (1<<LCD_DB6));
	ENABLE();   // send upper half byte
	
	SETBIT(LCD_PORT2, LCD_DB7);
	ENABLE();   // send lower half byte
	_delay_us(LCD_EXECDELAY);
	
	// clear display
	LCD_PORT1 &= ~((1<<LCD_DB4) | (1<<LCD_DB5));  // clear data pins
	LCD_PORT2 &= ~((1<<LCD_DB7) | (1<<LCD_DB6));
	ENABLE();   // send upper half byte
	asm("nop");
	SETBIT(LCD_PORT1, LCD_DB4);
	ENABLE();   // send lower half byte
	_delay_ms(LCD_CLEARDELAY);
	
	// entry mode set
	LCD_PORT1 &= ~((1<<LCD_DB4) | (1<<LCD_DB5));  // clear data pins
	LCD_PORT2 &= ~((1<<LCD_DB7) | (1<<LCD_DB6));
	ENABLE();   // send upper half byte
	asm("nop");
	SETBIT(LCD_PORT1, LCD_DB5);
	SETBIT(LCD_PORT2, LCD_DB6);
	ENABLE();   // send lower half byte
	_delay_us(LCD_EXECDELAY);                     
}

void lcd_write_byte(uint8_t byte, uint8_t status)
{
	LCD_PORT1 &= ~LCD_PORT1_BITMASK;  // clear pins
	LCD_PORT2 &= ~LCD_PORT2_BITMASK;
	if (status) SETBIT(LCD_PORT1, LCD_RS);        // 0 - write command, 1 - write data
	
	if (byte & (1<<7)) SETBIT(LCD_PORT2, LCD_DB7);
	if (byte & (1<<6)) SETBIT(LCD_PORT2, LCD_DB6);
	if (byte & (1<<5)) SETBIT(LCD_PORT1, LCD_DB5);
	if (byte & (1<<4)) SETBIT(LCD_PORT1, LCD_DB4);
	ENABLE();                                      // send upper half byte
	
	LCD_PORT1 &= ~((1<<LCD_DB4) | (1<<LCD_DB5));  // clear data pins
	LCD_PORT2 &= ~((1<<LCD_DB7) | (1<<LCD_DB6));
	
	if (byte & (1<<3)) SETBIT(LCD_PORT2, LCD_DB7);
	if (byte & (1<<2)) SETBIT(LCD_PORT2, LCD_DB6);
	if (byte & (1<<1)) SETBIT(LCD_PORT1, LCD_DB5);
	if (byte & (1<<0)) SETBIT(LCD_PORT1, LCD_DB4);
	ENABLE();                                      // send lower half byte
	//_delay_us(LCD_EXECDELAY);
}

void lcd_clear (void)
{
	// clear display
	lcd_write_byte(0x01, LCD_COMMAND);
	_delay_ms(2);
}

void lcd_set_cursor_type (uint8_t c_type)
{
	switch (c_type)
	{
		case 0:
			lcd_write_byte(0x0C, LCD_COMMAND);
			break;
			
		case 1:
			lcd_write_byte(0x0E, LCD_COMMAND);
			break;
		
		case 2:
			lcd_write_byte(0x0F, LCD_COMMAND);
			break;
	}
	//_delay_us(LCD_EXECDELAY);
}

void lcd_set_cursor_position (uint8_t row, uint8_t column)
{
	if (row) // second line
	{
		column = column + 0x40;
	} 
	lcd_write_byte((column | (1<<7)), LCD_COMMAND);
	//_delay_us(LCD_EXECDELAY);
}

void lcd_shift_display(uint8_t direction)
{
	if (direction)                
	{
		lcd_write_byte(0x18, LCD_COMMAND); // shift right
	} 
	else
	{
		lcd_write_byte(0x1C, LCD_COMMAND); // shift left
	}
	//_delay_us(LCD_EXECDELAY);
}

/*void lcd_putchar (char data)
{
	LCD_PORT1 &= ~((1<<LCD_RW) | (1<<LCD_RS) | (1<<LCD_DB4) | (1<<LCD_DB5));  // clear pins
	LCD_PORT2 &= ~((1<<LCD_DB7) | (1<<LCD_DB6));
	
	SETBIT(LCD_PORT1, LCD_RS); // write data
	
	if (data & (1<<7)) SETBIT(LCD_PORT2, LCD_DB7);
	if (data & (1<<6)) SETBIT(LCD_PORT2, LCD_DB6);
	if (data & (1<<5)) SETBIT(LCD_PORT1, LCD_DB5);
	if (data & (1<<4)) SETBIT(LCD_PORT1, LCD_DB4);
	ENABLE();                     // send upper half byte
	if (data & (1<<3)) SETBIT(LCD_PORT2, LCD_DB7);
	if (data & (1<<2)) SETBIT(LCD_PORT2, LCD_DB6);
	if (data & (1<<1)) SETBIT(LCD_PORT1, LCD_DB5);
	if (data & (1<<0)) SETBIT(LCD_PORT1, LCD_DB4);
	ENABLE();                     // send lower half byte
}*/

void lcd_putstring (char *str)
{	
	while (*str)
	{
		lcd_write_byte(*str++, LCD_DATA); // write data
		_delay_us(LCD_EXECDELAY);
	}		
}

void lcd_putstring_flash (const unsigned char *str)
{
	
	while (pgm_read_byte(*str))
	{
		lcd_write_byte(pgm_read_byte(*str++), LCD_DATA); // write data from flash
		_delay_us(LCD_EXECDELAY);
	}
}