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
	//Pre: --
	//Post: Initializes the timer0 to interrupt each 1ms.
	//@16MHz (Tinst = 250nS), 0.1ms/Tinst = 400tics 2^16-400 = 0xFE70

	TCCR1A = 0x00;	//Timer Control
	TCCR1B = 0x07;	//We select external clock source on rising edge
	TCCR1C = 0x00;

	TCNT1H = 0xFe;	//Timer Values
	TCNT1L = 0x70;

	TIMSK1 = 0x01;	//Timer Overflow Interrupt enable
	TIFR1 = 0x00;	  //Interrupt flag

	for (counter = 0; counter < NUMTIMERS; counter++) {
		timers[counter].busy = FALSE;
	}
}

void __attribute__((interrupt, no_auto_psv)) _TiRSITimer(void) {
//Timer Interrupt Service Routine
//@16MHz (Tinst = 250nS), 0.1ms/Tinst = 400tics 2^16-400 = 0xFE70

	TCNT1H = 0xFE;	//Reset Timer
	TCNT1L = 0x70;	//Reset timer

	TIFR1 = 0x00; //Clear interrupt flag
	tics++;	//Increase interrupt counter

	if (tics>=MAXTICS) {
	    //We reset them before they overflow (every 30s aprox)
	    for (counter = 0; counter < NUMTIMERS; counter++){
	        if (timers[counter].busy == TRUE){
	            timers[counter].initialTics -= tics;
	        }
	    }
	    tics=0;
	}

}

void TiResetTics(char Handle) {
//Pre: 0<Handle<MAXTIMERS.
//Post: Writes in the tics of the Handle timer the universal tics of the system.
	timers[Handle].initialTics=tics;
}

int TiGetTics(char Handle) {
//Pre: 0<Handle<MAXTIMERS.
//Post: Less than 32767 tics have passed since the last TiResetTics.
//Post: Returns the number of tics from the last TiResetTics for the Handle timer.

	volatile unsigned int actual;
	actual=tics;
	return (actual-(timers[Handle].initialTics));

}

char TiGetTimer(void) {
//Pre: There are free timers.
//Post: Returns the Handler of a timer and marks it as busy.
//Post:	If there are not free timers left, returns a -1.
	counter=0;
	while (timers[counter].busy==TRUE) {
		counter++;
		if (counter == NUMTIMERS) return -1;
	}
	timers[counter].busy=TRUE;
	return (counter);
}

void TiFreeTimer (char Handle) {
//Pre: 0<Handle<MAXTIMERS.
//Post: The Handle timer is marked as free.
	timers[Handle].busy=FALSE;
}
