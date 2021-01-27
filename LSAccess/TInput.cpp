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

void motorTInput(void) {
  switch (state) {
    case 0:
      numPress = 0;
      if (KeyCharAvailable() == 1) {
        numPress++;
        key = KeyGetChar();
        state = 1;
      }
      else if (SioCharAvailable() >= 1 && KeyCharAvailable() != 1) {
        key = SioGetChar();
        state = 6;
      }
      break;
    case 1:
      if (key == 1 && AuState() == IDLE_PROCESS && KeyCharAvailable() == 0) {
        AuLogin();
        key = -1;
        state = 0;
      }
      else if (key == 2 && AuState() == IDLE_PROCESS && KeyCharAvailable() == 0) {
        AuRegisterK();
        key = -1;
        state = 0;
      }
      else if (key == 10 || key == 12) {
        TiResetTics(timer);
        state = 2;
      }
      else if (key != 10 && key != 12 && AuState() != IDLE_PROCESS) {
        previousKey = key;
        TiResetTics(timer);
        AuAddChar(InItoa(key));
        state = 3;
      }
      else state = 0;
      break;
    case 2:
      if (TiGetTics(timer) >= T_RESET && key == 12) {
        AuReset();
        key = -1;
        state = 0;
      }
      else if (TiGetTics(timer) >= T_IDLE && key == 10) {
        AuIdle();
        key = -1;
        state = 0;
      }
      else if (KeyCharAvailable() != 1 && TiGetTics(timer) < T_RESET) state = 0;
      break;
    case 3:
      if (TiGetTics(timer) >= T_PRESS){
        previousKey = -1;
        AuFinishChar();
        state = 0;
      }
      else if (TiGetTics(timer) < T_PRESS && KeyCharAvailable() == 0) state = 4;
      break;
    case 4:
      if (TiGetTics(timer) >= T_PRESS){
        previousKey = -1;
        AuFinishChar();
        state = 0;
      }
      else if (TiGetTics(timer) < T_PRESS && KeyCharAvailable() == 1) {
        numPress++;
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
      else if (AuState() != IDLE_PROCESS && key != 10 && key != 13) AuAddChar(key);
      else if (key == '\n' || key == '\r' || key == 10 || key == 13) AuFinishInput();
      else if (key == '1' && AuState() == IDLE_PROCESS) AuRegisterC();
      else if (key == '2' && AuState() == IDLE_PROCESS) AuDelete();
      else if (key == '3' && AuState() == IDLE_PROCESS) AuChangeTime();
      else if (key == '4' && AuState() == IDLE_PROCESS) AuStatistics();
      key = -1;
      state = 0;
      break;
  }
}

unsigned char InItoa(char key) {
  unsigned char _key = 0;

  if (key == 11) _key = '0';
  else if (key == 1) _key = '1';
  else if (key == 7) {
    if (numPress % 5 == 1) _key = '7';
    else if (numPress % 5 == 0) _key = 'S';
    else _key = 'P' + numPress % 5 - 2;
  }
  else if (key == 9) {
    if (numPress % 5 == 1) _key = '9';
    else if (numPress % 5 == 0) _key = 'Z';
    else _key = 'W' + numPress % 5 - 2;
  }
  else if (key == 8) {
    if (numPress % 4 == 1) _key = '8';
    else if (numPress % 4 == 0) _key = 'V';
    else _key = 'T' + numPress % 4 - 2;
  }
  else {
    if (numPress % 4 == 1) _key = '0' + key;
    else if (numPress % 4 == 0) _key = 'A' + 3 * (key - 2) + 2;
    else _key = 'A' + 3 * (key - 2) + numPress % 4 - 2;
  }

  return _key;
}
