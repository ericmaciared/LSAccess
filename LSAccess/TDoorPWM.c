//---------------------------------------------------------
// @File: TDoorPWM*
// @Purpose:
// @Author: eric.macia
// @Data: 03/05/2020
//---------------------------------------------------------

//------------------------ INCLUDES -----------------------

#include "TDoorPWM.h"

#define TIME_PWM 20

//------------------------ VARIABLES ----------------------

static char tHigh;
static char timer;
//------------------------ FUNCTIONS ----------------------

void initTPWM(void) {
	/*TRISAbits.TRISA3 = 0;
	tHigh = 0;
	LATAbits.LATA3 = 0;
	timer = TiGetTimer();
	TiResetTics(timer);*/
}

void setTimeHigh(char value){
//Pre: 0<= value <= TIMEPWM
//Post: it sets a value to the DC of the PWM
//proportional to "value".
	tHigh = 2*value;
}

void motorPWM(void){
	/*static char state = 0;
	switch(state){
		case 0:
			if (TiGetTics(timer) >= tHigh){
				LATAbits.LATA3 = 0;
				state = 1;
			}
			break;
		case 1:
			if (TiGetTics(timer) >= TIME_PWM){
				TiResetTics(timer);
				LATAbits.LATA3 = 1;
				state = 0;
			}
			break;
	}*/
}
