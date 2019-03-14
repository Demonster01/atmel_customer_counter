/*
 * speaker.c
 *
 * Created: 30.07.2016 21:25:19
 *  Author: it.admin3
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#include "speaker.h"
#include "avr035.h"

ISR(TIMER2_OVF_vect)
{
	FLIPBIT(SPEAKER_PORT,SPEAKER_PIN);
}

void speaker_init (void)
{
	SETBIT(SPEAKER_DDR,SPEAKER_PIN);
	SETBIT(TIMSK2,TOIE2);
	SETBIT(SPEAKER_PORT,SPEAKER_PIN); // speaker connected to +5V, so set bit to 1 will stop sound
}

void speaker_play (void)
{
	SETBIT(TCCR2B,CS21); // set prescaler 8
}

void speaker_stop (void)
{
	CLEARBIT(TCCR2B,CS21);             // set prescaler 0 will stop timer
	TCNT2 = 0;                        // clear counter
	SETBIT(SPEAKER_PORT,SPEAKER_PIN); // speaker connected to +5V, so set bit to 1 will stop sound
}