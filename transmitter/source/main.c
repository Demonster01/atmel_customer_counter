/*
 * mega48_tk02_2.c
 *
 * Created: 14.11.2016 12:16:28
 * Author : Demonster
 * ychurov@i.ua
 */ 

#define F_CPU 10000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

#include "avr035.h"
#include "ir_transmit.h"


int main(void)
{
	/* Replace with your application code */
	ir_transmit_init();
	sei();
	
	while (1)
	{
	}
}
