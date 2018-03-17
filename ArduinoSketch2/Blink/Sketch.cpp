// XB-R1 bitbanger

#include <Arduino.h>
#include "xbr1_bitbanger.h"

#define BUF_HI 1024

// Arduino Sketch friendly header declare
uint8_t HexChar (char);
uint16_t StrToHex( String, uint8_t * );
void dmxByteStream ( uint8_t *, uint8_t *, uint16_t );

// Global Varibles
char tmpC[100];
String tmp = "AAFF0100AAAA1234567800FF";
uint8_t tmpC2[25];
uint8_t bufStream[BUF_SIZE];
uint8_t bufHi[BUF_HI];

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin( BAUD_RATE );

  // Setup Pins
  pinMode( PIN1R, INPUT );
  pinMode( PIN1RE, OUTPUT );
  pinMode( PIN1DE, OUTPUT );
  pinMode( PIN1T, OUTPUT );

  pinMode( PIN1_TRIGGER, OUTPUT);

  // Setup RS485 IC pins
  digitalWrite( PIN1RE, LOW);
  digitalWrite( PIN1DE, LOW);
  digitalWrite( PIN1T, LOW);
  digitalWrite( PIN1_TRIGGER, LOW);

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  }


// the loop function runs over and over again forever
void loop() {                

	String menu_command; 	
	uint8_t menu_item;


	for( int i =0; i < BUF_HI; i++) {
		bufHi[i] = 256 - (uint8_t) i;
	}


#ifdef DEBUG
	uint16_t tmpLength = StrToHex( tmp, tmpC2 );
	for( int i=0; i<BUF_SIZE; i++ ) {
		bufStream[i] = 0;
	}
	bitbang_out( (char*)tmpC2, 25 );
	bitbang_dmxout( (char*)tmpC2, 3);
	
#endif

	Serial.println( "XB-R1 BitBangger v0.1");
#ifdef DEBUG 
	if( digitalRead( 3 ) == HIGH ) {
#else
	if( Serial.available()) {
#endif
		menu_item = Serial.read();
		Serial.println( "menu_item:" + String( menu_item, HEX ));
		switch( menu_item - 0x30 ) {
			case 1: // bitbang output
				Serial.println( "BitBang Out" );
				if( Serial.available() ) {
					menu_command = Serial.readString();
					//bitbang_out( menu_command, menu_command.length() );
				}
				break;
			case 2: // dump rs485 4us band
				Serial.println( "Dump RS485 4us Baud");
				break;
			case 3: // setup PINS
				Serial.println( "Setup" );
				Serial.end();
				setup();
				break;
			case 4: // Blink LED
				Serial.println( "Blink LED reset PIN1DE");
				digitalWrite( LED_BUILTIN, HIGH );
				delay( 250);
				digitalWrite( LED_BUILTIN, LOW);
				delay(250);
				digitalWrite( PIN1DE, LOW );
				break;
			default:
				break;			
		}
	}
} 
 

uint8_t HexChar (char c)
{
	if ('0' <= c && c <= '9') return (uint8_t)(c - '0');
	if ('A' <= c && c <= 'F') return (uint8_t)(c - 'A' + 10);
	if ('a' <= c && c <= 'f') return (uint8_t)(c - 'a' + 10);
	return (uint8_t)(-1);
}

uint16_t StrToHex( String hexStr, uint8_t *hexArray ) {
	for( int i =0 ; i< hexStr.length(); i+=2) {
		uint8_t hexHi = HexChar( hexStr[i] );
		uint8_t hexLo = HexChar( hexStr[i+1] );
		hexArray[i/2] = hexHi*16+hexLo;
	}
	return hexStr.length() / 2;
}

// Generate dmx frame into binary stream
void dmxByteStream ( uint8_t *hexStream, uint8_t *byteStream, uint16_t numOfFrame) {
	uint8_t *bitPtr = byteStream;
	
	for( uint16_t i = 0; i < numOfFrame; i++ ) {
		
	}
}