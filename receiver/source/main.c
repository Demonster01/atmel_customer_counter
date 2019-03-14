/*
 * tk02_1.c
 *
 * Created: 19.02.2017 16:13:41
 * Author : Demonster
 * ychurov@i.ua
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
//#include <string.h>

#include "avr035.h"
#include "uart.h"
#include <util/delay.h>
//#include "fecc_lcd.h"
//#include "keyboard.h"
//#include "rtc.h"
//#include "eeprom.h"
#include "speaker.h"
#include "ir.h"

#define LED_PIN  PIND7
#define LED_DDR  DDRD
#define LED_PORT PORTD

#define DIR_PIN PIND6 // Direction jumper
#define DIR_PORT PIND

int main(void)
{
	char str[10];
    /* Replace with your application code */
	
	/*
	lcd_init();
	lcd_set_cursor_type(LCD_CURSOR_OFF);
	_delay_us(LCD_EXECDELAY);
	lcd_putstring ("00:00");
	lcd_set_cursor_position(0,7);
	_delay_us(LCD_EXECDELAY);
	lcd_putstring ("01/01/80");
	lcd_set_cursor_position(1,0);
	_delay_us(LCD_EXECDELAY);
	lcd_putstring ("Bx:0");
	lcd_set_cursor_position(1,7);
	_delay_us(LCD_EXECDELAY);
	lcd_putstring ("Bux:0");
	*/

	ir_init();
	
	speaker_init();
	
	uart_init();
	/*
	uart_putstring("Counter test");
	uart_putchar('\n');
	uart_putchar('\r');
	*/
	uart_putstring("IN0");
	uart_putstring("OUT0");
	
	SETBIT(LED_DDR,LED_PIN);
	SETBIT(LED_PORT,LED_PIN); // LED connected to +5V, so set bit to 1 will off LED
	
	sei();
		
    while (1) 
    {
		if (CHECKBIT(DIR_PORT,DIR_PIN))
		{
			switch (ir.status)
			{			
				case 4:
					ir.in_counter++;
					ir.status = 0;
					speaker_stop();
					utoa(ir.in_counter, str, 10);
					uart_putchar('I');
					uart_putchar('N');					
					uart_putstring(str);				
					FLIPBIT(LED_PORT,LED_PIN);
					break;
			
				case 8:
					ir.out_counter++;
					ir.status = 0;
					speaker_stop();
					utoa(ir.out_counter, str, 10);
					uart_putchar('O');
					uart_putchar('U');
					uart_putchar('T');
					uart_putstring(str);				
					FLIPBIT(LED_PORT,LED_PIN);
					break;
						
				case 0xFF:			
					speaker_play();
					break;
									
				default:
					speaker_stop();
					break;						
			}
		} 
		else
		{
			switch (ir.status)
			{
				case 8:
				ir.in_counter++;
				ir.status = 0;
				speaker_stop();
				utoa(ir.in_counter, str, 10);
				uart_putchar('I');
				uart_putchar('N');				
				uart_putstring(str);
				FLIPBIT(LED_PORT,LED_PIN);
				break;
				
				case 4:
				ir.out_counter++;
				ir.status = 0;
				speaker_stop();
				utoa(ir.out_counter, str, 10);
				uart_putchar('O');
				uart_putchar('U');
				uart_putchar('T');				
				uart_putstring(str);
				FLIPBIT(LED_PORT,LED_PIN);
				break;
				
				case 0xFF:
				speaker_play();
				break;
				
				default:
				speaker_stop();
				break;
			}			
		}
		
		// work with clock, display, keyboard
		//utoa(ir.status,str,10);
		//uart_putstring(str);
		//_delay_ms(8);
		
    }
}

