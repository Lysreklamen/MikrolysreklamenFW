/*
 * api.h
 *
 * Created: 21/01/2019 21:54:34
 *  Author: Oystein
 */ 


#ifndef API_H_
#define API_H_

#include <avr/io.h>

void play ( void );
void play_frames(uint8_t frames);
void api_clear( void );
void api_fill(uint8_t *color);
void api_fill_frame(uint8_t frame, uint8_t *color);

void skip(uint8_t frames);
void next( void );
//uint8_t* getColor(uint8_t bulb);
//uint8_t* RGBtoHSB(uint8_t color_red, uint8_t color_green, uint8_t color_blue);
void bulb_setRGB(uint8_t bulb, uint8_t color_red, uint8_t color_green, uint8_t color_blue);

#endif /* API_H_ */