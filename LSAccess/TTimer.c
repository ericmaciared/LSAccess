//---------------------------------------------------------
// @File: TTimer*
// @Purpose:
// @Author: eric.macia
// @Data: 03/05/2020
//---------------------------------------------------------

//------------------------ INCLUDES -----------------------

#include "TTimer.h"

#define TI_NUMTIMERS 25
#define TI_MAXTICS 30000
#define TI_FALSE 0
#define TI_TRUE 1

//------------------------ VARIABLES ----------------------
struct Timer {
	unsigned int h_initialTics;
	unsigned char b_busy;
} s_Timers[TI_NUMTIMERS];

static unsigned int h_Tics=0;  //Each time an interrupt occurs we increment
static char counter;

//------------------------ FUNCTIONS ----------------------

void initTimer(void) {
	//Pre: --
	//Post: Initializes the timer0 to interrupt each 1ms.
	//@16MHz (Tinst = 250nS), 1ms/Tinst = 4000tics 2^16-4000 = 0xF060

	TCCR1A = 0x00;	//Timer Control
	TCCR1B = 0x07;	//We select external clock source on rising edge
	TCCR1C = 0x00;

	TCNT1H = 0xF0;	//Timer Values
	TCNT1L = 0x60;

	TIMSK1 = 0x01;	//Timer Overflow Interrupt enable
	TIFR1 = 0x00;	//Interrupt flag

	for (counter = 0; counter < TI_NUMTIMERS; counter++) {
		s_Timers[counter].b_busy=TI_FALSE;
	}
}

void _TiRSITimer (void) {
//Timer Interrupt Service Routine
//@16MHz (Tinst = 250nS), 1ms/Tinst = 4000tics 2^16-4000 = 0xF060

	TCNT1H = 0xF0;	//Reset Timer
	TCNT1L = 0x60;	//Reset timer

	TIFR1 = 0x00; //Clear interrupt flag
	h_Tics++;	//Increase interrupt counter

	if (h_Tics>=TI_MAXTICS) {
	    //We reset them before they overflow (every 30s aprox)
	    for (counter = 0; counter < TI_NUMTIMERS; counter++){
	        if (s_Timers[counter].b_busy == TI_TRUE){
	            s_Timers[counter].h_initialTics -= h_Tics;
	        }
	    }
	    h_Tics=0;
	}

}
void TiResetTics(char Handle) {
//Pre: 0<Handle<MAXTIMERS.
//Post: Writes in the tics of the Handle timer the universal tics of the system.
	s_Timers[Handle].h_initialTics=h_Tics;
}

int TiGetTics(char Handle) {
//Pre: 0<Handle<MAXTIMERS.
//Post: Less than 32767 tics have passed since the last TiResetTics.
//Post: Returns the number of tics from the last TiResetTics for the Handle timer.

	volatile unsigned int actual;
	actual=h_Tics;
	return (actual-(s_Timers[Handle].h_initialTics));

}
char TiGetTimer(void) {
//Pre: There are free timers.
//Post: Returns the Handler of a timer and marks it as busy.
//Post:	If there are not free timers left, returns a -1.
	counter=0;
	while (s_Timers[counter].b_busy==TI_TRUE) {
		counter++;
		if (counter == TI_NUMTIMERS) return -1;
	}
	s_Timers[counter].b_busy=TI_TRUE;
	return (counter);
}

void TiFreeTimer (char Handle) {
//Pre: 0<Handle<MAXTIMERS.
//Post: The Handle timer is marked as free.
	s_Timers[Handle].b_busy=TI_FALSE;
}
