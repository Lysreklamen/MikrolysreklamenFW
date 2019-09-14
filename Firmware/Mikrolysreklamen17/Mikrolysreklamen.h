/*
 * Mikrolysreklamen.h
 *
 * Created: 2019-01-17 20:56:19
 *  Author: medlem
 */ 


#ifndef MIKROLYSREKLAMEN_H_
#define MIKROLYSREKLAMEN_H_

#define F_CPU 32000000UL

#include <avr/io.h>

#define APA_PORT PORTD
#define CLK_PIN 7
#define DATA_PIN 5

#define NUM_LEDS 82

#define RED 0
#define GREEN 1
#define BLUE 2

#define AVAIL_MEM 8
#define BUFFERSIZE  AVAIL_MEM

typedef uint8_t uint8_sequencebuffer_t[BUFFERSIZE][NUM_LEDS][3];

volatile extern uint8_sequencebuffer_t sequenceBuffer;

volatile extern uint8_t bufferIteratorA;
volatile extern uint8_t bufferIteratorB;

volatile extern uint8_t *bufferIterator;

volatile extern uint8_t Timer1;
volatile extern uint8_t Timer2;  /* 100Hz decrement timer */

#endif /* MIKROLYSREKLAMEN_H_ */