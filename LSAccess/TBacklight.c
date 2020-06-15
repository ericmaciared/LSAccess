/*//---------------------------------------------------------
// @File: TTimer*
// @Purpose:
// @Author: eric.macia
//          guillermo.sabate
// @Data: 05/05/2020
//---------------------------------------------------------

//------------------------ INCLUDES -----------------------
#include "TBacklight.h"
#include <arduino.h>

//------------------------ DEFINES ------------------------
#define TIME_PWM 500

//------------------------ VARIABLES ----------------------
static unsigned char state;
static unsigned char timer;
static unsigned char timeOn;

//------------------------ FUNCTIONS ----------------------

void initTBacklight(void) {
  SET_BL_DIR();
  BL_OFF();
  state = 0;
  timer = TiGetTimer();
  timeOn=10;
}

void motorTBacklight(void){
        switch(state){
        case 0:
            if (TiGetTics(timer)>=timeOn){
                TiResetTics(timer);
                state = 1;
                BL_OFF();
            }
            break;
        case 1:
            if (TiGetTics(timer)>= PERIODBL - timeOn){
                TiResetTics(timer);
                state = 0;
                BL_ON();
            }
            break;
        }
}

char getTBacklightDuty(void){
  return timeOn;
}

void setTBacklightDuty(char newTime){
  timeOn = newTime;
}*/
