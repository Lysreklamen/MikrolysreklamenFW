/*
 * pgmplayer.h
 *
 * Created: 14.09.2019 19:05:19
 *  Author: medlem
 */ 


#ifndef PGMPLAYER_H_
#define PGMPLAYER_H_

#include "ff/ff.h"
#include "ff/diskio.h"
#include <avr/io.h>

#define PGM_LINE_READ_SUCCESSFULLY 4
#define PGM_FILE_ERROR 2

void set_error_color(uint8_t fr);
uint8_t pgm_player( void );
uint8_t pgm_read_playlist( FIL* playlist, FIL* sequence );
uint8_t pgm_read_preamble(FIL* file);
uint8_t pgm_read_sequence_frame( FIL* sequence);


#endif /* PGMPLAYER_H_ */