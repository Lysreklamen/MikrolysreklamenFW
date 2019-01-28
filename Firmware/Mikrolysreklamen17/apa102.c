/*
 * apa102.c
 *
 * Created: 2019-01-17 20:37:45
 *  Author: medlem
 */ 

#include <avr/io.h>
#include "Mikrolysreklamen.h"
#include "apa102.h"

void setupapa( void ){
	// Set clk and data pins as output
	APA_PORT.DIR = (1 << CLK_PIN) | (1 << DATA_PIN);
	// Set low just in case
	APA_PORT.OUT = 0;
}

void startframe ( void ){
	bitbangbonanza(0);
	bitbangbonanza(0);
	bitbangbonanza(0);
	bitbangbonanza(0);
}

void endframe ( uint8_t count ){
	for (uint8_t i = 0; i < (count + 14)/16; i++){
		bitbangbonanza(0);
	}
}

void bitbangbonanza( uint8_t val){
	APA_PORT.OUT = ( (val >> 7 & 1) << DATA_PIN ); // MSB of data
	APA_PORT.OUT |= (1 << CLK_PIN); // Set clk high
	APA_PORT.OUT &= ~(1 << CLK_PIN); // Set clk low
	APA_PORT.OUT = ( (val >> 6 & 1) << DATA_PIN );
	APA_PORT.OUT |= (1 << CLK_PIN);
	APA_PORT.OUT &= ~(1 << CLK_PIN);
	APA_PORT.OUT = ( (val >> 5 & 1) << DATA_PIN );
	APA_PORT.OUT |= (1 << CLK_PIN);
	APA_PORT.OUT &= ~(1 << CLK_PIN);
	APA_PORT.OUT = ( (val >> 4 & 1) << DATA_PIN );
	APA_PORT.OUT |= (1 << CLK_PIN);
	APA_PORT.OUT &= ~(1 << CLK_PIN);
	APA_PORT.OUT = ( (val >> 3 & 1) << DATA_PIN );
	APA_PORT.OUT |= (1 << CLK_PIN);
	APA_PORT.OUT &= ~(1 << CLK_PIN);
	APA_PORT.OUT = ( (val >> 2 & 1) << DATA_PIN );
	APA_PORT.OUT |= (1 << CLK_PIN);
	APA_PORT.OUT &= ~(1 << CLK_PIN);
	APA_PORT.OUT = ( (val >> 1 & 1) << DATA_PIN );
	APA_PORT.OUT |= (1 << CLK_PIN);
	APA_PORT.OUT &= ~(1 << CLK_PIN);
	APA_PORT.OUT = ( (val >> 0 & 1) << DATA_PIN ); // LSB of data
	APA_PORT.OUT |= (1 << CLK_PIN);
	APA_PORT.OUT &= ~(1 << CLK_PIN);
}

void pushframe(uint8_t framebuffer[][3], uint8_t brightness){
	startframe();
	for(uint8_t i=0; i<NUM_LEDS; i++){
		bitbangbonanza(0b11100000 | brightness); // Brightness
		bitbangbonanza(framebuffer[i][BLUE]); // B
		bitbangbonanza(framebuffer[i][GREEN]); // G
		bitbangbonanza(framebuffer[i][RED]); // R
	}
	endframe(NUM_LEDS);
}

void pushframe_global(uint8_t frame, uint8_t brightness){
	startframe();
	for(uint8_t i=0; i<NUM_LEDS; i++){
		bitbangbonanza(0b11100000 | brightness); // Brightness
		bitbangbonanza(sequenceBuffer[frame][i][BLUE]); // B
		bitbangbonanza(sequenceBuffer[frame][i][GREEN]); // G
		bitbangbonanza(sequenceBuffer[frame][i][RED]); // R
	}
	endframe(NUM_LEDS);
}