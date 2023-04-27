/*
 * pgmplayer.c
 *
 * Created: 14.09.2019 19:05:32
 *  Author: medlem
 */ 

#include "Mikrolysreklamen.h"
#include "pgmplayer.h"
#include "ff/ff.h"
#include "ff/diskio.h"
#include <avr/io.h>
#include <util/delay.h>

uint16_t bulbMapping[NUM_LEDS][3] = {{0, 1, 2},
{3, 4, 5},
{6, 7, 8},
{203, 303, 403},
{204, 304, 404},
{205, 305, 405},
{206, 306, 406},
{207, 307, 407},
{208, 308, 408},
{209, 309, 409},
{210, 310, 410},
{211, 311, 411},
{215, 315, 415},
{216, 316, 416},
{217, 317, 417},
{218, 318, 418},
{219, 319, 419},
{220, 320, 420},
{221, 321, 421},
{225, 325, 425},
{226, 326, 426},
{230, 330, 430},
{231, 331, 431},
{232, 332, 432},
{233, 333, 433},
{234, 334, 434},
{235, 335, 435},
{236, 336, 436},
{237, 337, 437},
{238, 338, 438},
{239, 339, 439},
{240, 340, 440},
{241, 341, 441},
{242, 342, 442},
{243, 343, 443},
{245, 345, 445},
{246, 346, 446},
{247, 347, 447},
{248, 348, 448},
{249, 349, 449},
{250, 350, 450},
{251, 351, 451},
{252, 352, 452},
{253, 353, 453},
{254, 354, 454},
{255, 355, 455},
{256, 356, 456},
{260, 360, 460},
{261, 361, 461},
{262, 362, 462},
{263, 363, 463},
{264, 364, 464},
{265, 365, 465},
{266, 366, 466},
{267, 367, 467},
{268, 368, 468},
{269, 369, 469},
{270, 370, 470},
{271, 371, 471},
{272, 372, 472},
{273, 373, 473},
{275, 375, 475},
{276, 376, 476},
{277, 377, 477},
{278, 378, 478},
{279, 379, 479},
{280, 380, 480},
{281, 381, 481},
{282, 382, 482},
{283, 383, 483},
{284, 384, 484},
{285, 385, 485},
{286, 386, 486},
{287, 387, 487},
{288, 388, 488},
{289, 389, 489},
{290, 390, 490},
{291, 391, 491},
{292, 392, 492},
{293, 393, 493},
{294, 394, 494},
{295, 395, 495}
};

uint8_t pgm_player(uint8_framebuffer_t* frameBuffer){
	FIL playlist;
	FIL sequence;
	volatile FRESULT fr;
	uint8_t res = 0;
	fr = f_open(&playlist, "playlist.txt", FA_READ);
	if (fr) return (int)fr;
	res = pgm_read_playlist(&playlist, &sequence);
	if (res) return res;
	res = pgm_read_preamble(&sequence);
	if (res) return res;
	
	while( pgm_read_sequence_frame(&sequence, frameBuffer) == PGM_LINE_READ_SUCCESSFULLY){
		pushframe(frameBuffer, 1);
	}
	
	
	
	
	return 0;
}


// Reads the playlist, gets the name of the next sequence, translates to file pointer, then sets the read cursor in the playlist to the start of the next sequence.
uint8_t pgm_read_playlist( FIL* playlist, FIL* sequence ){
	UINT br; // Number of bytes read
	volatile FRESULT fr;
	
	// Check if file is actually open, close it if open
	if (sequence){
		f_close(sequence);
	}
	
	uint8_t buffer[64]; // Does not support a sequence name longer than 64 characters
	
	/* read as much of the playlist file that can fit in the buffer */
	fr = f_read(playlist, &buffer, 64, &br);
	if (fr) return (int)fr;
	
	/* replace newline character with file ending plus string termination so we can use the buffer as a file name */
	uint8_t i = 0;
	while (i < 64){
		if (buffer[i] == '\n'){
			buffer[i] = '.';
			buffer[i+1] = 'p';
			buffer[i+2] = 'g';
			buffer[i+3] = 'm';
			buffer[i+4] = '\0';
			break;
		}
		i++;
	}
	/* Rewind read/write pointer the number of bytes read minus i */
	//fr = f_lseek(&playlist, f_tell(&playlist) - (br-i));
	if (fr) return (int)fr;
	
	fr = f_open(sequence, buffer, FA_READ);
	if (fr) return (int)fr;
	
	//f_close(&fil);
	return 0;
}

uint8_t pgm_read_preamble(FIL* file){
	// Skip the preamble of the pgm file
	// TODO read and parse the preamble
	uint8_t lines = 0;
	uint8_t character;
	volatile FRESULT fr;
	UINT br; // Number of bytes read
	
	while (lines<3) {
		fr = f_read(file, &character, 1, &br);
		if (fr) return (int)fr;
		if (character == '\n') {
			lines++;
		}
	}
	return 0;
}

// Takes a sequence file FIL, and a pointer to the frame buffer as input
uint8_t pgm_read_sequence_frame(FIL* file, uint8_framebuffer_t* frameBuffer){
	UINT br; // Number of bytes read
	volatile FRESULT fr;
	uint8_t buffer[512];
	uint8_t bytebuffer[3];
	uint8_t character;
	uint8_t dmxaddress = 0;
	uint16_t pgmbyteno = 0; // byte counter per line
	uint16_t nextvalidpgmbyte = bulbMapping[0][0];
	
	volatile uint8_t foo = 0;
	
	uint8_t linefeed = 0;
	uint8_t i = 0;
	uint8_t dmxbyte = 0;
	uint8_t bulbNo = 0;
	uint8_t bulbChannelNo = 0;
	//fr = f_read(file, &buffer, 400, &br);
	//if (fr) return PGM_FILE_ERROR;
	while (!linefeed) {
		fr = f_read(file, &character, 1, &br);
		if (fr) return PGM_FILE_ERROR;
		if (character == '\n') {
			linefeed = 1;
			return PGM_LINE_READ_SUCCESSFULLY;
		} else if (character == ' ') { // Then we have read the ascii for one byte
			pgmbyteno++;
			if (pgmbyteno > 77){
				foo++;
			}
			if (pgmbyteno >= nextvalidpgmbyte) { // Skip the unused bytes in the pgm file
				dmxbyte = 0;
				// convert to byte
				for (uint8_t j=0; j<i; j++){
					dmxbyte += bytebuffer[j] * pow(10, i-j);
				}
				*frameBuffer[bulbNo][bulbChannelNo] = dmxbyte;
			
				if (bulbChannelNo < BULBCHANNELS) {
					bulbChannelNo++;
				} else{
					bulbChannelNo = 0;
					bulbNo++;
				}
				nextvalidpgmbyte = bulbMapping[bulbNo][bulbChannelNo];
				i = 0;
			}
		} else {
			bytebuffer[i] = character - '0';
			i++;
		}
	}
	return foo;
}

/*
// Reads the second line of the pgm file
FRESULT read_line_2(FIL* fp, void* buff){
	volatile FRESULT fr; // File action result
	UINT br; // Number of bytes read
	uint8_t character = 0;
	uint8_t iterator = 0;
	while(character != '\r'){
		fr = f_read(&fp, character, 1, &br);
		buff[iterator] = character;
	}
	fr = f_read(&fp, character, 1, &br);
	if (character == '\n'){
		return 0;
	} else {
		return FR_INT_ERR;
	}
}
*/