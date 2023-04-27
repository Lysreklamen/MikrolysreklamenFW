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


uint8_t pgm_player( uint8_framebuffer_t* );
uint8_t pgm_read_playlist( FIL* playlist, FIL* sequence );
uint8_t pgm_read_preamble(FIL* file);
uint8_t pgm_read_sequence_frame( FIL* sequence, uint8_framebuffer_t* );


#endif /* PGMPLAYER_H_ */