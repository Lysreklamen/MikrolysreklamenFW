/*
 * pgmplayer.c
 *
 * Created: 14.09.2019 19:05:32
 *  Author: medlem
 */ 

#include "pgmplayer.h"
#include "ff/ff.h"
#include "ff/diskio.h"
#include <avr/io.h>
#include <util/delay.h>


uint8_t pgm_player(){
	FIL playlist;
	FIL sequence = 0;
	uint8_t res = 0;
	res = pgm_read_playlist(&playlist, &sequence);
	if (res) return res;
	
	res = pgm_read_sequence(&sequence);
	if (res) return res;
	
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
	f_read(&playlist, &buffer, 64, &br);
	
	/* replace newline character with file ending plus string termination so we can use the buffer as a file name */
	for(uint8_t i; i< 64; i++){
		if (buffer[i] == '\n'){
			buffer[i] = '.';
			buffer[i+1] = 'p';
			buffer[i+2] = 'g';
			buffer[i+3] = 'm';
			buffer[i+4] = '\0';
		}
	}
	/* Rewind read/write pointer the number of bytes read minus i */
	fr = f_lseek(&playlist, f_tell(fp) - (br-i));
	if (fr) return (int)fr;
	
	fr = f_open(sequence, buffer, FA_READ);
	if (fr) return (int)fr;
	
	//f_close(&fil);
	return 0;
}

uint8_t pgm_read_sequence(FIL* sequence){
	UINT br; // Number of bytes read
	volatile FRESULT fr;
	uint8_t buffer[512];
	uint8_t bytebuffer[3];
	uint8_t character;
	uint8_t dmxaddress = 0;
	
	f_lseek(&sequence, 4); // skip first line (2 characters + cr + lf)
	uint8_t i = 0;
	
	// Read one byte and put it in the frameBuffer buffer
	while (1) {
		f_read(&file, character, 1, &br);
		// TODO check br
		if (character == ' ') {
			break;
		} else {
			bytebuffer[i] = character;
			i++;
		}
	}
	
	// TODO look up in mapping table what values from the pgm file to use
	
	uint8_t dmxbyte = 0;
	// convert to byte
	for (uint8_t j=0; j<i; j++){
		dmxbyte += bytebuffer[j]*pow(10, i-j);
	}
	
	// Lookup where in the framebuffer it should go
	
	// put byte in framebuffer
	//uint8_t framebuffer[] = dmxbyte;
		
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