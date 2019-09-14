/*
 * pgmplayer.c
 *
 * Created: 14.09.2019 19:05:32
 *  Author: medlem
 */ 

#include "pgmplayer.h"


// TODO, finish this
uint8_t pgm_read_playlist( char* playlist ){
	FIL fil;
	UINT br; // Number of bytes read
	volatile FRESULT fr;
	uint8_t length; //Playlist length
	
	uint8_t buffer[64];
	
	fr = f_open(&fil, "playlist.txt", FA_READ);
	if (fr) return 0;
	
	f_read(&fil, &buffer, 64, &br);
	uint8_t character;
	while (character != '\n'){
		// TODO
	}
	
	f_close(&fil);
	return length;
}

uint8_t pgm_read_sequence(uint8_t* sequence_name){
	FIL file;
	UINT br; // Number of bytes read
	volatile FRESULT fr;
	uint8_t buffer[512];
	uint8_t bytebuffer[3];
	uint8_t character;
	uint8_t dmxaddress = 0;
	
	fr = f_open(&file, &sequence_name, FA_READ);
	f_lseek(4); // skip first line (2 characters + cr + lf)
	uint8_t i = 0;
	
	// Read one byte and put it in the framebuffer buffer
	while () {
		f_read(&file, character, 1, &br)
		// TODO check br
		if (character == ' ') {
			break;
		} else {
			bytebuffer[i] = character;
			i++;
		}
	}
	uint8_t dmxbyte = 0;
	// convert to byte
	for (uint8_t j=0; j<i; j++){
		dmxbyte += bytebuffer[j]*pow(10, i-j);
	}
	
	// Lookup where in the framebuffer it should go
	
	// put byte in framebuffer
	framebuffer[] = dmxbyte;
		
		/*
		if (character == '\r')
		{
			f_read(&file, character, 1, &br)
			if (character == '\n')
			{
				// Line is read
			}
		}
		*/
	}
}


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