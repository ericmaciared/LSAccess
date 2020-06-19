//---------------------------------------------------------
// @File: TTimer*
// @Purpose:
// @Author: eric.macia
// @Data: 03/05/2020
//---------------------------------------------------------

//------------------------ INCLUDES -----------------------

#include "TTimer.h"

//------------------------ VARIABLES ----------------------
struct Timer {
	unsigned int initialTics;
	unsigned char busy;
} timers[NUMTIMERS];

static unsigned int tics=0;  //Each time an interrupt occurs we increment
static unsigned char counter;

//------------------------ FUNCTIONS ----------------------

void initTimer(void) {
	/*TCCR1A = 0x00;	//Timer Control
	TCCR1B = 0x07;	//We select external clock source on rising edge
	TCCR1C = 0x00;

	TCNT1H = 0xFe;	//Timer Values
	TCNT1L = 0x70;

	TIMSK1 = 0x01;	//Timer Overflow Interrupt enable
	TIFR1 = 0x00;	  //Interrupt flag*/

	for (counter = 0; counter < NUMTIMERS; counter++) {
		timers[counter].busy = FALSE;
	}
}

void TiResetTics(char Handle) {
	timers[Handle].initialTics = millis();
}

int TiGetTics(char Handle) {
	return (millis() - (timers[Handle].initialTics));
}

char TiGetTimer(void) {
	counter=0;
	while (timers[counter].busy==TRUE) {
		counter++;
		if (counter == NUMTIMERS) return -1;
	}
	timers[counter].busy=TRUE;
	return (counter);
}

void TiFreeTimer (char Handle) {
  timers[Handle].busy = FALSE;
}
