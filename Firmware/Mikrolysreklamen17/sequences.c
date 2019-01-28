/*
 * sequences.c
 *
 * Created: 2019-01-27 14:59:27
 *  Author: Oystein
 */ 

#include <avr/io.h>
#include "Mikrolysreklamen.h"
#include "bulbgroup.h"
#include "effects.h"

void sequence_AuroraDemo( void ) {
	uint8_t c[3]   = {57, 255, 20}; // neon green
	uint8_t c_b[3] = {0, 70, 20}; // background green
	// (uint8_t* bulbGroup, uint8_t numBulbs, uint8_t* color, uint8_t time, uint8_t fade, uint8_t nChangeBulbs, uint8_t minBrightness);
	for (uint8_t i=0; i<5; i++){
		api_fill(c_b);
		effect_aurora(mergedAllBulbs, 82, c, 16, 2, 30, 0x30);
		*bufferIterator = 0;
		play();
	}
}

void sequence_Glitter( void ) {
	uint8_t c[3]   = {212,175,0}; // Gold
	uint8_t c_b[3] = {0, 0, 0}; // Background
	// (uint8_t* bulbGroup, uint8_t numBulbs, uint8_t* color, uint8_t time, uint8_t fade, uint8_t nChangeBulbs, uint8_t minBrightness);
	for (uint8_t i=0; i<5; i++){
		api_fill(c_b);
		effect_aurora(mergedAllBulbs, 82, c, 16, 2, 30, 0x30);
		*bufferIterator = 0;
		play();
	}
}

void sequence_rgbFadeDemo( void ){
	api_clear();
	uint8_t c[3] = {190, 0, 127};
	for(uint8_t i = 0; i<NUM_LEDS; i++){
		effect_RGBFade(i, c, 16);
	}
	*bufferIterator = 0;
	play();
}