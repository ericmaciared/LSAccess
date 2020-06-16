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
  digitalWrite(DOOR, HIGH); //Initialize DOOR to HIGH
  open = 0;
  timer = TiGetTimer();
  TiResetTics(timer);
}

void DoOpenDoor(void){
  open = 1;
}

void motorTDoorPWM(void){
	static char state = 0;
	switch(state){
		case 0:
      if (open == 1) {
        TiResetTics(timer);
        digitalWrite(DOOR, LOW);
        state = 2;
      }
      else if (TiGetTics(timer) >= T_HIGH) {
        digitalWrite(DOOR, LOW);
        state = 1;
      }
			break;
    case 1:
      if (TiGetTics(timer) >= TIME_PWM) {
        TiResetTics(timer);
        digitalWrite(DOOR, HIGH);
        state = 0;
      }
      break;
    case 2:
      if (TiGetTics(timer) >= T_OPEN) {
        TiResetTics(timer);
        digitalWrite(DOOR, HIGH);
        open = 0;
        state = 0;
      }
      break;
	}
}
