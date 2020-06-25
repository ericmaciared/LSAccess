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
static char numPress;

//------------------------ FUNCTIONS ----------------------

void initTInput(void) {
  timer = TiGetTimer();
  key = -1;
  previousKey = -1;
  numPress = 0;
  state = 0;
}

void motorTInput(void){
  switch (state){
    case 0:
      if (KeyCharAvailable() == 1) {
        key = KeyGetChar();
        state = 1;
      }
      else if (SioCharAvailable() >= 1 && KeyCharAvailable() != 1) state = 6;
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
      else if (key == 10 || key == 12) {
        TiResetTics(timer);
        state = 2;
      }
      else if (key != 10 && key != 12 && AuState() != IDLE) {
        previousKey = key;
        TiResetTics(timer);
        AuAddChar(InItoa(key));
        state = 3;
      }
      break;
    case 2:
      if (TiGetTics(timer) >= T_RESET && key == 12) {
        AuReset();
        state = 0;
      }
      else if (TiGetTics(timer) >=T_IDLE && key == 10) {
        AuIdle();
        state = 0;
      }
      else if (KeyCharAvailable() != 1 && TiGetTics(timer) < T_RESET) state = 0;
      break;
    case 3:
      if (TiGetTics(timer) >= T_PRESS) state = 0;
      else if (TiGetTics(timer) < T_PRESS && KeyCharAvailable() == 0) state = 4;
      break;
    case 4:
      if (TiGetTics(timer) >= T_PRESS) state = 0;
      else if (TiGetTics(timer) < T_PRESS && KeyCharAvailable() == 1) {
        key = KeyGetChar();
        state = 5;
      }
      break;
    case 5:
      if (previousKey == key) {
        AuSwitchChar(InItoa(key));
        TiResetTics(timer);
        state = 3;
      }
      else {
        AuAddChar(InItoa(key));
        TiResetTics(timer);
        previousKey = key;
        state = 3;
      }
      break;
    case 6:
      if (key == 27) AuIdle();
      else if (AuState() != IDLE) AuAddChar(key);
      else if (key == '1') AuRegister();
      else if (key == '2') AuDelete();
      else if (key == '3') AuChangeTime();
      else if (key == '4') AuStatistics();
      state = 0;
      break;
  }
}

unsigned char InItoa(char key){

}
