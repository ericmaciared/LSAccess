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
static char row;
static char key;
//------------------------ FUNCTIONS ----------------------

void initTKeyboard(void) {
  pinMode(COL0, INPUT_PULLUP);
  pinMode(COL1, INPUT_PULLUP);
  pinMode(COL2, INPUT_PULLUP);
  pinMode(ROW0, OUTPUT);
  pinMode(ROW1, OUTPUT);
  pinMode(ROW2, OUTPUT);
  pinMode(ROW3, OUTPUT);
  digitalWrite(ROW0, HIGH); //Initialize ROW0 to HIGH
  digitalWrite(ROW1, LOW);  //Initialize ROW1 to LOW
  digitalWrite(ROW2, LOW);  //Initialize ROW2 to LOW
  digitalWrite(ROW3, LOW);  //Initialize ROW3 to LOW
  row = 0;
  key = -1;
  timer = TiGetTimer();
}

void motorTKeyboard(void){
  static char state = 0;
  switch(state){
    case 0:
    if (!digitalRead(COL0) || !digitalRead(COL1) || !digitalRead(COL2)) {
      TiResetTics(timer);
      state = 1;
    }
    else{
      row = (++row > 3) ? 0 : row;
      digitalWrite(ROW0, (row == 0) ? LOW : HIGH);
      digitalWrite(ROW1, (row == 1) ? LOW : HIGH);
      digitalWrite(ROW2, (row == 2) ? LOW : HIGH);
      digitalWrite(ROW3, (row == 3) ? LOW : HIGH);
    }
    break;
    case 1:
    if (TiGetTics(timer) >= T_DEBOUNCE) state = 2;
    break;
    case 2:
    if (!digitalRead(COL0) && digitalRead(COL1) && digitalRead(COL2)) {
      key = 3*row+1;
      state = 3;
    }
    else if (digitalRead(COL0) && !digitalRead(COL1) && digitalRead(COL2)) {
      key = 3*row+2;
      state = 3;
    }
    else if (digitalRead(COL0) && digitalRead(COL1) && !digitalRead(COL2)) {
      key = 3*row+3;
      state = 3;
    }    
    else state = 0;
    break;
    case 3:
    if (digitalRead(COL0) && digitalRead(COL1) && digitalRead(COL2)) {
      TiResetTics(timer);
      state = 4;
    }
    break;
    case 4:
    if (TiGetTics(timer) >= T_DEBOUNCE) {
      key = -1;
      state = 0;
    }
    break;
  }
}

char KeyCharAvailable(void){
  return ((key == -1) ? FALSE : TRUE);
}

char KeyGetChar(void){
  return key;
}
