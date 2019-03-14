/*
 * speaker.h
 *
 * Created: 30.07.2016 21:25:01
 *  Author: it.admin3
 */ 


#ifndef SPEAKER_H_
#define SPEAKER_H_

// define speaker pin
#define SPEAKER_PIN  PINB0
#define SPEAKER_DDR  DDRB
#define SPEAKER_PORT PORTB

void speaker_init (void);
void speaker_play (void);
void speaker_stop (void);

#endif /* SPEAKER_H_ */