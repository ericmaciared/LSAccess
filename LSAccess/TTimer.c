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
    /*
    RCONbits.IPEN = 0; //No priorities
    INTCONbits.GIE_GIEH = 1;
    INTCONbits.PEIE_GIEL = 1;
    INTCONbits.TMR0IE = 1;
    INTCONbits.TMR0IF = 0;
    T0CON = 0x08; //16 bits without prescaler
    //@ 40MHz (Tinst = 100nS), we want 1ms/Tinst=10.000 tics 2*16-10.000=0xD8F0
    TMR0H = 0xD8;
    TMR0L = 0xF0;
    T0CONbits.TMR0ON = 1; //Start timer

    for (counter=0;counter<TI_NUMTIMERS;counter++) {
	s_Timers[counter].b_busy=TI_FALSE;
}*/
  //deactivate_priorities();


}

void _TiRSITimer (void) {
//Timer Interrupt Service Routine
    //@ 40MHz (Tinst = 100nS), we want 1ms/Tinst=10.000 tics 2*16-10.000=0xD8F0
    /*
    TMR0H = 0xD8;
    TMR0L = 0xF0;

    INTCONbits.TMR0IF = 0;
    h_Tics++;

    if (h_Tics>=TI_MAXTICS) {
        //We reset them before they overflow (every 30s aprox)
        for (counter=0;counter<TI_NUMTIMERS;counter++){
            if (s_Timers[counter].b_busy==TI_TRUE){
                s_Timers[counter].h_initialTics -= h_Tics;
            }
        }
        h_Tics=0;
    }*/

}
void TiResetTics(char Handle) {
//Pre: 0<Handle<MAXTIMERS.
//Post: Writes in the tics of the Handle timer the universal tics of the system.

    /*s_Timers[Handle].h_initialTics=h_Tics;*/
}

int TiGetTics(char Handle) {
//Pre: 0<Handle<MAXTIMERS.
//Post: Less than 32767 tics have passed since the last TiResetTics.
//Post: Returns the number of tics from the last TiResetTics for the Handle timer.
/*
    volatile unsigned int actual;
    actual=h_Tics;
    return (actual-(s_Timers[Handle].h_initialTics));*/

}
char TiGetTimer(void) {
//Pre: There are free timers.
//Post: Returns the Handler of a timer and marks it as busy.
//Post:	If there are not free timers left, returns a -1.
/*
    counter=0;
    while (s_Timers[counter].b_busy==TI_TRUE) {
        counter++;
	if (counter == TI_NUMTIMERS) return -1;
    }
    s_Timers[counter].b_busy=TI_TRUE;
    return (counter);
    */
}

void TiFreeTimer (char Handle) {
//Pre: 0<Handle<MAXTIMERS.
//Post: The Handle timer is marked as free.
/*
    s_Timers[Handle].b_busy=TI_FALSE;*/
}
