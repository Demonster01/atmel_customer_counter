/*
 * ir.c
 *
 * Created: 30.07.2016 18:37:54
 *  Author: it.admin3
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
//#include <stdlib.h>

#include "ir.h"
#include "avr035.h"
//#include "uart.h"

// F_CPU 4000000UL
// timer prescaler 256
// timer0 overflow interrupt every 1/4000000 * 256 * 256 = 16.384 ms
// static const uint8_t ir_prescaler = (1 << CS02);

// F_CPU 7372800UL
// timer prescaler 256
// timer0 overflow interrupt every 1/7372800 * 256 * 256 = 8.889 ms
// static const uint8_t ir_prescaler = (1 << CS02);

// F_CPU 14745600UL
// timer prescaler 1024
// timer0 overflow interrupt every 1/14745600 * 256 * 1024 = 17.778 ms
// static const uint8_t ir_prescaler = (1 << CS02);

// F_CPU 14745600UL
// timer prescaler 1024
// timer0 overflow interrupt every 1/14745600 * 256 * 256 = 4.444 ms
// static const uint8_t ir_prescaler = (1 << CS02);

void ir_init (void)
{
	SETBIT(TIMSK0, TOIE0);  // timer0 interrupt enable
	SETBIT(TCCR0B, CS02);   // start timer with prescaler 256
	SETBIT(TCCR0B, CS00);   // start timer with prescaler 1024	
	//SETBIT(PORTB,IR_IN);   // set pull-up resistors
	//SETBIT(PORTB,IR_IN);	
}

ISR(TIMER0_OVF_vect)
{
	uint8_t temp;
	//char str[5];
	
	temp = IR_PORT & IR_MASK;
		
	switch (temp)
	{
		case 0:
			ir.passing = 0;
			switch (ir.status)
			{
				case 3:
					ir.status = 4; // in count
					break;
				
				case 4: // not counted yet
					break;
				
				case 7:
					ir.status = 8; // out count
					break;
				
				case 8: // not counted yet
					break;
				
				default:
					ir.status = 0; // passage is free
					break;
			}
			break;
		
		case IR_IN_MASK:
			switch (ir.status)
			{
				case 0:
					ir.status = 1; // in
					break;
			
				case 1:
					ir.passing++; // still in
					break;
			
				case 4: // not counted yet
					break;
				
				case 6:
					ir.status = 7; // out count before free
					break;
				
				case 7:
					ir.passing++; // still in
					break;
				
				case 8: // not counted yet
					break;
			
				default:
					ir.status = 1;
					ir.passing++; // in but with fluctuations
					break;			
			}
			break;			
			
		case IR_OUT_MASK:
			switch (ir.status)
			{
				case 0:
					ir.status = 5; // out
					break;
				
				case 2:
					ir.status = 3; // in count before free
					break;
				
				case 3:
					ir.passing++; // still out
					break;
				
				case 4: // not counted yet
					break;
				
				case 5:
					ir.passing++; // still out
					break;
					
				case 8: // not counted yet
					break;
				
				default:
					ir.status = 5;
					ir.passing++; // out but with fluctuations
					break;
			}
			break;
			
		case IR_MASK:
			switch (ir.status)
			{
				case 0:
					ir.status = 9;
					ir.passing++; // error - no signal
					break;
				
				case 1:
					ir.status = 2; // busy before out
					break;
								
				case 3:
					ir.status = 2; // busy before out
					ir.passing++;
					break;
					
				case 4: // not counted yet
					break;
				
				case 5:
					ir.status = 6; // busy before in
					break;
									
				case 7:
					ir.status = 6; // busy before in
					ir.passing++;
					break;
				
				case 8: // not counted yet
					break;
				
				default:
					ir.passing++; //  error - no signal
					break;
			}			
			break;
	}
	
	//if (ir.passing > 200) // 200 * 16.384 = 3.277 sec
	// 250 * 4.444 = 1.111 sec
	if (ir.passing > 250) // 250 * 17.778 = 4.44 sec
	{
		ir.passing = 250;
		ir.status = 0xFF; // error - no signal too long
	}
	/*
	if (ir.status)
	{
		utoa(ir.status,str,10);
		uart_putstring(str);
	}*/
		
}