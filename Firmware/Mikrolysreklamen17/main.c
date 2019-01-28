/*
 * Mikrolysreklamen17.c
 *
 * Created: 2019-01-17 18:18:21
 * Author : medlem
 */ 

#include "Mikrolysreklamen.h"
#include "apa102.h"
#include "api.h"
#include "effects.h"
#include "sequences.h"
#include <avr/io.h>
#include <util/delay.h>

#define APA_PORT PORTD
#define CLK_PIN 7
#define DATA_PIN 5


void setup( void );

//volatile uint8_sequencebuffer_t sequenceBufferA;
//volatile uint8_sequencebuffer_t sequenceBufferB;

volatile uint8_t bufferIteratorA = 0;
volatile uint8_t bufferIteratorB = 0;

volatile uint8_sequencebuffer_t sequenceBuffer;
volatile uint8_t *bufferIterator;

int main(void)
{
	setup();
	setupapa();
	
	while (1) {
		sequence_AuroraDemo();
		//sequence_Glitter();
		//sequence_rgbFadeDemo();
	}
}

void setup ( void ) {
	// Select internal 32MHz Oscillator as clock source
	//OSC.CTRL = 0b001;
	NVM.CTRLB |= (1 << 3); // Set EEPROM to memory mapped access
	
	
	srand(1337 % 255);
	
	bufferIterator = &bufferIteratorA;
}
