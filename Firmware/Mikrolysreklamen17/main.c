/*
 * Mikrolysreklamen17.c
 *
 * Created: 2019-01-17 18:18:21
 * Author : medlem
 */ 

#include <avr/io.h>
#include "Mikrolysreklamen.h"
#include "apa102.h"

#define APA_PORT PORTD
#define CLK_PIN 7
#define DATA_PIN 5

void setup( void );


int main(void)
{
	setup();
	setupapa();
	
	uint8_t framebuffer[NUM_LEDS][3];
	
	for(uint8_t j=0; j<82; j++){
		for (uint8_t i=0; i<3; i++){
			//if(i == 0){
				framebuffer[j][i] = 0x00;
			//} else {
			//	framebuffer[j][i] = 0x00;
			//}
		}
	}
	
	pushframe(framebuffer, 1);
	
	framebuffer[0][RED] = 0xF0;
	framebuffer[1][GREEN] = 0xF0;
	framebuffer[2][RED] = 0xF0;
	
	while (1) {
		pushframe(framebuffer, 1);
	}
}

void setup ( void ) {
	// Select internal 32MHz Oscillator as clock source
	//OSC.CTRL = 0b001;
}