/*
 * apa102.h
 *
 * Created: 2019-01-17 20:37:27
 *  Author: medlem
 */ 


#ifndef APA102_H_
#define APA102_H_

void setupapa( void );
void bitbangbonanza( uint8_t val);
void startframe( void );
void endframe( uint8_t count);
void pushframe(uint8_t framebuffer[][3], uint8_t brightness);

#endif /* APA102_H_ */