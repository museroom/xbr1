/*
 * xbr1_bitbanger.h
 *
 * Created: 6/2/2017 5:45:46
 *  Author: mPlayer
 */ 


#ifndef XBR1_BITBANGER_H_
#define XBR1_BITBANGER_H_

#define BAUD_RATE		250000
#define BUF_SIZE		1024
#define PIN1R			11
#define PIN1RE			10
#define PIN1DE			9
#define PIN1T			8
#define PIN1_TRIGGER	2


extern "C" {
	void bitbang_out( char *, uint16_t );
	void bitbang_dmxout( char *, uint16_t );
	void bitbang_dump();
};


#endif /* XBR1-BITBANGER_H_ */