/*
 * sequences.c
 *
 * Created: 2019-01-27 14:59:27
 *  Author: Oystein
 */ 

#include <avr/io.h>
#include "Mikrolysreklamen.h"
#include "bulbgroup.h"
#include "api.h"
#include "effects.h"

void sequence_AuroraDemo( void ) {
	uint8_t c[3]   = {57, 255, 20}; // neon green
	uint8_t c_b[3] = {0, 70, 20}; // background green
	// (uint8_t* bulbGroup, uint8_t* color, uint8_t time, uint8_t fade, uint8_t nChangeBulbs, uint8_t minBrightness);
	for (uint8_t i=0; i<5; i++){
		api_fill(c_b);
		effect_aurora(allBulbs, c, 16, 2, 30, 0x30);
		*bufferIterator = 0;
		play();
	}
}

void sequence_Glitter( void ) {
	uint8_t c[3]   = {212,175,0}; // Gold
	uint8_t c_b[3] = {0, 0, 0}; // Background
	// (uint8_t* bulbGroup, uint8_t* color, uint8_t time, uint8_t fade, uint8_t nChangeBulbs, uint8_t minBrightness);
	for (uint8_t i=0; i<5; i++){
		api_fill(c_b);
		effect_aurora(allBulbs, c, 16, 2, 30, 0x30);
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

void sequence_letterDemo( void ){
	uint8_t c[3] = {200, 0, 0};
	uint8_t blank[3] = {0,0,0};
	effect_fill_group(letter_A, c, 8);
	play_frames(8);
	effect_fill_group(letter_A, blank, 8);
	effect_fill_group(letter_B, c, 8);
	play_frames(8);
	effect_fill_group(letter_B, blank, 8);
	effect_fill_group(letter_C, c, 8);
	play_frames(8);
	effect_fill_group(letter_C, blank, 8);
	effect_fill_group(letter_D, c, 8);
	play_frames(8);
	effect_fill_group(letter_D, blank, 8);
	effect_fill_group(letter_E, c, 8);
	play_frames(8);
	effect_fill_group(letter_E, blank, 8);
	effect_fill_group(letter_F, c, 8);
	play_frames(8);
	effect_fill_group(letter_F, blank, 8);
	effect_fill_group(letter_G, c, 8);
	play_frames(8);
	effect_fill_group(letter_G, blank, 8);
	effect_fill_group(letter_H, c, 8);
	play_frames(8);
	effect_fill_group(letter_H, blank, 8);
	effect_fill_group(letter_I, c, 8);
	play_frames(8);
	effect_fill_group(letter_I, blank, 8);
	play_frames(8);
}

void sequence_digitDemo( void ){
	uint8_t c[3] = {200, 0, 0};
	uint8_t blank[3] = {0,0,0};
	effect_fill_group(digit_A, c, 8);
	play_frames(8);
	effect_fill_group(digit_A, blank, 8);
	effect_fill_group(digit_B, c, 8);
	play_frames(8);
	effect_fill_group(digit_B, blank, 8);
	effect_fill_group(digit_C, c, 8);
	play_frames(8);
	effect_fill_group(digit_C, blank, 8);
	play_frames(8);
}