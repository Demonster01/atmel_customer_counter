/*
 * ir.h
 *
 * Created: 30.07.2016 18:38:11
 *  Author: it.admin3
 */ 


#ifndef IR_H_
#define IR_H_

// define ir pins - must be on same port
#define IR_IN   PINB1
#define IR_OUT  PINB2
#define IR_MASK (uint8_t) ((1<<IR_IN) | (1<<IR_OUT))
#define IR_IN_MASK (uint8_t) (1<<IR_IN)
#define IR_OUT_MASK (uint8_t) (1<<IR_OUT)
#define IR_PORT PINB

volatile struct ir_struct
{
	uint8_t status;       // current status of passage: 0 - free; 1 - in; 2 - out; 3 - in count; 4 - out count; 5 - busy; 0xFF - error
	//uint8_t status_old;   // previous status
	uint8_t passing;      // save how many interrupts with status 3 "now passing" is occured
	uint16_t in_counter;  // save input counter
	uint16_t out_counter; // save output counter
} ir;

void ir_init (void);

#endif /* IR_H_ */