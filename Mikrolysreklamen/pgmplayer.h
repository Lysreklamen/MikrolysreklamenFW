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


uint8_t pgm_read_playlist( FIL* playlist, FIL* sequence );


#endif /* PGMPLAYER_H_ */