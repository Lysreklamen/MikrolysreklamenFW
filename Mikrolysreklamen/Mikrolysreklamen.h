/*
 * Mikrolysreklamen.h
 *
 * Created: 2019-01-17 20:56:19
 *  Author: medlem
 */ 


#ifndef MIKROLYSREKLAMEN_H_
#define MIKROLYSREKLAMEN_H_

//#define UKA15 // LURIFAX
//#define UKA17 // Ta-De-Du!
//#define UKA19 // Vivillé
//#define UKA21 // Razzmatazz
#define UKA23 // SPRÆKK
//#define ARK100
//#define TEST

#define FW_VERSION "0.1.0"
#define FW_VERSION_LEN 5

#define F_CPU 32000000UL

#include <avr/io.h>

#define APA_PORT PORTD
#define CLK_PIN 7
#define DATA_PIN 5

#ifdef UKA15
#define NUM_LEDS 83
#endif

#ifdef UKA17
#define NUM_LEDS 82
#endif

#ifdef UKA19
#define NUM_LEDS 49
#endif

#ifdef UKA21
#define NUM_LEDS 83
#endif

#ifdef UKA23
#define NUM_LEDS 60
#endif

#ifdef ARK100
#define NUM_LEDS 42
#endif

#define BULBCHANNELS 3
#define RED 0
#define GREEN 1
#define BLUE 2

#define AVAIL_MEM 8
#define BUFFERSIZE  AVAIL_MEM


typedef uint8_t uint8_sequencebuffer_t[BUFFERSIZE][NUM_LEDS][3];
typedef uint8_t uint8_framebuffer_t[NUM_LEDS][3];

//volatile extern uint8_sequencebuffer_t sequenceBuffer;
volatile extern uint8_framebuffer_t frameBuffer;

volatile extern uint8_t bufferIteratorA;
volatile extern uint8_t bufferIteratorB;

volatile extern uint8_t *bufferIterator;

volatile extern uint8_t Timer1;
volatile extern uint8_t Timer2;  /* 100Hz decrement timer */

void write_fw_version(void);

#endif /* MIKROLYSREKLAMEN_H_ */