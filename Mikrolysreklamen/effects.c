/*
 * effects.c
 *
 * Created: 21/01/2019 21:52:28
 *  Author: Oystein
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "Mikrolysreklamen.h"
#include "api.h"
#include "effects.h"

void effect_aurora(uint8_t* bulbGroup, uint8_t color[3], uint8_t time, uint8_t fade, uint8_t nChangeBulbs, uint8_t minBrightness) {
	// uint8_t *bulbGroup;
	// uint8_t color [3];
	// uint8_t time;
	// uint8_t fade;
	// uint8_t nChangeBulbs;
	// uint8_t minBrightness;
	
	uint8_t nRepeats = (uint8_t)( time / fade );
	uint8_t numBulbs = bulbGroup[0];
	
	for (uint8_t j = 0; j < nRepeats; j++) {
		for (uint8_t i = 0; i < nChangeBulbs; i++) {
			uint8_t nextBulbIdx = (rand() % numBulbs) + 1;
			uint8_t nextBulb = bulbGroup[nextBulbIdx];
			uint8_t nextBrightness = rand() % 255;
			uint8_t colorbuffer[3];
			while (nextBrightness <= minBrightness) {
				nextBrightness = rand() % 255;
			}
			for(uint8_t k=0; k<3; k++){
				colorbuffer[k] = (color[k]*nextBrightness) / 255; // TBD do proper HSI brightness adjustment
			}
			effect_RGBFade(nextBulb, colorbuffer, fade);
		}
		skip(fade);
	}
}

void effect_RGBFade(uint8_t bulb, uint8_t endColor[3], uint8_t frames) {
	uint8_t bufferIterator_start = *bufferIterator;
	uint8_t startColor[3] = {sequenceBuffer[*bufferIterator][bulb][BLUE],
							 sequenceBuffer[*bufferIterator][bulb][GREEN],
							 sequenceBuffer[*bufferIterator][bulb][RED]};
	volatile uint8_t delta_r, delta_g, delta_b;
	
	if (endColor[RED] > startColor[RED]) {
		delta_r = (endColor[RED]   - startColor[RED])   / frames;
	} else {
		delta_r = 0;
	}
	if (endColor[GREEN] > startColor[GREEN]) {
		delta_g = (endColor[GREEN] - startColor[GREEN]) / frames;
		} else {
		delta_g = 0;
	}
	if (endColor[BLUE] > startColor[BLUE]) {
		delta_b = (endColor[BLUE]  - startColor[BLUE])  / frames;
		} else {
		delta_b = 0;
	}

	for(uint8_t frame = 1; frame <= frames; frame++) { // && !isCancelled()
		uint8_t red   = (startColor[RED]   + (uint8_t)(delta_r*frame));
		uint8_t green = (startColor[GREEN] + (uint8_t)(delta_g*frame));
		uint8_t blue  = (startColor[BLUE]  + (uint8_t)(delta_b*frame));

		bulb_setRGB(bulb, red, green, blue);
		next();
	}
	*bufferIterator = bufferIterator_start;
}

void effect_fill_group(uint8_t* bulbGroup, uint8_t *color, uint8_t frames){
	uint8_t numBulbs = bulbGroup[0];
	
	for(uint8_t j=0; j<numBulbs; j++){
		uint8_t bufferIterator_start = *bufferIterator;
		for (uint8_t frame=0; frame<frames; frame++){
			for(uint8_t i=0; i<3; i++){
				sequenceBuffer[frame][bulbGroup[j+1]][i] = color[i];
			}
			next();
		}
		*bufferIterator = bufferIterator_start;
	}
}