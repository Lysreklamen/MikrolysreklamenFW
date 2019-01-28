/*
 * api.c
 *
 * Created: 21/01/2019 21:54:45
 *  Author: Oystein
 */ 

#include <avr/io.h>
#include "Mikrolysreklamen.h"
#include "api.h"
#include <util/delay.h>

#define MAX_PWM 255
#define GAMMA   1.8

void play( void ) {
	for(uint8_t i = 0; i<BUFFERSIZE; i++){
		pushframe_global(i, 1);
		if (i != BUFFERSIZE-1){
			_delay_ms(5);
		}
	}
}

void play_frames(uint8_t frames) {
	for(uint8_t i = 0; i<frames; i++){
		pushframe_global(i, 1);
		if (i != frames-1){
			_delay_ms(5);
		}
	}
}

void skip(uint8_t frames){
	(*bufferIterator) += frames;
}

void next( void ){
	(*bufferIterator)++;
}

void api_clear( void ){
	uint8_t color[3] = {0,0,0};
	api_fill(color);
}

void api_fill(uint8_t *color){
	for (uint8_t k=0; k<BUFFERSIZE; k++) {
		api_fill_frame(k, color);
	}
}

void api_fill_frame(uint8_t frame, uint8_t *color){
	for(uint8_t j=0; j<NUM_LEDS; j++){
		for(uint8_t i=0; i<3; i++){
			sequenceBuffer[frame][j][i] = color[i];
		}
	}
}

/* Make macro instead
uint8_t[][] getColor(uint8_t bulb){
	return sequenceBuffer[*bufferIterator][bulb];
}
*/

uint8_t* RGBtoHSB(uint8_t color_red, uint8_t color_green, uint8_t color_blue)
{
	uint8_t hue, saturation, brightness;
	uint8_t hsbvals[3];
	uint8_t cmax = (color_red > color_green) ? color_red : color_green;
	if (color_blue > cmax) cmax = color_blue;
	uint8_t cmin = (color_red < color_green) ? color_red : color_green;
	if (color_blue < cmin) cmin = color_blue;
	brightness = cmax;
	if (cmax != 0) {
		saturation = ((cmax - cmin)*255 / (cmax));
	} else {
		saturation = 0;
	}
	if (saturation == 0) {
		hue = 0;
	} else {
		float redc   = ((cmax - color_red)*255) / ((cmax - cmin));
		float greenc = ((cmax - color_green)*255) / ((cmax - cmin));
		float bluec  = ((cmax - color_blue)*255) / ((cmax - cmin));
		if (color_red == cmax) {
			hue = bluec - greenc;
		} else if (color_green == cmax){
			hue = 2.0f + redc - bluec;
		} else {
			hue = 4.0f + greenc - redc;
		}
		hue = hue / 6.0f;
		if (hue < 0) {
			hue = hue + 1.0f;
		}
	}
	hsbvals[0] = hue;
	hsbvals[1] = saturation;
	hsbvals[2] = brightness;
	return hsbvals;
}

// http://blog.saikoled.com/post/43693602826/why-every-led-light-should-be-using-hsi
void hsi2rgb(float H, float S, float I, uint32_t* rgb){
    uint32_t r, g, b;
    H = fmod(H,360);          // cycle H around to 0-360 degrees
    H = (3.14159*H)/(float)180; // Convert to radians.
    S = S>0?(S<1?S:1):0;      // clamp S and I to interval [0,1]
    I = I>0?(I<1?I:1):0;
    I = pow(I, GAMMA);
    
    if(H < 2.09439) {
        r = MAX_PWM*((I/3)*(1+S*cos(H)/cos(1.047196667-H)));
        g = MAX_PWM*((I/3)*(1+S*(1-cos(H)/cos(1.047196667-H))));
        b = MAX_PWM*((I/3)*(1-S));
    } else if(H < 4.188787) {
        H = H - 2.09439;
        g = MAX_PWM*((I/3)*(1+S*cos(H)/cos(1.047196667-H)));
        b = MAX_PWM*((I/3)*(1+S*(1-cos(H)/cos(1.047196667-H))));
        r = MAX_PWM*((I/3)*(1-S));
    } else {
        H = H - 4.188787;
        b = MAX_PWM*((I/3)*(1+S*cos(H)/cos(1.047196667-H)));
        r = MAX_PWM*((I/3)*(1+S*(1-cos(H)/cos(1.047196667-H))));
        g = MAX_PWM*((I/3)*(1-S));
    }
    rgb[0]=r;
    rgb[1]=g;
    rgb[2]=b;
}

void bulb_setRGB(uint8_t bulb, uint8_t color_red, uint8_t color_green, uint8_t color_blue){
	volatile uint8_t bulbdebug = bulb;
	sequenceBuffer[*bufferIterator][bulbdebug][RED]   = color_red;
	sequenceBuffer[*bufferIterator][bulbdebug][GREEN] = color_green;
	sequenceBuffer[*bufferIterator][bulbdebug][BLUE]  = color_blue;
}