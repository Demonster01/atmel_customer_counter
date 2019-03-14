/*
 * fecc_lcd.h
 *
 * Created: 12.08.2016 17:01:05
 *  Author: it.admin3
 * Library for Fordata FECC1602D-FLYYBW-65LR LCD
 * 4-bit interface mode, 2 rows, 16 columns
 */ 


#ifndef FECC_LCD_H_
#define FECC_LCD_H_

#define F_CPU 4000000UL

//! define ports
#define LCD_PORT1  PORTA
#define LCD_DDR1   DDRA
#define LCD_PIN1   PINA
#define LCD_PORT2  PORTB
#define LCD_DDR2   DDRB
#define LCD_PIN2   PINB

//! define pins
#define LCD_RS     PINA3
#define LCD_RW     PINA4
#define LCD_E      PINA2

#define LCD_DB4    PINA1
#define LCD_DB5    PINA0
#define LCD_DB6    PINB0
#define LCD_DB7    PINB1

// define masks
#define LCD_PORT1_BITMASK (uint8_t) ((1<<LCD_RW) | (1<<LCD_RS) | (1<<LCD_E) | (1<<LCD_DB4) | (1<<LCD_DB5))
#define LCD_PORT2_BITMASK (uint8_t) ((1<<LCD_DB6) | (1<<LCD_DB7))

// define delay of enable cycle in us
#define LCD_CLEARDELAY 2
#define LCD_EXECDELAY   38

// define ENABLE cycle (min 500ns by datasheet)
#define ENABLE() ({SETBIT(LCD_PORT1, LCD_E); asm("nop"); asm("nop"); asm("nop"); CLEARBIT(LCD_PORT1, LCD_E);})

// define status
#define LCD_COMMAND 0
#define LCD_DATA    1

// define cursor type
#define LCD_CURSOR_OFF   0
#define LCD_CURSOR_ON    1
#define LCD_CURSOR_BLINK 2

// define display shift direction
#define LCD_SHIFT_LEFT  0
#define LCD_SHIFT_RIGHT 1

// define functions
void lcd_init (void);                                    // init pins, set 4-bit mode, clear screen, set cursor to first symbol of first line
//char lcd_read_byte(char status);                         // read byte as status of RS: 0 - command, 1 - data
void lcd_write_byte(uint8_t byte, uint8_t status);             // write byte as status of RS: 0 - command, 1 - data
//char lcd_busy_flag (void);                               // read lcd busy flag: if 0x00 - ready, if 0xFF - busy
void lcd_clear (void);                                   // clear screen, set cursor to first symbol of first line !!! set delay to 1.52ms before next operation
void lcd_set_cursor_type (uint8_t c_type);                  // set cursor to ON, OFF or BLINK !!! display is on
void lcd_set_cursor_position (uint8_t row, uint8_t column);    // set cursor to row (0-1) and column (0-15) !!! overflow is not handled 
void lcd_shift_display(uint8_t direction);                  // shift display LEFT (0) or RIGHT (1)
//void lcd_putchar (char data);                            // put char to current position
void lcd_putstring (char *str);                          // put string to current position
void lcd_putstring_flash (const unsigned char *str);     // put string to current position from flash

// Cyrillic symbols conversion
/*
if (byte >= 0xA0 && state != 0)
{
	switch (byte)
	{
		case 0xC0: byte = 0x41; break;//�
		case 0xC1: byte = 0xA0; break;//�
		case 0xC2: byte = 0x42; break;//�
		case 0xC3: byte = 0xA1; break;//�
		case 0xC4: byte = 0xE0; break;//�
		case 0xC5: byte = 0x45; break;//�
		case 0xA8: byte = 0xA2; break;//�
		case 0xC6: byte = 0xA3; break;//�
		case 0xC7: byte = 0xA4; break;//�
		case 0xC8: byte = 0xA5; break;//�
		case 0xC9: byte = 0xA6; break;//�
		case 0xCA: byte = 0x4B; break;//�
		case 0xCB: byte = 0xA7; break;//�
		case 0xCC: byte = 0x4D; break;//�
		case 0xCD: byte = 0x48; break;//H
		case 0xCE: byte = 0x4F; break;//O
		case 0xCF: byte = 0xA8; break;//�
		case 0xD0: byte = 0x50; break;//P
		case 0xD1: byte = 0x43; break;//C
		case 0xD2: byte = 0x54; break;//T
		case 0xD3: byte = 0xA9; break;//�
		case 0xD4: byte = 0xAA; break;//�
		case 0xD5: byte = 0x58; break;//X
		case 0xD6: byte = 0xE1; break;//�
		case 0xD7: byte = 0xAB; break;//�
		case 0xD8: byte = 0xAC; break;//�
		case 0xD9: byte = 0xE2; break;//�
		case 0xDA: byte = 0xAD; break;//�
		case 0xDB: byte = 0xAE; break;//�
		case 0xDC: byte = 0x62; break;//�
		case 0xDD: byte = 0xAF; break;//�
		case 0xDE: byte = 0xB0; break;//�
		case 0xDF: byte = 0xB1; break;//�
		case 0xE0: byte = 0x61; break;//�
		case 0xE1: byte = 0xB2; break;//�
		case 0xE2: byte = 0xB3; break;//�
		case 0xE3: byte = 0xB4; break;//�
		case 0xE4: byte = 0xE3; break;//�
		case 0xE5: byte = 0x65; break;//�
		case 0xB8: byte = 0xB5; break;//�
		case 0xE6: byte = 0xB6; break;//�
		case 0xE7: byte = 0xB7; break;//�
		case 0xE8: byte = 0xB8; break;//�
		case 0xE9: byte = 0xB9; break;//�
		case 0xEA: byte = 0xBA; break;//�
		case 0xEB: byte = 0xBB; break;//�
		case 0xEC: byte = 0xBC; break;//�
		case 0xED: byte = 0xBD; break;//�
		case 0xEE: byte = 0x6F; break;//�
		case 0xEF: byte = 0xBE; break;//�
		case 0xF0: byte = 0x70; break;//�
		case 0xF1: byte = 0x63; break;//�
		case 0xF2: byte = 0xBF; break;//�
		case 0xF3: byte = 0x79; break;//�
		case 0xF4: byte = 0xE4; break;//�
		case 0xF5: byte = 0x78; break;//�
		case 0xF6: byte = 0xE5; break;//�
		case 0xF7: byte = 0xC0; break;//�
		case 0xF8: byte = 0xC1; break;//�
		case 0xF9: byte = 0xE6; break;//�
		case 0xFA: byte = 0xC2; break;//�
		case 0xFB: byte = 0xC3; break;//�
		case 0xFC: byte = 0xC4; break;//�
		case 0xFD: byte = 0xC5; break;//�
		case 0xFE: byte = 0xC6; break;//�
		case 0xFF: byte = 0xC7; break;//�
	}
}

*/

#endif /* FECC_LCD_H_ */