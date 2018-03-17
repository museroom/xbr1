
/*
 * bitbang_dmxout.S
 *
 * Created: 2/8/2017 14:03:57
 *  Author: muser_000
 */ 


.global bitbang_dmxout

bitbang_dmxout:
starbit:
	ldi r19, 0b00000001			// set start bit 0
	out 5, r19					// output star bit 0
	ldi r20, 10					// delay 4us amount
	call delay4us				// call delay4us
	nop
	nop
	nop
loadstream:
	mov r30,r24					// read parameter address
	mov r31,r25										
	mov r24,r22				    // 16bit counter for total number of bytes
	mov r25,r23				    // ... next nibble
loop:
	ldi r18, 7					// set loop count for 8bit shifting
	ldd r16, Z+0				// load byte
loadbit:
	mov r19, r16				// copy 
	andi r19, 0b10000000		// mask out MSB 
	lsr r19                     // move to correct pin for rs485 output
	lsr r19                     // ... continue
	ori r19, 0b0000001          // PinDE HIGH
	out 5, r19                  // output PORTB 
	rol r16						// shift the byte buf one bit left
	ldi r20, 11					// amount of loop to delay
	call delay4us		        // call delay4us route
	nop						
	nop
	dec r18						// dec 8bit counter
	brne loadbit			    // less than 8 bit return loadbit:

	mov r19, r16				// load LSB of 8bit
	andi r19, 0b10000000		// mask out MSB 
	lsr r19                     // move to correct pin for rs485 output
	lsr r19                     // ... continue
	nop
	ori r19, 0b0000001          // PinDE HIGH
	out 5, r19                  // output PORTB 
	rol r16						// shift the byte buf one bit left
	ldi r20, 10					// amount of loop to delay
	call delay4us		        // call delay4us route

	adiw r30, 1					// increase Z pointer
	sbiw r24, 1					// decrease counter
	brne loop
	
stopbit:
	rjmp .+0
	rjmp .+0
	rjmp .+0
	rjmp .+0
	ldi r19, 0b00100001			// set stop 2x stop bit 
	out 5, r19					// output stop 2x stop bit
	ldi r20, 80					// delay 4us amount
	call delay4us				// call delay4us

	clr r25
	ret

delay4us:
	nop
	dec r20
	brne delay4us
	ret

