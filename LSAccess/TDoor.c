//---------------------------------------------------------
// @File: TDoorPWM*
// @Purpose:
// @Author: eric.macia
// @Data: 03/05/2020
//---------------------------------------------------------

//------------------------ INCLUDES -----------------------

#include "TDoor.h"

//------------------------ VARIABLES ----------------------

static char timer;
static char open;

//------------------------ FUNCTIONS ----------------------

void initTDoorPWM(void) {
  pinMode(DOOR, OUTPUT); //Set DOOR pin as OUTPUT
  digitalWrite(DOOR, LOW); //Initialize DOOR to LOW
  open = 0;
  timer = TiGetTimer();
  TiResetTics(timer);
}


void DoOpenDoor(void){
//Pre: --
//Post: Opens door for 3 seconds.
  open = 1;
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
