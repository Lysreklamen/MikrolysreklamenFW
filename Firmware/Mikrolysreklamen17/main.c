/*
 * Mikrolysreklamen17.c
 *
 * Created: 2019-01-17 18:18:21
 * Author : medlem
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#include "Mikrolysreklamen.h"
#include "apa102.h"

#define APA_PORT PORTD
#define CLK_PIN 7
#define DATA_PIN 5

void setup( void );
void clear(uint8_t framebuffer[][3]);
void fill(uint8_t framebuffer[][3], uint8_t val);

int main(void)
{
	setup();
	setupapa();
	
	uint8_t framebuffer[NUM_LEDS][3];
	clear(framebuffer);
	pushframe(framebuffer, 1);
	
	while (1) {
		for(uint8_t i = 0; i<3; i++){
			_delay_ms(1000);
			clear(framebuffer);
			for(uint8_t j=0; j<NUM_LEDS; j++){
				framebuffer[j][i] = 0x40;
			}
			pushframe(framebuffer, 1);
		}
	}
}

void setup ( void ) {
	// Select internal 32MHz Oscillator as clock source
	//OSC.CTRL = 0b001;
}

void clear(uint8_t framebuffer[][3]){
	fill(framebuffer, 0x00);
}

void fill(uint8_t framebuffer[][3], uint8_t val){
	for(uint8_t j=0; j<NUM_LEDS; j++){
		for (uint8_t i=0; i<3; i++){
			framebuffer[j][i] = val;
		}
	}
}
