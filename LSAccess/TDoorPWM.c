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
static char door;

//------------------------ FUNCTIONS ----------------------

void initTDoorPWM(void) {
  pinMode(LED, 0); //Set LED pin as OUTPUT
  digitalWrite(LED, 0); //Initialize LED to LOW
  door = 0;
  tHigh = 0;
  timer = TiGetTimer();
  TiResetTics(timer);
}

void DpSetTimeHigh(char value){
//Pre: 0<= value <= TIMEPWM
//Post: it sets a value to the DC of the PWM
//proportional to "value".
	tHigh = 2*value;
}

void motorTDoorPWM(void){
	static char state = 0;
	switch(state){
		case 0:
			if (tHigh != 0) state = 1;
			break;
		case 1:
			if (TiGetTics(timer) >= tHigh){
				door = 0;
				state = 2;
			}
			break;
    case 2:
      if (TiGetTics(timer) >= TIME_PWM) {
        TiResetTics(timer);
        door= 1;
      }
      break;
	}
}
