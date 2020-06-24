//---------------------------------------------------------
// @File: TInput*
// @Purpose:
// @Author: eric.macia
// @Data: 03/05/2020
//---------------------------------------------------------

//------------------------ INCLUDES -----------------------

#include "TInput.h"

//------------------------ VARIABLES ----------------------

static char timer;
static char key;
static char previousKey;
static char state;

//------------------------ FUNCTIONS ----------------------

void initTInput(void) {
  timer = TiGetTimer();
  key = -1;
  previousKey = -1;
  state = 0;
}

void motorTInput(void){
  switch (state){
    case 0:
      if (KeyCharAvailable() == 1) {
        key = KeyGetChar();
        state = 1;
      }
      else if (SioCharAvailable() >= 1 && KeyCharAvailable() != 1) {
        state = 5;
      }
      break;
    case 1:
      if (key == 1 && AuState() == IDLE) {
        AuLogin();
        state = 0;
      }
      else if (key == 2 && AuState() == IDLE) {
        AuRegister();
        state = 0;
      }
      else if (key == 10) {
        AuIdle();
        state = 0;
      }
      else if (key == 12) {
        TiResetTics(timer);
        state = 2;
      }
      else if (key != 10 && key != 12 && AuState() == 0) {
        previousKey = key;
        TiResetTics(timer);
        AuAddChar(InItoa(key));
        state = 3;
      }
      break;
    case 2:
      if (TiGetTics(timer) >= T_RESET ) {
        AuReset();
        state = 0;
      }
      else if (KeyCharAvailable() != 1 && TiGetTics(timer) < T_RESET){
        state = 0;
      }
      break;
    case 3:
      if (TiGetTics(timer) >= T_PRESS) {
        previousKey = -1;
        state = 0;
      }
      else if (TiGetTics(timer) < T_PRESS && KeyCharAvailable() == 1) {
        //TODO: check that KeyCharAvailable gets to 0

      }
      break;
  }
}

unsigned char InItoa(char key){

}
