/*
 * ir_transmit.h
 *
 * Created: 11.08.2016 12:55:10
 *  Author: it.admin3
 */ 


#ifndef IR_TRANSMIT_H_
#define IR_TRANSMIT_H_

//! define ir transmit pin here
#define IR_PIN  PINB3     // PB3/MOSI/OC2A timer/counter2 output compare match
//#define IR_PORT PORTB	
#define IR_PORT_DDR DDRB

// constants for OCR2 compare register
// for F_CPU = 4 MHz and prescaler = 1 one CPU tic is 1 / 4MHz = 0.25us
// for F_CPU = 4 MHz and prescaler = 8 one CPU tic is 8 / 4MHz = 2us
// for F_CPU = 8 MHz and prescaler = 1 one CPU tic is 1 / 8MHz = 0.125us
// for F_CPU = 10 MHz and prescaler = 1 one CPU tic is 1 / 10MHz = 0.1us
#define IR_PULSE 69      //  6.944 us / 0.1 us ~ 69 counts of timer
#define IR_PAUSE 208      // 20.833 us / 0.1 us ~ 208 counts of timer

void ir_transmit_init (void);


#endif /* IR_TRANSMIT_H_ */