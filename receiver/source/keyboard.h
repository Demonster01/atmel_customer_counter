/*
 * keyboard.h
 *
 * Created: 16.08.2016 13:01:14
 *  Author: it.admin3
 */ 


#ifndef KEYBOARD_H_
#define KEYBOARD_H_

// define keys pins and ports
#define KEY_PORT  PORTC
#define KEY_DDR   DDRC
#define KEY_MENU  PINC7
#define KEY_LEFT  PINC4
#define KEY_RIGHT PINC6
#define KEY_EXIT  PINC5

#define KEY_DELAY_US 3

#endif /* KEYBOARD_H_ */