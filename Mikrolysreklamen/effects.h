/*
 * effects.h
 *
 * Created: 21/01/2019 21:52:41
 *  Author: Oystein
 */ 


#ifndef EFFECTS_H_
#define EFFECTS_H_

#include <avr/io.h>

void effect_aurora(uint8_t* bulbGroup, uint8_t color[3], uint8_t time, uint8_t fade, uint8_t nChangeBulbs, uint8_t minBrightness);
void effect_RGBFade(uint8_t bulb, uint8_t* endColor, uint8_t frames);

void effect_fill_group(uint8_t* bulbGroup, uint8_t *color, uint8_t frames);


#endif /* EFFECTS_H_ */