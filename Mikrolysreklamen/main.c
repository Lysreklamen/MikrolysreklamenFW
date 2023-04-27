/*
 * Mikrolysreklamen17.c
 *
 * Created: 2019-01-17 18:18:21
 * Author : medlem
 */ 

#include "Mikrolysreklamen.h"
#include "apa102.h"
#include "api.h"
#include "effects.h"
#include "sequences.h"
#include "pgmplayer.h"
#include "ff/ff.h"
#include "ff/diskio.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define APA_PORT PORTD
#define CLK_PIN 7
#define DATA_PIN 5

FATFS FatFs;

void setup( void );
uint8_t sdcardtest( void );
void setup_rtc( void );

//volatile uint8_sequencebuffer_t sequenceBufferA;
//volatile uint8_sequencebuffer_t sequenceBufferB;

volatile uint8_t bufferIteratorA = 0;
volatile uint8_t bufferIteratorB = 0;

//volatile uint8_sequencebuffer_t sequenceBuffer;
volatile uint8_t *bufferIterator;

volatile uint8_t Timer1;
volatile uint8_t Timer2;  /* 100Hz decrement timer */

volatile uint8_framebuffer_t frameBuffer;

int main(void)
{
	setup();
	setupapa();
	setup_rtc();
	sei();
	//sdcardtest();
	write_fw_version();
	
	/* Register work area to the default drive */
	f_mount(&FatFs, "", 0);
	
	/*
	for (uint8_t i=0;i<NUM_LEDS;i++){
		for (uint8_t j=0; j<BULBCHANNELS;j++)
		{
			frameBuffer[i][j] = 0;
		}
	}
	*/
	pushframe(frameBuffer, 1);
	while (1) {
		pgm_player(&frameBuffer);
		//sequence_letterDemo();
		//sequence_digitDemo();
		//sequence_AuroraDemo();
		//sequence_Glitter();
		//sequence_rgbFadeDemo();
	}
}

void setup ( void ) {
	// Select internal 32MHz Oscillator as clock source
	//OSC.CTRL = 0b001;
	NVM.CTRLB |= (1 << 3); // Set EEPROM to memory mapped access
	
	
	srand(1337 % 255);
	
	bufferIterator = &bufferIteratorA;
	
	// Set Memory Card SPI pins as output
	PORTC.DIR = (1 << 4) | (1 << 5) | (1 << 7);
}

uint8_t sdcardtest(){
	FIL fil;
	char line[100];
	volatile FRESULT fr;
	
	/* Register work area to the default drive */
	f_mount(&FatFs, "", 0);

	/* Open a text file */
	fr = f_open(&fil, "message.txt", FA_READ | FA_WRITE | FA_OPEN_ALWAYS);
	if (fr) return (int)fr;
	
	//f_putc("a", &fr);
	
	line[0] = 'a';
	UINT bw = 0;
	
	f_write(&fil, line, 1, &bw);

	/* Close the file */
	f_close(&fil);

	return 0;
}

/* Writes the FW version (stored in define) to a file on the SD card for debugging (without a debugger) purposes */
void write_fw_version(void){
	FIL fil;
	volatile FRESULT fr;
	UINT bw = 0;
	f_mount(&FatFs, "", 0);
	fr = f_open(&fil, "fw_version.txt", FA_READ | FA_WRITE | FA_OPEN_ALWAYS);
	if (fr) return (int)fr;
	char line[] = FW_VERSION;
	f_write(&fil, line, FW_VERSION_LEN, &bw);
	f_close(&fil);
}

void setup_rtc( void ){
	OSC_CTRL |= OSC_RC32KEN_bm; // Enable internal 32k oscillator
	while (!(OSC_STATUS & OSC_RC32KRDY_bm)); // Wait until stable
	CLK.RTCCTRL = CLK_RTCSRC_RCOSC_gc | CLK_RTCEN_bm; // Enable RTC with 1.024kHz from 32.768kHz internal oscillator
	
	RTC_CTRL = RTC_PRESCALER_DIV1_gc; // Enable RTC
	RTC_INTCTRL = RTC_COMPINTLVL0_bm; // Set interrupt
	RTC_COMP = 10;
	
	PMIC_CTRL |= PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm; // Enable global interrupts
}

ISR(RTC_COMP_vect){
	RTC_CNT = 0; // Clear the RTC counter value
	if (Timer1 > 0)
	{
		Timer1--;
	}
	if (Timer2 > 0)
	{
		Timer2--;
	}
}