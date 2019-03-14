/*
 * ir_transmit.c
 *
 * Created: 11.08.2016 12:55:26
 *  Author: it.admin3
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

#include "avr035.h"
#include "ir_transmit.h"

ISR(TIMER2_COMPA_vect)
{
	if (OCR2A == IR_PULSE) OCR2A = IR_PAUSE;
	else OCR2A = IR_PULSE; 	
}

void ir_transmit_init (void)
{
	//CLEARBIT(IR_PORT, IR_PIN);   // ir_pin = 0
	OCR2A = IR_PAUSE;             // set compare register to pause delay
	SETBIT(TIMSK2, OCIE2A);        // enable interrupt by output compare match
	TCCR2A = (1<<COM2A0) | (1<<WGM21); // set timer/counter2 to CTC (clear timer on compare match) mode, toggle OC2A on match, start timer with no prescaling
	TCCR2B = (1<<CS20);
	SETBIT(IR_PORT_DDR, IR_PIN); // set of OC2 as output must be done last
}
