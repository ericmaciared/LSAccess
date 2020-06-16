//---------------------------------------------------------
// @File: TKeyboard*
// @Purpose:
// @Author: eric.macia
// @Data: 03/05/2020
//---------------------------------------------------------

//------------------------ INCLUDES -----------------------

#include "TKeyboard.h"

//------------------------ VARIABLES ----------------------

static char timer;

//------------------------ FUNCTIONS ----------------------

void initTDoor(void) {
  pinMode(COL0, INPUT);
  pinMode(COL1, INPUT);
  pinMode(COL2, INPUT);
  pinMode(ROW0, OUTPUT);
  pinMode(ROW1, OUTPUT);
  pinMode(ROW2, OUTPUT);
  pinMode(ROW3, OUTPUT);
  digitalWrite(ROW0, HIGH); //Initialize ROW0 to HIGH
  timer = TiGetTimer();
  TiResetTics(timer);
}

void motorTKeyboard(void){
	static char state = 0;
	switch(state){
		case 0:
			break;
    case 1:
      break;
    case 2:
      break;
	}
}

char KeyCharAvailable(void){

}

char KeyGetChar(void){

}
