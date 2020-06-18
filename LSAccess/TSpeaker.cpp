//---------------------------------------------------------
// @File: TSpeaker*
// @Purpose:
// @Author: eric.macia
// @Data: 03/05/2020
//---------------------------------------------------------

//------------------------ INCLUDES -----------------------

#include "TSpeaker.h"

//------------------------ VARIABLES ----------------------

static char timer;
static char beeps;
static char pwmCounter;

//------------------------ FUNCTIONS ----------------------

void initTSpeaker(void) {
  pinMode(SPEAKER, OUTPUT); //Set SPEAKER pin as OUTPUT
  digitalWrite(SPEAKER, LOW); //Initialize SPEAKER to LOW
  beeps = 5;
  pwmCounter = 0;
  timer = TiGetTimer();
  TiResetTics(timer);
  Serial.println("Javi comeme el nabo");

}

void SpAddBeeps(char numBeeps){
  beeps += numBeeps;
}

void motorTSpeaker(void){
  static char state = 0;
  switch (state){
    case 0:
      if (beeps != 0) {
        TiResetTics(timer);
        pwmCounter = 0;
        digitalWrite(SPEAKER, HIGH);
        state = 1;
      }
      break;
    case 1:
      if (TiGetTics(timer) >= T_HIGH && pwmCounter != 100) {
        digitalWrite(SPEAKER, LOW);
        state = 2;
      }
      else if (pwmCounter == 100) {
        digitalWrite(SPEAKER, LOW);
        TiResetTics(timer);
        state = 3;
      }
      break;
    case 2:
      if (TiGetTics(timer) >= T_PWM) {
        pwmCounter++;
        digitalWrite(SPEAKER, HIGH);
        TiResetTics(timer);
        state = 1;
      }
      break;
    case 3:
      if (TiGetTics(timer) >= T_BEEP) {
        beeps--;
        state = 0;
      }
      break;
  }
}
